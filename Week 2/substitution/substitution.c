#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool only_alpha(string s);
bool twenty_six(string t);
bool alpha_unique(string u);
char ciphertext_shift(int b, string y, char w);

int main(int argc, string argv[])
{
    // check if program has just one command-line argument
    if (argc != 2)
    {
        //exit if not one command-line argument
        printf("Usage:./caeser KEY\n");
        return 1;
    }
    // check if program has only letters in command-line argument
    bool alphacheck = only_alpha(argv[1]);
    if (alphacheck == false)
    {
        //exit if doesn't contain only letters
        printf("Usage:./substitution key must contain only alphabetic characters.\n");
        return 1;
    }
    // check if key has 26 characters
    bool twentysixcheck = twenty_six(argv[1]);
    if (twentysixcheck == false)
    {
        //exit if key doesn't have 26 characters
        printf("Usage:./substitution key must contain 26 characters.\n");
        return 1;
    }

    // check that key has 26 unique letters
    bool uniquealphacheck = alpha_unique(argv[1]);
    if (uniquealphacheck == false)
    {
        //exit if key doesn't contain 26 unique letters
        printf("Usage:./substitution key must not contain repeated characters.\n");
        return 1;
    }
    //Get Plaintext
    string plaintext = get_string("plaintext: ");

    // Convert argv[1] from a string to int
    int converted_key_plain = atoi(plaintext);

    printf("ciphertext: ");
    char ct;
    //For each character in the plaintext
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        int plain_alpha_place = toupper(plaintext[i]) - 65;
        ct = ciphertext_shift(plain_alpha_place, argv[1], plaintext[i]);
        //Print rotated characters ciphertext
        printf("%c", ct);
    }
    printf("\n");
    return 0;
}
// check if program has only letters in command-line argument
bool only_alpha(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isalpha(s[i]))
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
// check if key has 26 characters
bool twenty_six(string t)
{
    int n = strlen(t);
    if (n == 26)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool alpha_unique(string u)
{
    for (int i = 0; i < strlen(u) - 1; i++)
    {
        for (int j = i + 1; j < strlen(u); j++)
        {
            if (toupper(u[i]) == toupper(u[j]))
            {
                return false;
            }
        }
    }
    return true;
}

char ciphertext_shift(int b, string y, char w)
{
    char c;
    // Rotate the character if it's a letter
    if (isalpha(w) && isupper(w) && isupper(y[b]))
    {
        c = y[b];
    }
    else if (isalpha(w) && islower(w) && islower(y[b]))
    {
        c = y[b];
    }
    else if (isalpha(w) && isupper(w) && islower(y[b]))
    {
        c = y[b] - 32;
    }
    else if (isalpha(w) && islower(w) && isupper(y[b]))
    {
        c = y[b] + 32;
    }
    else
    {
        c = w;
    }
    return c;
}