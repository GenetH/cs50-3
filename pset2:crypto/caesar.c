/****************************************************************************
 * greedy.c
 *
 * Fanney Zhu
 * fanneyzhu@college.harvard.edu
 *
 * Computer Science 50
 * Problem Set 2
 *
 *
 * Caesar's Cipher
 ***************************************************************************/

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define ALPHABET 26

int main(int argc, string argv[])
{
    int k = 0;
  
    /* must accept a single command-line argument 
     * if program is executed without any or more than one 
     * yell at user and return 1
     * else, continue by return 0
     * makes sure k is a non-negative integer
	 */
    if (argc != 2 || k < 0)
    {
        printf("Try again\n");
        return 1;
    }
    
    // convert string k into int
    k = atoi(argv[1]);
    
    // prompt user for plaintext
    string plaintext = GetString();
    
    // produce ciphertext
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // preserve uppercase
        if (isupper(plaintext[i]))
        {
            printf("%c", (plaintext[i] + k - 'A') % ALPHABET + 'A');
        }   
        
        // preserves lowercase
        if (islower(plaintext[i]))
        {
            printf("%c", (plaintext[i] + k - 'a') % ALPHABET + 'a');
        }
        
        // dont shift non-letters
        if (!isalpha(plaintext[i]))
        {
            printf("%c", plaintext[i]);
        }
    }
    
    // new line
    printf("\n");
    
    return 0;
}
