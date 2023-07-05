#include "helpers.h"
#include <math.h>
#include <cs50.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int gray = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtRed = gray;
            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtGreen = gray;
        }
    }
    return;
}
// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {

            // sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
            //sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
            //sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;


            float sepiaRed = round(.393 * red + .769 * green + .189 * blue);
            float sepiaGreen = round(.349 * red + .686 * green + .168 * blue);
            float sepiaBlue = round(.272 * red + .534 * green + .131 * blue);

            image[i][j].rgbtRed= fmin(255,sepiaRed);
            image[i][j].rgbtGreen = fmin(255,sepiaGreen);
            image[i][j].rgbtBlue = fmin(255,sepiaBlue);

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        int tempwidth = 0;
        for(int j = width - 1; j >= 0; j--,tempwidth++)
        {
            temp[i][tempwidth] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    // temp into image

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int count = 0;

            int rowblur [] = {i - 1, i , i + 1};
            int columblur [] = {j - 1, j, j + 1};
            float Red = 0;
            float Green = 0;
            float Blue = 0;

            for (int r = 0; r < 3; r++)
            {
                for(int c = 0; c < 3; c++)
                {
                    int newrow = rowblur[r];
                    int newcol= columblur[c];

                    if(newrow >= 0 && newrow < height && newcol >=0 && newcol < width)
                    {
                        RGBTRIPLE square = image[newrow][newcol];
                        Red += square.rgbtRed;
                        Green += square.rgbtGreen;
                        Blue += square.rgbtBlue;
                        count++;
                    }

                }
            }

            temp[i][j].rgbtRed = round(Red/count);
            temp[i][j].rgbtBlue = round(Blue/count);
            temp[i][j].rgbtGreen = round(Green/count);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
            {
                image[i][j] = temp[i][j];
            }
    }
    return;
}
