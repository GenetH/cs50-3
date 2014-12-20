/***************************************************************************
 *
 * generate.c
 *
 * Fanney Zhu
 * fanneyzhu@college.harvard.edu
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 ***************************************************************************/
 
// standard libraries
#define _XOPEN_SOURCE
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    // Makes sure program receives either one or two 
    // command-line arguments. If not, prompt user again.
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // First command-line argument number is initially 
    // stored as a string. Convert data type of number 
    // from string to int using atoi().
    int n = atoi(argv[1]);

    // If the user inputs two command-line arguments
    // convert the data type of the "seed" (second 
    // command-line argument) from string to long int 
    // using atoi(). Then, input this seed into srand48() 
    // to generate pseudo-random numbers using linear 
    // congruential algorithm and 48-bit integer arithmetic.
    // If the user doesn't input a second command-line 
    // argument, input time, which will be different every 
    // time (since time is constantly changing), into 
    // srand48() to generate pseudo-random numbers
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }

    // Print a different randomly generated number times 
    // the constant, LIMIT = 65536, on each line n times. 
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
