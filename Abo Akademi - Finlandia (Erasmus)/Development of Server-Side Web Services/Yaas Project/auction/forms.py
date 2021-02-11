from django import forms
from datetime import timedelta
from django.utils import timezone


class CreateAuctionForm(forms.Form):
    title = forms.CharField(max_length=256)
    description = forms.CharField(widget=forms.Textarea())
    minimum_price = forms.FloatField(label="Minimum Price", min_value=0.01)
    deadline_date = forms.DateTimeField(input_formats=['%d.%m.%Y %H:%M:%S', ],
                                        widget=forms.TextInput(attrs={"placeholder": "dd.mm.yyyy HH:MM:SS"}),
                                        help_text="The format of date should be dd.mm.yyyy HH:MM:SS",
                                        label="Deadline Date")

    def is_deadline_valid(self):
        date = self.cleaned_data['deadline_date']
        minimum_date = timezone.now() + timedelta(hours=72)
        if date < minimum_date:
            return False
        else:
            return True


class ConfAuctionForm(forms.Form):
    CHOICES = [(x, x) for x in ("Yes", "No")]
    option = forms.ChoiceField(choices=CHOICES)
    a_title = forms.CharField(widget=forms.HiddenInput())
    a_description = forms.CharField(widget=forms.HiddenInput())
    a_minimum_price = forms.FloatField(widget=forms.HiddenInput())
    a_deadline_date = forms.DateTimeField(widget=forms.HiddenInput())


class NewPriceBidForm(forms.Form):
    new_price = forms.FloatField(label="New Price")