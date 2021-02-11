# Miguel Ángel Benítez Alguacil
## Student ID: 1900853


## List of implemented requirements
For the realization of this project I have followed the tests provided in testsTDD.py, I have passed all of them successfully.
Also I have done the "UC3: create auction", "REQ9.3: store language preference" and "TREQ4.1.1 test REQ9.3".
- In the UC3 there is a section in class CreateAuction that must be uncommented in order to have the confirmation functionality, I had to comment it because other way, all the tests that involved the auction creation such as bid, ban... would have failed because the tests don't contemplate the confirmation of the auction.

This is the part of the code that you need to uncomment (simply erase both '''):

\# Uncomment this paragraph to check the Create Auction

'''

form = ConfAuctionForm({"a_title": a_title, "a_description": a_description, "a_minimum_price": a_minimum_price, "a_deadline_date": a_deadline_date})

return render(request, 'auction/confirm_auction.html', {'form': form})

'''


The list of use cases that I have implemented are:
- UC1: create user
- UC2: edit user
- UC3: create auction
- UC4: edit auction description
- UC5: Browse & Search
- UC6: bid
- UC7: ban auction
- UC8: resolve auction
- UC9: language switching
- UC11: currency exchange
- WS1: Browse & Search API
- WS2: Bid api
- REQ9.3: store language preference (no test provided, verified manually) 1
- TREQ4.1.1 test REQ9.3


## Browser used
I have used Google Chrome to test the application


## List of Pyhton packages used

