#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string a);
int count_words(string b);
int count_sentences(string c);

int main(void)
{
    //get string from user
    string text = get_string("Text: ");

    //count number of letters in string
    int letter_count = count_letters(text);

    //count number of words
    int word_count = count_words(text);

    //count number of sentences
    int sentence_count = count_sentences(text);

    //convert ints to floats
    float letter_count_f = (float) letter_count;
    float word_count_f = (float) word_count;
    float sentence_count_f = (float) sentence_count;

    //define grading index
    float L = ((letter_count_f * 100) / word_count_f);
    float S = ((sentence_count_f * 100) / word_count_f);
    int index = round((0.0588 * L) - (0.296 * S) - 15.8);

    //print grade level
    if (index <= 16 && index > 0)
    {
        printf("Grade %d\n", index);
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }
    return 0;
}
int count_letters(string a)
{
    //loop through phrase counting words
    int counter = 0;
    for (int i = 0, n = strlen(a); i < n; i++)
    {
        if (isalpha(a[i]))
        {
            counter++;
        }
    }
    return counter;
}
int count_words(string b)
{
    //loop through phrase counting words
    int counter = 0;
    for (int i = 0, n = strlen(b); i <= n; i++)
    {
        if (isspace(b[i]) || b[i] == '\0')
        {
            counter++;
        }
    }
    return counter;
}
int count_sentences(string c)
{
    //loop through phrase counting sentences
    int counter = 0;
    for (int i = 0, n = strlen(c); i <= n; i++)
    {
        if ((c[i]) == '.' || c[i] == '!' || c[i] == '?')
        {
            counter++;
        }
    }
    return counter;
}