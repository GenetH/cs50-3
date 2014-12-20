/**
 * helpers.c
 *
 * Fanney Zhu
 * fanneyzhu@college.harvard.edu
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */

bool search(int value, int values[], int n)
{
    // return false if there is nothing in the list
    if (n < 1)
    {
        return false;
    }
    
    // search if there is something in the list
    int min = 0;
    int max = n - 1;
    
    while (min <= max)
    {
        int mid = (min + max)/2;
        if (value == values[mid])
        {
            return true;
        }
        else if (value < values[mid])
        {
            max = mid - 1;
        }
        else if (value > values[mid])
        {
            min = mid + 1;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // if less than 2 things in list, return list.  
    if (n < 2)
    {
        return;
    }
    
    // else, selection sort: find the minimum element and swap into ordered list
    else
    {
        for (int i = 0; i < n; i++)
        {
            int min = values[i];
            int index = i;
            for (int j = i + 1; j < n; j++)
            {
                if (values[j] < min)
                {
                    min = values[j];
                    index = j;
                }
            }
            if (index != i)
            {
                values[index] = values[i];
                values[i] = min;
            }
        }
    }
    return;
}
