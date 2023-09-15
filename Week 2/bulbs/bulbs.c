#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // get string from user and declare buffer
    char *string = get_string("words to convert: ");
    int buffer[sizeof(string)];

    // loop through each letter of string
    for (int i = 0, n = strlen(string); i < n; i++)
    {
        //typecast character to int
        int x = string[i];

        // loop through calculating light until 8 bulbs
        for (int j = 0; j < 8; j++)
        {
            if (x == 0)
            {
                buffer[j] = 0;
            }
            else if (x % 2 == 0)
            {
                buffer[j] = 0;
                x = x / 2;
            }

            else if (x % 2 > 0)
            {
                buffer[j] = 1;
                x = x / 2;
            }
        }

        //call print bulb in reverse order
        for (int k = 7; k >= 0; k--)
        {
            print_bulb(buffer[k]);
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
