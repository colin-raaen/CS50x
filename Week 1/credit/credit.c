#include <cs50.h>
#include <stdio.h>

int card_check(long z);
int checksum_calculation(long y);
int checksum_calculationtwo(long x);
bool amex_test(long w, int a);
bool visa_test(long v, int b);
bool mastercard_test(long u, int c);

int main(void)
{
    //prompt user for credit card number
    long credit_card_number = get_long("Number: ");

    //calcualte check sum using Luhns algorithm
    int check_sum = checksum_calculation(credit_card_number);
    check_sum += checksum_calculationtwo(credit_card_number);
    //if doesn't pass algorithm print invalid and exit
    if (check_sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    //get card number length
    int number_check = card_check(credit_card_number);

    //check Amex brand print if true
    bool amex_check = amex_test(credit_card_number, number_check);
    if (amex_check == true)
    {
        printf("AMEX\n");
        return 0;
    }

    //check Visa brand print if true
    bool visa_check = visa_test(credit_card_number, number_check);
    if (visa_check == true)
    {
        printf("VISA\n");
        return 0;
    }

    //check mastercard brand print if true
    bool mastercard_check = mastercard_test(credit_card_number, number_check);
    if (mastercard_check == true)
    {
        printf("MASTERCARD\n");
        return 0;
    }
    //if not brands found print invalid
    printf("INVALID\n");
    return 0;
}
int checksum_calculation(long y)
{
    int check_sum = 0;
    int multiplier = 0;
    int adder = 0;
    //multiply every other number by 2
    while (y != 0)
    {
        y = y / 10;
        multiplier = y % 10;
        multiplier = (multiplier * 2);
        //add the digits of products together
        while (multiplier != 0)
        {
            adder = multiplier % 10;
            check_sum += adder;
            multiplier = multiplier / 10;
        }
        y = y / 10;
    }
    return check_sum;
}
int checksum_calculationtwo(long x)
{
    int check_sum_two = 0;
    int multiplier = 0;
    //add every other number together that wasn't used
    while (x != 0)
    {
        multiplier = x % 10;
        check_sum_two += multiplier;
        x = x / 100;
    }
    return check_sum_two;
}
int card_check(long z)
{
    int count = 0;
    //iterate over credit card numbers adding to count
    while (z != 0)
    {
        z = z / 10;
        count++;
    }
    return count;
}
bool amex_test(long w, int a)
{
    long b = w;
    //remove last digit until only two are left
    while (b >= 100)
    {
        b = b / 10;
    }
    //if amex criteria is met return true
    if (a == 15 && (b == 34 || b == 37))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool visa_test(long v, int b)
{
    long c = v;
    //remove last digit until only one is left
    while (c >= 10)
    {
        c = c / 10;
    }
    //if Visa criteria is met return true
    if ((b == 13 || b == 16) && c == 4)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool mastercard_test(long u, int c)
{
    long b = u;
    //remove last digit until only two are left
    while (b >= 100)
    {
        b = b / 10;
    }
    //if mastercard criteria is met return true
    if (c == 16 && (b >= 51 && b <= 55))
    {
        return true;
    }
    else
    {
        return false;
    }
}