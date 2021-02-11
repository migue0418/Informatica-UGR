from django.utils import translation
from django.views import View
from django.contrib import messages
from django.contrib.auth.models import User
from django.contrib.auth.forms import UserCreationForm
from django.http import HttpResponseRedirect
from django.shortcuts import render, redirect, get_object_or_404
from django.urls import reverse
from user.forms import SignUpForm, EditProfileForm
from django.contrib import auth
from django.contrib.auth.forms import UserChangeForm, PasswordChangeForm
from django.contrib.auth import update_session_auth_hash
from user.models import UserPreferences


class SignUp(View):
    def get(self, request):
        form = SignUpForm()
        return render(request, "signup.html", {'form': form})

    def post(self, request):
        form = SignUpForm(request.POST)
        if form.is_valid():
            clean_username = form.cleaned_data['username']
            clean_email = form.cleaned_data['email']
            clean_password = form.cleaned_data['password']

            if len(User.objects.filter(username=clean_username)) > 0:
                messages.add_message(request, messages.ERROR, "This username has been taken")
                return render(request, 'signup.html', {"form": form}, status=200)

            elif len(User.objects.filter(email=clean_email)) > 0:
                messages.add_message(request, messages.ERROR, "This email has been taken")
                return render(request, 'signup.html', {"form": form}, status=200)

            else:
                user = User.objects.create_user(clean_username, clean_email, clean_password)
                user.save()

                user_pref = UserPreferences(username=user, language_preference='EN')
                user_pref.save()

                messages.add_message(request, messages.INFO, "User created")
                return HttpResponseRedirect(reverse("index"), status=302)
        else:
            return render(request, 'signup.html', {"form": form}, status=200)


class SignIn(View):
    def get(self, request):
        return render(request, 'signin.html')

    def post(self, request):
        username = request.POST.get('username', '')
        password = request.POST.get('password', '')
        user = auth.authenticate(username=username, password=password)
        if user is None:
            messages.add_message(request, messages.INFO, "Invalid username or password")
            return render(request, 'signin.html')
        else:
            auth.login(request, user)

            # Activate language stored in preferences
            user_pref = UserPreferences.objects.get(username=request.user)
            lang_preference = user_pref.language_preference
            translation.activate(lang_preference)
            request.session[translation.LANGUAGE_SESSION_KEY] = lang_preference

            messages.add_message(request, messages.INFO, "Signed in")
            return HttpResponseRedirect(reverse("index"), status=302)


def signout(request):
    auth.logout(request)
    return HttpResponseRedirect(reverse("index"), status=302)


class EditProfile(View):
    def get(self, request):
        if self.request.user.is_authenticated:
            form = EditProfileForm(instance=request.user)
            return render(request, 'edit_profile.html', {"form": form}, status=200)
        else:
            return HttpResponseRedirect(reverse("signin"), status=302)

    def post(self, request):
        form = EditProfileForm(request.POST, instance=request.user)

        if form.is_valid():
            clean_email = User.objects.filter(email=form.cleaned_data['email'])

            if len(clean_email) > 0:
                messages.add_message(request, messages.ERROR, "This email has been taken")
                return render(request, 'edit_profile.html', {"form": form}, status=200)
            else:
                form.save()
                return render(request,'profile.html', status=302)


def change_password(request):
    if request.method == 'POST':
        form = PasswordChangeForm(data=request.POST, user=request.user)
        if form.is_valid():
            form.save()
            update_session_auth_hash(request, form.user)
            messages.add_message(request, messages.INFO, "Password updated!")
            return render(request, 'profile.html', status=302)
        else:
            messages.add_message(request, messages.ERROR, "Fill the form correctly")
            return HttpResponseRedirect('/user/password')
    else:
        form = PasswordChangeForm(user=request.user)
        return render(request, 'change_password.html', {"form": form}, status=200)
