// Implements a dictionary's functionality

#include <stdbool.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

const unsigned int N = 
    186019; // rule of thumb: hash table size should be 1.3 times a prime number of elements it's going to contain

node *table[N];

// hash function by djb2
// link: http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    for (const char *c = word; *c != '\0'; ++c)
    {
        hash = ((hash << 5) + hash) + tolower(*c);
    }
    return hash % N;
}

// checks if a word exists in the dictionary
bool check(const char *word)
{
    unsigned int index = hash(word);
    node *head = table[index];
    while (head != NULL)
    {
        if (strcasecmp(head->word, word) == 0)
        {
            return true;
        }
        head = head->next;
    }
    return false;
}

// finds the number of words in the dictionary
unsigned int size(void)
{
    unsigned int counter = 0;
    node *head = NULL;
    for (int i = 0; i < N; ++i)
    {
        head = table[i];
        while (head != NULL)
        {
            ++counter;
            head = head->next;
        }
    }
    return counter;
}

// unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; ++i)
    {
        node *head = table[i];
        while (head != NULL)
        {
            node *temp = head;
            head = head->next;
            free(temp);
        }
    }
    return true;
}

// loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Failed to open %s\n", dictionary);
        return false;
    }

    while (true)
    {
        node *new_node = malloc(sizeof(*new_node));
        if (new_node == NULL)
        {
            printf("Memory allocation has failed\n");
            return false;
        }
        
        if (fscanf(dict, "%s", new_node->word) == EOF)
        {
            free(new_node);
            break;
        }
        new_node->next = NULL;

        int index = hash(new_node->word);
        node *head = table[index];

        // first node insertion
        if (head == NULL)
        {
            table[index] = new_node;
        }
        else // collision
        {
            new_node->next = table[index]; // connect new_node -> table
            table[index] = new_node; // update table to be new_node
        }
    }
    
    fclose(dict);
    return true;
}
