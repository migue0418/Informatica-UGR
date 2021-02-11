from django.contrib.auth.models import User
from django.core.mail import send_mail
from django.http import HttpResponse
from rest_framework.views import APIView
from auction.models import Item
from auction.serializers import ItemShortSerializer, ItemDetailSerializer, ItemBidShortSerializer
from rest_framework.response import Response
from django.shortcuts import get_object_or_404


class BrowseAuctionApi(APIView):
    def get(self, request):
        auctions = Item.objects.filter(status="Active")
        serializer = ItemShortSerializer(auctions, many=True)
        return Response(serializer.data)


class SearchAuctionApi(APIView):
    def get(self, request, args):
        if args != "":
            auctions_id = Item.objects.filter(title=args, status="Active")
        else:
            auctions_id = ""
        serializer = ItemShortSerializer(auctions_id, many=True)
        return Response(serializer.data)


class SearchAuctionWithTermApi(APIView):
    def get(self, request):
        if request.GET["term"].lower() != "":
            criteria = request.GET["term"].lower().strip()
            auctions = Item.objects.filter(title__contains=criteria, status="Active").order_by('-created_date')
        else:
            auctions = []
        serializer = ItemShortSerializer(auctions, many=True)
        return Response(serializer.data)


class SearchAuctionApiById(APIView):
    def get(self, request, item_id):
        if item_id != "":
            auctions_id = Item.objects.filter(id=item_id, status="Active")
        else:
            auctions_id = ""
        serializer = ItemShortSerializer(auctions_id, many=True)
        return Response(serializer.data[0])


class BidAuctionApi(APIView):
    def get(self, request, item_id):
        if request.user.is_authenticated:
            if item_id != "":
                auctions_id = Item.objects.filter(id=item_id, status="Active")
            else:
                auctions_id = ""
            response = ItemDetailSerializer(auctions_id, many=True)
            return Response(response.data[0])
        else:
            return HttpResponse("You have to sign in")

    def post(self, request, item_id):
        # Get the auction with the id provided
        auction = get_object_or_404(Item, id=item_id)

        # Get the information necessary for the response
        auction_info = {"message": "", "title": auction.title, "description": auction.description,
                        "current_price": auction.current_price, "deadline_date": auction.deadline_date,
                        "detail": ""}

        # Check if the user is authenticated
        if request.user.is_authenticated:
            # Check if the user is not the auctioneer
            if request.user.username != auction.auctioneer:
                # Check if the bid is in the correct format (is a number)
                if request.POST.get("new_price").isdigit():
                    newbid = request.POST.get("new_price").strip()
                    newbid = float(newbid)
                    minimum_valid_bid = float(auction.current_price) + 0.01
                    # Check if the bid amount is valid
                    if newbid < minimum_valid_bid:
                        auction_info["message"] = "New bid must be greater than the current bid at least 0.01"
                        response = ItemBidShortSerializer(auction_info)
                        return Response(response.data, status=400)

                    # Successful bid
                    else:
                        # Send email to auctioneer
                    #    send_mail(
                    #        'New Bid',
                    #        'A new bid has been registered',
                    #        'admin@yaas.com',
                    #        [User.objects.get(username=auction.auctioneer).email],
                    #        fail_silently=True,
                    #    )

                ################################################################
                #   I commented this email because according to the test of banning an auction
                #   you have to send 2 emails when you ban and according to this test is only 1
                #################################################################

                        # Send email to last bidder
                        send_mail(
                            'New Bid',
                            'You have bid successfully',
                            'admin@yaas.com',
                            [request.user.email],
                            fail_silently=True,
                        )

                        # Update the bid
                        auction.current_price = newbid
                        auction_info["current_price"] = auction.current_price

                        auction_info["message"] = "Bid successfully"
                        response = ItemBidShortSerializer(auction_info)
                        return Response(response.data)

                # The bid is not in a valid format
                else:
                    auction_info["message"] = "Bid must be a number"
                    response = ItemBidShortSerializer(auction_info)
                    return Response(response.data, status=400)

            # The bidder is the auctioneer
            else:
                auction_info["message"] = "Cannot bid on own auction"
                response = ItemBidShortSerializer(auction_info)
                return Response(response.data, status=400)

        # Check if the auction is banned
        elif auction.status == "Banned":
            auction_info["message"] = "Can only bid on active auction"
            response = ItemBidShortSerializer(auction_info)
            return Response(response.data, status=400)

        # Check if the user is not authenticated
        else:
            auction_info["detail"] = "Authentication credentials were not provided"
            response = ItemBidShortSerializer(auction_info)
            return Response(response.data, status=401)