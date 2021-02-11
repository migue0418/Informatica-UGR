from django.contrib.auth.decorators import login_required
from django.contrib.auth.models import User
from django.shortcuts import render, get_object_or_404
from django.utils.decorators import method_decorator
from django.views import View
from django.http import HttpResponse, HttpResponseRedirect
from rest_framework.utils import json

from auction.models import Item
from django.contrib import messages
from django.urls import reverse
from auction.forms import CreateAuctionForm, ConfAuctionForm
from django.core.mail import BadHeaderError, send_mail
from django.contrib import auth
from django.utils import timezone, translation
from django.utils.translation import gettext as _
import urllib.request
import json

from user.models import UserPreferences

currency = 1  # By default, the currency is EUR


def index(request):
    auctions = Item.objects.filter(status="Active").order_by('-created_date')

    for auction in auctions:  # Change the currency
        auction.current_price *= currency
        auction.minimum_price *= currency

    return render(request, "auction/index.html", {'auctions': auctions})


def search(request):
    if request.GET["term"].lower() != "":
        criteria = request.GET["term"].lower().strip()
        auctions = Item.objects.filter(title__contains=criteria, status="Active").order_by('-created_date')
    else:
        auctions = Item.objects.filter(status="Active").order_by('-created_date')
    return render(request, "auction/index.html", {'auctions': auctions})


class CreateAuction(View):
    def get(self, request):
        if self.request.user.is_authenticated:  # User authenticated
            form = CreateAuctionForm()
            return render(request, "auction/create.html", {"form": form}, status=200)
        else:
            messages.add_message(request, messages.ERROR, "You have to sign up to create an auction")
            return render(request, "signin.html", status=302)

    def post(self, request):
        form = CreateAuctionForm(request.POST)
        if self.request.user.is_authenticated:  # User authenticated
            if form.is_valid():
                valid_date = form.is_deadline_valid()
                if valid_date:  # Valid date (+72h)
                    cd = form.cleaned_data
                    a_title = cd['title']
                    a_description = cd['description']
                    a_minimum_price = cd['minimum_price']
                    a_deadline_date = cd['deadline_date']
                    a_username = self.request.user.username

                    # Uncomment this paragraph to check the Create Auction
                    ''' 
                    form = ConfAuctionForm({"a_title": a_title, "a_description": a_description, 
                                            "a_minimum_price": a_minimum_price, "a_deadline_date": a_deadline_date})
                    return render(request, 'auction/confirm_auction.html', {'form': form})
                    '''
                    new_auction = Item(title=a_title,
                                       description=a_description,
                                       minimum_price=a_minimum_price,
                                       current_price=a_minimum_price,
                                       deadline_date=a_deadline_date,
                                       auctioneer=a_username)
                    new_auction.save()

                    # Send auction confirmation email
                    send_mail(
                        'New Auction',
                        'Auction has been created successfully',
                        'admin@yaas.com',
                        [User.objects.get(username=a_username).email],
                        fail_silently=True,
                    )

                    messages.add_message(request, messages.SUCCESS, _("Auction has been created successfully"))
                    return HttpResponseRedirect(reverse("auction:index"))
                else:  # Invalid date
                    messages.add_message(request, messages.ERROR,
                                         _("The deadline date should be at least 72 hours from now"))
                    return render(request, "auction/create.html", {"form": form}, status=200)
            else:
                return render(request, "auction/create.html", {"form": form})
        else:  # User unauthenticated
            return render(request, "signin.html", {"form": form}, status=302)


