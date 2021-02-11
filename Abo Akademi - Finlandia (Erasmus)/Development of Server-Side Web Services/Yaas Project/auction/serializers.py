from rest_framework import serializers
from auction.models import Item


class ItemShortSerializer(serializers.ModelSerializer):
    class Meta:
        model = Item
        fields = ('id', 'title', 'description', 'minimum_price', 'deadline_date')


class ItemBidShortSerializer(serializers.ModelSerializer):
    class Meta:
        model = Item
        fields = ('message', 'title', 'description', 'current_price', 'deadline_date', 'detail')


class ItemDetailSerializer(serializers.ModelSerializer):
    class Meta:
        model = Item
        fields = ('id', 'title', 'description', 'minimum_price', 'deadline_date', 'current_price', 'auctioneer', 'bidders')
