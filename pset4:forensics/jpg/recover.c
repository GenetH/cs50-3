/**
 * recover.c
 *
 * Fanney Zhu
 * fanneyzhu@college.harvard.edu
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// number of bytes in one block
#define BLOCK 512

// size of title
#define SIZE 8

// assign 8 bits to BYTE
typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
    // open card.raw
    FILE* file = fopen("card.raw", "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    
    // storage for block
    BYTE buffer[BLOCK];
    
    // storage for number of jpegs
    int jpegNum = 0;
    
    // storage for title
    char title[SIZE];
    
    // read one block at a time until end of file is reached
    while(fread(&buffer, sizeof(buffer), 1, file) == 1)  
    {
        // look for first signature
        while (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff 
            && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            // open jpeg file
            sprintf(title, "%03i.jpg", jpegNum);
            FILE* img = fopen(title, "w");
            if (img == NULL)
            {
                fclose(img);
                fprintf(stderr, "Could not create image.\n");
                return 3;
            }
            
            // write to image
            fwrite(&buffer, sizeof(buffer), 1, img);
        
            // keep writing if signature not identified
            while(fread(&buffer, sizeof(buffer), 1, file) == 1)
            {
                if (!(buffer[0] == 0xff && buffer[1] == 0xd8 && 
                buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1)))
                {
                    fwrite(&buffer, sizeof(buffer), 1, img);
                }
                else
                {
                    // close image
                    fclose(img);
                    
                    // increment number of jpeg by 1
                    jpegNum++;
                    
                    // exit loop
                    break;
                }
            }  
        }   
    }
    
    return 0;
}
