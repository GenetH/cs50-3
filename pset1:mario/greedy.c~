/****************************************************************************
 * greedy.c
 *
 * Fanney Zhu
 * fanneyzhu@college.harvard.edu
 *
 * Computer Science 50
 * Problem Set 1
 *
 *
 * Calculate the fewest number of coins needed
 ***************************************************************************/

#include <stdio.h>
#include <cs50.h>
#include <math.h>

#define QUARTER 25
#define DIME 10
#define NICKEL 5
#define PENNY 1

int main (void)
{
    float dollars;
    
    // ask how much change is owed
    // can't have negative change
    do
    {
        printf("How much change do I owe you?\n");
        dollars = GetFloat();
    }
    while (dollars < 0);
    
    // convert dollars to cents and round number
    int cents;
    cents = round(100*dollars);
    
    // keep track of how many coins used
    int coins = 0;
    
    // quarters used
    while (cents >= QUARTER)
    {
       cents = cents-QUARTER;
       coins++;
    }
    
    
    // dimes used
    while (cents >= DIME)
    {
        cents = cents-DIME;
        coins++;
    }
    
    // nickels used
    while (cents >= NICKEL)
    {
        cents = cents-NICKEL;
        coins++;
    }
    
    // pennies used
    while (cents >= PENNY)
    {
        cents = cents-PENNY;
        coins++;
    }
    
    // print number of coins used
    printf("%i\n", coins);
}
