#include <stdio.h>
#include <cs50.h>
#include <math.h>

//fewest number of coins for change

int main (void)
{
    //ask how much change is owed
    float dollars;
    do
    {
        printf("How much change do I owe you?\n");
        dollars = GetFloat();
    }
    while (dollars < 0);
    
    //convert dollars to cents and round number
    int cents;
    cents = round(100*dollars);
    
    //keep track of how many coins used
    int coins=0;
    int value=0;
    

    //quarters used
    while (cents >= 25)
    {
       value=cents/25;
       cents=cents%25;
       coins=coins+value;
    }
    
    
    //dimes used
    while (cents >= 10)
    {
       value=cents/10;
       cents=cents%10;
       coins=coins+value;
    }
    
    //nickels used
    while (cents >= 5)
    {
       value=cents/5;
       cents=cents%5;
       coins=coins+value;
    }
    
    //pennies used
    while (cents >= 1)
    {
       value=cents/1;
       cents=cents%1;
       coins=coins+value;
    }

    
    //print number of coins used
    printf("%i\n", coins);
}
