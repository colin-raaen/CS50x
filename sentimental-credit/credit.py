from cs50 import get_int


def main():
    # prompt user for credit card number
    credit_card_number = get_int("Number: ")

    # calculate check sum using the luhns algorithm
    check_sum = checksum_calculation(credit_card_number)
    # if doesn't pass algorithm print invalid and exit
    if check_sum % 10 != 0:
        print("INVALID")
        return

    number_length = len(str(credit_card_number))
    ccn = str(credit_card_number)
    # Amex check
    if number_length == 15 and ccn[:2] in ('34', '37'):
        print("AMEX")
        return 0
    # Visa Check
    elif (number_length == 13 or number_length == 16) and ccn[0] == '4':
        print("VISA")
        return 0
    # Mastercard Check
    elif number_length == 16 and 51 <= int(ccn[:2]) <= 55:
        print("MASTERCARD")
        return 0
    # if no match print invalid
    else:
        print("INVALID")
        return 0


def checksum_calculation(y):
    check_sum = 0
    # multiply every other number by 2
    while (y > 0):
        check_sum += y % 10
        y = y // 10
        multiplier = (y % 10) * 2
        # add digits of products together
        while (multiplier != 0):
            check_sum += multiplier % 10
            multiplier = multiplier // 10
        y = y // 10
    return check_sum


if __name__ == "__main__":
    main()