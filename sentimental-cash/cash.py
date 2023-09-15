from cs50 import get_float
from math import trunc


def main():
    # Ask how many cents the customer is owed
    cents = get_cents()

    # calculate the number of quarters to give the customer
    quarters = calculate_coins(cents, .25)
    cents = round(cents - quarters * .25, 2)

    # Calculate the number of dimes to give the customer
    dimes = calculate_coins(cents, .1)
    cents = round(cents - dimes * .10, 2)

    # Calculate the number of nickels to give the customer
    nickels = calculate_coins(cents, .05)
    cents = round(cents - nickels * .05, 2)

    # Calculate the number of pennies to give the customer
    pennies = calculate_coins(cents, .01)

    # calculate number of coins
    coins = quarters + dimes + nickels + pennies

    # Print total number of coins to give the customer
    print(coins)


def get_cents():
    while True:
        n = get_float("Change owed: ")
        # make sure cents is a positive value
        if n > 0:
            return n


def calculate_coins(cents, value):
    return cents // value


if __name__ == "__main__":
    main()