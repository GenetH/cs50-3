/****************************************************************************
 * mario.c
 *
 * Fanney Zhu
 * fanneyzhu@college.harvard.edu
 *
 * Computer Science 50
 * Problem Set 1
 *
 *
 * Build Mario's half-pyramid with #
 ***************************************************************************/

#include <stdio.h>
#include <cs50.h>

int main (void)
{
    // height is a non-negative integer no greater than 23
    int height;
    do
    {
        printf("Height:\n");
        height = GetInt();
    }
    while (height < 0 || height > 23);
    
    //construct pyramid along left-side
    for (int i = 0; i < height; i++)
    {
        //print spaces
        for (int j = height - i; j>1; j--)
        {
            printf(" ");
        }
        
        //print #
        for (int k = 0; k < i+2; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
