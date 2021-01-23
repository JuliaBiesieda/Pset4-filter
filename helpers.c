#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);
            // printf("average is %i\n", average);

            if (average > 255)
            {
                average = 255;
            }
            // printf("new average is %i\n", average);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            // printf("Value of red is %i, value of blue is %i, value of green is %i\n", average, average, average);


        }
    }
    //  printf("new value of red is %i\n", image[2][3].rgbtRed);
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    void swap(RGBTRIPLE * b, RGBTRIPLE * c);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j], &image[i][width - 1 - j]);
        }
    }

    return;
}

void swap(RGBTRIPLE *b, RGBTRIPLE *c)
{
    RGBTRIPLE temp1;
    RGBTRIPLE temp2;
    temp1 = *b;
    temp2 = *c;
    *b = temp2;
    *c = temp1;
}




// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new[height][width];

    // Loop through all the rows and columns of the img
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // set vars for counter and new colors
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            int counter = 0;

            // create new arrays to loop though a 3x3 square
            int row[] = {i - 1, i, i + 1};
            int column[] = {j - 1, j, j + 1};

            // start looping through rows of 3x3 square
            for (int f = 0; f < 3; f++)
            {
                //exclude row 0 and row height - q
                if (row[f] >= 0 && row[f] <= height - 1)
                {
                    // start looping through columns of 3x3 square
                    for (int s = 0; s < 3; s++)
                    {
                        // exclude columns 0 and width - 1
                        if (column[s] >= 0 && column[s] <= width - 1)
                        {
                            sumRed += image[row[f]][column[s]].rgbtRed;
                            sumGreen += image[row[f]][column[s]].rgbtGreen;
                            sumBlue += image[row[f]][column[s]].rgbtBlue;
                            counter++;
                        }
                    }
                }
            }

            new[i][j].rgbtRed = round((float)sumRed / counter);
            new[i][j].rgbtBlue = round((float)sumBlue / counter);
            new[i][j].rgbtGreen = round((float)sumGreen / counter);

        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new[i][j];
        }
    }

    return;
}
