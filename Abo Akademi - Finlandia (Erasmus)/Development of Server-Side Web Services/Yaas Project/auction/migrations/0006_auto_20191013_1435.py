# Generated by Django 2.2.5 on 2019-10-13 14:35

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('auction', '0005_item_bidder'),
    ]

    operations = [
        migrations.RenameField(
            model_name='item',
            old_name='new_price',
            new_name='max_bid',
        ),
        migrations.RenameField(
            model_name='item',
            old_name='bidder',
            new_name='max_bidder',
        ),
    ]