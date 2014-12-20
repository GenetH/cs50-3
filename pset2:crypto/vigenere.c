/****************************************************************************
 * vigenere.c
 *
 * Fanney Zhu
 * fanneyzhu@college.harvard.edu
 *
 * Computer Science 50
 * Problem Set 2
 *
 *
 * Vigenere's Cipher
 ***************************************************************************/ 

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // must accept a single command-line argument 
    // if program is executed without any or more than one 
    // yell at user and return 1
    // else, continue by return 0
    if (argc != 2)
    {
        printf("Try again\n");
        return 1;
    }
    
    string k = argv[1];
    // makes sure k is composed entirely of alphabetical characters
    for (int i = 0, n = strlen(k); i < n; i++)
    {
        if (!isalpha(k[i]))
        {
            printf("Try again\n");
            return 1;
        }
    }
    
    // prompt user for plaintext
    string plaintext = GetString();
    
    // produce ciphertext
    int index = 0;
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // if plaintext is uppercase
        if (isupper(plaintext[i]))
        {
            // if keyword is uppercase
            if (isupper(k[index]))
            {
                printf("%c", (k[index] - 'A' + plaintext[i] - 'A') % 26 + 'A');
                index++;
            }
            // if keyword is lowercase
            else if (islower(k[index]))
            {
                printf("%c", (k[index] - 'a' + plaintext[i] - 'A') % 26 + 'A');
                index++;
            }
        }   
        
        // if plaintext is lowercase
        else if (islower(plaintext[i]))
        {
            // if keyword is uppercase
            if (isupper(k[index]))
            {
                printf("%c", (k[index] - 'A' + plaintext[i] - 'a') % 26 + 'a');
                index++;
            }
            // if keyword is lowercase
            else if (islower(k[index]))
            {
                printf("%c", (k[index] - 'a' + plaintext[i] - 'a') % 26 + 'a');
                index++;
            }
        }
        
        // dont shift non-letters
        else if (!isalpha(plaintext[i]))
        {
            printf("%c", plaintext[i]);
        }
        
        // reset index 
        if (index == strlen(k))
        {
            index = 0;
        }
    }
    
    // new line
    printf("\n");
    
    return 0;
}
