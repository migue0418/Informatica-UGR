from django.db import models


class Item(models.Model):
    title = models.CharField(max_length=256)
    description = models.CharField(max_length=1024, blank=True)
    minimum_price = models.FloatField(default=0.0)
    deadline_date = models.DateTimeField()
    created_date = models.DateTimeField(auto_now_add=True)
    status = models.CharField(max_length=1024, default="Active")
    auctioneer = models.CharField(max_length=256, default="")
    current_price = models.FloatField(default=0.0)
    max_bidder = models.CharField(max_length=256, default="")
    bidders = list()    # Useful for the resolve part (send email to all the bidders)
    message = models.CharField(max_length=512, default="")
    detail = models.CharField(max_length=512, default="")

    def __str__(self):
        return self.title
