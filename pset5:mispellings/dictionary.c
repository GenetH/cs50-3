/****************************************************************************
 * dictionary.c
 *
 * Fanney Zhu
 * fanneyzhu@college.harvard.edu
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// define size of hashTable
#define HASHSIZE 94007

// struct for node
typedef struct node
{
    char str[LENGTH + 1];
    struct node* next;
}
node;

// declare hashTable
node* hashTable[HASHSIZE];

// declare loadedSize
int loadedSize = 0;

/**
 * Hashfunction: djb2 from (http://www.cse.yorku.ca/~oz/hash.html)
 */
unsigned int hash(char *str)
{
    unsigned int hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % HASHSIZE;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // temporary storage for word converted to lowercase
    char* lowWord = malloc(sizeof(char)*(strlen(word) + 1));
    
    // copy word into lowWord
    strcpy(lowWord, word);
    
    // convert characters to lowercase if not already
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        lowWord[i] = tolower(word[i]);
    }
    
    // determine hashIndex of lowWord using hashFunction
    int hashIndex = hash(lowWord);
    
    // temporary storage for pointer to hashTable
    node* temp = hashTable[hashIndex];
    
    // as long as the pointer is not NULL
    while (temp != NULL)
    {
        // if strings match, return true
        if (strcmp(lowWord, temp -> str) == 0)
        {
            return true;
        } 
        // else follow pointer to next node     
        temp = temp -> next;        
    }
    
    // free allocated memory from heap
    free(lowWord);
    
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open dictionary
    FILE* file = fopen(dictionary, "r");
    
    // check if dictionary was successfully opened
    if (file == NULL)
    {
        fclose(file);
        return false;
    }
    
    // temporary variable to store dictionary word
    char* dictWord = malloc(sizeof(char) * (LENGTH + 1));
    
    // read one string at a time until end of file is reached
    while (fscanf(file, "%s", dictWord) != EOF)
    {
        // create a new node
        node* new = malloc(sizeof(node));
        
        // store the dictionary word in the new node
        strcpy(new -> str, dictWord);
        
        // determine the hashIndex
        int hashIndex = hash(dictWord);
        
        // if pointer in hashTable[hashIndex] is null, start a linked list
        if (hashTable[hashIndex] == NULL)
        {
            hashTable[hashIndex] = new;
            new -> next = NULL;
        }
        // if linked list already exists, insert into linked list
        else
        {
            new -> next = hashTable[hashIndex];
            hashTable[hashIndex] = new;
        }
        
        // increment loadedSize to count number of words loaded
        loadedSize++;
    }
    
    // free allocated memory from heap
    free(dictWord);

    // close dictionary file
    fclose(file);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return loadedSize;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // iterate through the entire hashTable
    for (int i = 0; i < HASHSIZE; i++)
    {
        // declare and initiate cursor to point where hashTable[i] is pointing
        node* cursor = hashTable[i];
        
        // continue as long as cursor is not NULL
        while (cursor != NULL)
        {
            // declare and initiate temp to point where the cursor -> next is pointer
            node* temp = cursor -> next;
            
            // free what the cursor is pointing to
            free(cursor);
            
            // set the cursor to point where temp is pointing
            cursor = temp;           
        }
    }
    
    return true;
}
