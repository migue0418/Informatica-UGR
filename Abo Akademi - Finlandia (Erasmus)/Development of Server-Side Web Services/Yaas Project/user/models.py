from django.contrib.auth.models import User
from django.db import models


class UserPreferences(models.Model):
    username = models.OneToOneField(User, to_field='username', on_delete=models.CASCADE)
    language_preference = models.CharField(max_length=5, default='EN')
