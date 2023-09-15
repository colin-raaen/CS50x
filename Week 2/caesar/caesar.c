#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool only_digits(string s);
char ciphertext_shift(char w, int key);
int main(int argc, string argv[])
{
    // check if program has just one command-line argument
    if (argc != 2)
    {
        //exit if not one command-line argument
        printf("Usage:./caeser key\n");
        return 1;
    }
    // check if program has only digits in command-line argument
    bool digitcheck = only_digits(argv[1]);
    if (digitcheck == false)
    {
        printf("Usage:./caeser key\n");
        return 1;
    }
    // Convert argv[1] from a string to int
    int converted_key = atoi(argv[1]);

    //Get Plaintext
    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");
    char ct;
    //For each character in the plaintext
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        ct = ciphertext_shift(plaintext[i], converted_key);
        //Print rotated characters ciphertext
        printf("%c", ct);
    }
    printf("\n");
    return 0;
}
bool only_digits(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isdigit(s[i]))
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}
char ciphertext_shift(char w, int key)
{
    char c;
    // Rotate the character if it's a letter
    if (isalpha(w) && isupper(w))
    {
        c = ((((w - 65) + key) % 26) + 65);
    }
    else if (isalpha(w) && islower(w))
    {
        c = ((((w - 97) + key) % 26) + 97);
    }
    else
    {
        c = w;
    }
    return c;
}