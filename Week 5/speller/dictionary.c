// Implements a dictionary's functionality

#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include<math.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 78;

// Hash table
node *table[N];
unsigned int word_counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Access hash function
    unsigned int hash_code = hash(word);
    // declare traversing pointer variable
    node *cursor = table[hash_code];

    //check if word is a match
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // return variable declaration
    unsigned int hash_code = 0;
    double x = fmin(strlen(word), 3);

    // Hash function that adds first three letters of word together
    for (int i = 0; i < x; i++)
    {
        if (islower(word[i]))
        {
            hash_code += word[i] - 97;
        }
        else if (isupper(word[i]))
        {
            hash_code += word[i] - 65;
        }
    }
    return hash_code;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //buffer declaration
    char buffer[LENGTH + 1];
    // Open dictionary file
    FILE *dict_load = fopen(dictionary, "r");
    if (dict_load == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        unload();
        return false;
    }
    //read strings from text file to nodes
    while (fscanf(dict_load, "%s", buffer) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Not enough memory \n");
            unload();
            return false;
        }
        //copy word into node
        strcpy(n->word, buffer);
        n->next = NULL;

        //call hash function and return index
        unsigned int hash_code = hash(n->word);

        //insert node into hast table linked list using hash code
        n->next = table[hash_code];
        table[hash_code] = n;

        word_counter++;
    }
    fclose(dict_load);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // return amount of words counted in dictionary
    return word_counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // free memory for the hash table
    for (int i = 0; i < N; i++)
    {
        // delclare cursor and temp nodes to traverse and free memory
        node *cursor = table[i];
        node *temp = table[i];

        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(temp);
            temp = cursor;
        }
    }
    return true;
}