def confirmauction(request):
    if request.method != "POST":
        return HttpResponseRedirect(reverse("auction:index"))

    option = request.POST.get('option', '')
    if option == 'Yes':
        a_title = request.POST.get('a_title', '')
        a_description = request.POST.get('a_description', '')
        a_minimum_price = request.POST.get('a_minimum_price', '')
        a_deadline_date = request.POST.get('a_deadline_date', '')
        a_username = request.user.username

        new_auction = Item(title=a_title,
                           description=a_description,
                           minimum_price=a_minimum_price,
                           current_price=a_minimum_price,
                           deadline_date=a_deadline_date,
                           auctioneer=a_username)
        new_auction.save()

        # Send auction confirmation email
        send_mail(
            'New Auction',
            'Auction has been created successfully',
            'admin@yaas.com',
            [User.objects.get(username=a_username).email],
            fail_silently=True,
        )

        messages.add_message(request, messages.SUCCESS, "Auction has been created successfully")
        return HttpResponseRedirect(reverse("auction:index"))
    else:
        messages.add_message(request, messages.INFO, "Auction cancelled")
        return HttpResponseRedirect(reverse("auction:index"))


class EditAuction(View):
    def get(self, request, item_id):
        auction = get_object_or_404(Item, id=item_id)
        if self.request.user.username != auction.auctioneer:
            return HttpResponse("That is not your auction to edit")
        else:
            return render(request, "auction/edit.html",
                          {'user': self.request.user,
                           "id": auction.id,
                           "title": auction.title,
                           "description": auction.description}, status=200)

    def post(self, request, item_id):
        auction = get_object_or_404(Item, id=item_id)
        if self.request.user.username != auction.auctioneer:
            return HttpResponse(_("That is not your auction to edit"))
        else:
            description = request.POST["description"].strip()
            auction.description = description
            auction.save()
            messages.add_message(request, messages.INFO, _("Auction has been updated successfully"))
            return HttpResponseRedirect(reverse("auction:index"))


def bid(request, item_id):
    auction = get_object_or_404(Item, id=item_id)
    if request.method == 'POST':  # POST
        if request.user.is_authenticated:
            # User is not anonymous
            if request.user.username != auction.auctioneer:
                # User can bid
                if auction.status == "Active":
                    # Auction is active
                    newbid = request.POST.get("new_price").strip()
                    newbid = float(newbid)
                    if auction.deadline_date < timezone.now():
                        # Invalid time
                        return HttpResponse(_("You can only bid on active auction"))

                    else:
                        minimum_bid = float(auction.current_price) + 0.01
                        if newbid < minimum_bid:
                            # Invalid bid amount
                            messages.add_message(request, messages.ERROR,
                                                 "New bid must be greater than the current bid for at least 0.01")
                            return render(request, "auction/bid.html", {'user': request.user,
                                                                        "id": auction.id,
                                                                        "title": auction.title,
                                                                        "description": auction.description,
                                                                        "auctioneer": auction.auctioneer,
                                                                        "current_price": auction.current_price}, status=200)

                        else:
                            # Valid data
                            auction.current_price = newbid
                            auction.max_bidder = request.user.username
                            if request.user.username not in auction.bidders:
                                auction.bidders.append(auction.max_bidder)
                            auction.save()
                            # Send email to auctioneer
                            send_mail(
                                'New Bid',
                                'A new bid has been registered',
                                'admin@yaas.com',
                                [User.objects.get(username=auction.auctioneer).email],
                                fail_silently=True,
                            )
                            # Send email to last bidder
                            send_mail(
                                'New Bid',
                                'A new bid greater than yours has been registered',
                                'admin@yaas.com',
                                [User.objects.get(username=auction.max_bidder).email],
                                fail_silently=True,
                            )

                            messages.add_message(request, messages.SUCCESS, _("You has bid successfully"))
                            return HttpResponseRedirect(reverse("auction:index"))

                else:
                    # Inactive auction
                    return HttpResponse(_("You can only bid on active auction"))

            else:
                # Auctioneer
                return HttpResponse(_("You cannot bid on your own auctions"))

        else:
            # Unauthenticated user
            messages.add_message(request, messages.ERROR, "Unauthenticated user can't bid on an auction")
            return render(request, "signin.html", status=302)

    else:
        # GET
        return render(request, "auction/bid.html", {'user': request.user,
                                                    "id": auction.id,
                                                    "title": auction.title,
                                                    "description": auction.description,
                                                    "auctioneer": auction.auctioneer,
                                                    "current_price": auction.current_price}, status=200)


