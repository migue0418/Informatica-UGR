from django.test import TestCase, override_settings
from django.contrib import auth
from django.urls import reverse
from django.utils import translation
from user.models import UserPreferences

current_points = 0


class ExampleTest(TestCase):
    def setUp(self):
        # setUp run before every test method
        pass

    def test_something_that_will_pass(self):
        self.assertTrue(True)


class REQ93_StoreLanguagePreferencesTests(TestCase):
    """REQ93: Store language preferences"""

    number_of_passed_tests = 0  # passed tests in this test case
    tests_amount = 2  # number of tests in this suite
    points = 2  # points granted by this use case if all tests pass

    def setUp(self):
        # Create user for testing purpose
        self.user1Info = {
            "username": "testUser1",
            "password": "123",
            "email": "user1@mail.com"
        }
        self.user2Info = {
            "username": "testUser2",
            "password": "321",
            "email": "user2@mail.com"
        }

        # Create both users
        self.client.post(reverse("signup"), self.user1Info)
        self.client.post(reverse("signup"), self.user2Info)

        # Change language preference of user1 to Swedish
        self.client.post(reverse("signin"), self.user1Info)
        lang_code = "sv"
        response = self.client.get(reverse("changeLanguage", args=(lang_code,)))

        # Change language preference of user2 to English
        self.client.post(reverse("signin"), self.user2Info)
        lang_code = "en"
        response = self.client.get(reverse("changeLanguage", args=(lang_code,)))

    @classmethod
    def tearDownClass(cls):
        # check if test case passed or failed
        calculate_points(cls.number_of_passed_tests, cls.tests_amount, cls.points, "REQ93")

    def test_store_language(self):
        """
        REQ9.3.1
        Check if the languages preferences have been stored in UserPreferences
        """

        # Check if the language preference of testUser1 is Swedish
        pref1 = UserPreferences.objects.get(username=self.user1Info["username"])
        self.assertEqual(pref1.language_preference, 'sv')

        # Check if the language preference of testUser2 is English
        pref2 = UserPreferences.objects.get(username=self.user2Info["username"])
        self.assertEqual(pref2.language_preference, 'en')

        # calculate points
        self.__class__.number_of_passed_tests += 1

    def test_check_if_language_user1_is_swedish(self):
        """
        REQ9.3.2
        Check if the language of the web page seen by the user1 is Swedish
        """

        self.client.post(reverse("signin"), self.user1Info)
        language = translation.get_language()
        self.assertEqual(language, 'sv')

        # calculate points
        self.__class__.number_of_passed_tests += 1

    def test_check_if_language_user2_is_english(self):
        """
        REQ9.3.3
        Check if the language of the web page seen by the user2 is English
        """

        self.client.post(reverse("signin"), self.user2Info)
        language = translation.get_language()
        self.assertEqual(language, 'en')

        # calculate points
        self.__class__.number_of_passed_tests += 1


def calculate_points(number_of_passed_tests, amount_of_tests, points_of_the_use_case, use_case_name):
    if number_of_passed_tests < amount_of_tests:
        print("{} fails!".format(use_case_name))
    else:
        global current_points
        current_points += points_of_the_use_case
        message = "{} passed, {} points, Current points: {}/2".format(use_case_name, points_of_the_use_case, current_points)
        print(message)
