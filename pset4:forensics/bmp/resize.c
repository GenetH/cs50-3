/**
 * resize.c
 *
 * Fanney Zhu
 * fanneyzhu@college.harvard.edu
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes 24-bit uncompressed BMPs by a factor of n
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // convert string to int
    int n = atoi(argv[1]);
    
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
    
    // ensure n is a positive integer less than or equal to 100
    if (n < 1 || n > 100)
    {
        fclose(inptr);
        fclose(outptr);
        printf("Invalid: Please input positive integer less than or equal to 100.\n");
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // store padding of infile for scanline
    int infilepadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // store infile's biWidth and biHeight
    int infilewidth = bi.biWidth;
    int infileheight = bi.biHeight;
    
    // update outfile's biWidth and biHeight
    bi.biWidth = n * bi.biWidth;
    bi.biHeight = n * bi.biHeight;
    
    // determine padding for outfile for scanlines
    int outfilepadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // update outfile's biSizeImage
    bi.biSizeImage = ((bi.biWidth * abs(bi.biHeight)) * sizeof(RGBTRIPLE)) + 
                       (outfilepadding * abs(bi.biHeight));
    
    // update outfiles bfSize
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + 
                sizeof(BITMAPINFOHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFO HEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, height = abs(infileheight); i < height; i++)
    {
        // temporary storage for pixels in an array for entire scanline
        RGBTRIPLE scanline[bi.biWidth];
        
        // iterate over pixels in scanline
        for (int j = 0; j < infilewidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            for (int k = 0; k < n; k++)
            {
                // need to move index so you don't overwrite previous entries
                scanline[j * n + k] = triple;
            }
        }
        
        // skip over padding, if any
        fseek(inptr, infilepadding, SEEK_CUR);
        
        // write array n times
        for (int l = 0; l < n; l++)
        {
            fwrite(&scanline, sizeof(scanline), 1, outptr);

            // add padding
            for (int k = 0; k < outfilepadding; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
