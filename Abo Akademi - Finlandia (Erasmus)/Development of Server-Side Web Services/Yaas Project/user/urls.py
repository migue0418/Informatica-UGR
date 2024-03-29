from django.urls import path, include
from . import views

app_name = 'user'
urlpatterns = [
    path('profile/', views.EditProfile.as_view(), name='editprofile'),
    path('', views.EditProfile.as_view(), name='user'),
    path('signup', views.SignUp.as_view(), name='signup'),
    path('signin', views.SignIn.as_view(), name='signin'),
    path('signout', views.signout, name='signout'),
    path('password/', views.change_password, name="changepassword")
]