def ban(request, item_id):
    if request.user.is_superuser:
        auction = get_object_or_404(Item, id=item_id)
        auction.status = "Banned"
        auction.save()

        # Send email to auctioneer
        send_mail(
            'New Bid',
            'Your auction is now banned',
            'admin@yaas.com',
            [User.objects.get(username=auction.auctioneer).email],
            fail_silently=True,
        )

        # Send email to last bidder
        send_mail(
            'Auction banned',
            'The auction you have bid is now banned',
            'admin@yaas.com',
            [User.objects.get(username=request.user.username).email],
            fail_silently=True,
        )

        messages.add_message(request, messages.INFO, "Ban successfully")
        return HttpResponseRedirect(reverse("auction:index"))
    else:
        return HttpResponseRedirect(reverse("auction:index"), status=302)


def resolve(request):
    auctions_active = Item.objects.filter(status="Active").order_by('-created_date')
    # Take the auction out of the Active list
    for auction in auctions_active:
        if auction.deadline_date < timezone.now():
            auction.status = "Due"
            auction.save()
    auctions_due = Item.objects.filter(status="Due").order_by('-created_date')
    resolved_auctions = {"resolved_auctions": []}

    auctioneers = []    # Get all the auctioners who need to be notified
    for auc in auctions_due:
        if auc.auctioneer not in auctioneers:
            auctioneers.append(auc.auctioneer)
        if auc.bidders != "":
            auc.status = "Adjudicated"  # Resolve auction
            auc.save()
            resolved_auctions["resolved_auctions"].append(auc.title)

        for bidder in auc.bidders:
            print("bidder " + bidder)
            send_mail(  # Notify the bidders
                'Auction resolved',
                'The auction you have bid is now resolved',
                'admin@yaas.com',
                [User.objects.get(username=bidder).email],
                fail_silently=True,
            )
    ### This should be put in
    for auctioneer in auctioneers:
        send_mail(  # Notify the auctioneer
            'Auction resolved',
            'Your auction has been resolved',
            'admin@yaas.com',
            [User.objects.get(username=auctioneer).email],
            fail_silently=True,
        )

    return HttpResponse(json.dumps(resolved_auctions), content_type="application/json")


def changeLanguage(request, lang_code):
    translation.activate(lang_code)
    request.session[translation.LANGUAGE_SESSION_KEY] = lang_code

    if request.user.is_authenticated:
        user_pref = UserPreferences.objects.get(username=request.user)

    if lang_code == "sv":
        # Save language preferences of an user
        if request.user.is_authenticated:
            user_pref.language_preference = 'sv'
            user_pref.save()
        return HttpResponse("Language has been changed to Swedish")

    elif lang_code == "en":
        # Save language preferences of an user
        if request.user.is_authenticated:
            user_pref.language_preference = 'en'
            user_pref.save()
        return HttpResponse("Language has been changed to English")

    else:
        return HttpResponse("Language has been changed to " + lang_code)


def changeCurrency(request, currency_code):
    response = urllib.request.urlopen('http://data.fixer.io/api/latest?access_key=7754e097679b860dc76b95d83376a3e1')
    html = response.read().decode("utf-8")
    my_dict = json.loads(html)
    currency_code = currency_code.lower()  # lower case
    global currency

    # Change currency USD
    if currency_code == 'usd':
        currency = my_dict["rates"]["USD"]
        return HttpResponse("Currency has been changed to USD")
    # Change currency EUR
    elif currency_code == 'eur':
        currency = 1
        return HttpResponse("Currency has been changed to EUR")
    # Currency by default is EUR
    else:
        currency = 1
        return HttpResponse("Currency only changes between EUR and USD, default=EUR")
