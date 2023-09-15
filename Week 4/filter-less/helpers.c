#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int grayscale;
    //for every row
    for (int i = 0, n = height; i < n; i++)
    {
        //for every column
        for (int j = 0, m = width; j < m; j++)
        {
            //calculate grayscale and assign
            grayscale = round(((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0));
            image[i][j].rgbtBlue = grayscale;
            image[i][j].rgbtGreen = grayscale;
            image[i][j].rgbtRed = grayscale;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int newSepiaRed;
    int newSepiaGreen;
    int newSepiaBlue;
    //for every row
    for (int i = 0, n = height; i < n; i++)
    {
        //for every column
        for (int j = 0, m = width; j < m; j++)
        {
            //calculate sepia values
            newSepiaRed = round((.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) + (.189 * image[i][j].rgbtBlue));
            newSepiaGreen = round((.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) + (.168 * image[i][j].rgbtBlue));
            newSepiaBlue = round((.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) + (.131 * image[i][j].rgbtBlue));

            //if new Sepia value is above 255, assign to 255
            if (newSepiaRed > 255)
            {
                newSepiaRed = 255;
            }
            if (newSepiaGreen > 255)
            {
                newSepiaGreen = 255;
            }
            if (newSepiaBlue > 255)
            {
                newSepiaBlue = 255;
            }

            //assign new values
            image[i][j].rgbtRed = newSepiaRed;
            image[i][j].rgbtGreen = newSepiaGreen;
            image[i][j].rgbtBlue = newSepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //for every row
    for (int i = 0, n = height; i < n; i++)
    {
        //for every column
        for (int j = 0, m = width; j < (m - (j + 1)); j++)
        {
            //swap red values
            uint8_t tempred;
            tempred = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][m - (j + 1)].rgbtRed;
            image[i][m - (j + 1)].rgbtRed = tempred;

            //swap green values
            uint8_t tempgreen;
            tempgreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][m - (j + 1)].rgbtGreen;
            image[i][m - (j + 1)].rgbtGreen = tempgreen;

            //swap blue values
            uint8_t tempBlue;
            tempBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][m - (j + 1)].rgbtBlue;
            image[i][m - (j + 1)].rgbtBlue = tempBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //array to copy pixel values into
    RGBTRIPLE COPY[height][width];

    //for every row
    for (int i = 0, n = height; i < n; i++)
    {
        //for every column
        for (int j = 0, m = width; j < m; j++)
        {
            //if corner piece calculate new values
            if (i == 0 && j == 0)
            {
                COPY[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed +
                                            image[i + 1][j + 1].rgbtRed) / 4.0);
                COPY[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                              image[i + 1][j + 1].rgbtGreen) / 4.0);
                COPY[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                                             image[i + 1][j + 1].rgbtBlue) / 4.0);
            }
            //if corner piece calculate new values
            else if (i == 0 && j == (width - 1))
            {
                COPY[i][j].rgbtRed = round((image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i + 1][j - 1].rgbtRed +
                                            image[i + 1][j].rgbtRed) / 4.0);
                COPY[i][j].rgbtGreen = round((image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen +
                                              image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen) / 4.0);
                COPY[i][j].rgbtBlue = round((image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue +
                                             image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue) / 4.0);
            }
            //if corner piece calculate new values
            else if (i == (height - 1) && j == 0)
            {
                COPY[i][j].rgbtRed = round((image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                                            image[i][j].rgbtRed + image[i][j + 1].rgbtRed) / 4.0);
                COPY[i][j].rgbtGreen = round((image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                              image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen) / 4.0);
                COPY[i][j].rgbtBlue = round((image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j].rgbtBlue +
                                             image[i][j + 1].rgbtBlue) / 4.0);
            }
            //if corner piece calculate new values
            else if (i == (height - 1) && j == (width - 1))
            {
                COPY[i][j].rgbtRed = round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed +
                                            image[i][j - 1].rgbtRed + image[i][j].rgbtRed) / 4.0);
                COPY[i][j].rgbtGreen = round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                              image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen) / 4.0);
                COPY[i][j].rgbtBlue = round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                             image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue) / 4.0);
            }
            //if EDGE piece calculate new values
            else if (i == 0 && (0 < j < (m - 1)))
            {
                COPY[i][j].rgbtRed = round((image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                                            image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0);
                COPY[i][j].rgbtGreen = round((image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                              image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.0);
                COPY[i][j].rgbtBlue = round((image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                                             image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.0);
            }
            //if EDGE piece calculate new values
            else if ((0 < i < (n - 1)) && j == 0)
            {
                COPY[i][j].rgbtRed = round((image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j].rgbtRed +
                                            image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0);
                COPY[i][j].rgbtGreen = round((image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                              image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                              image[i + 1][j + 1].rgbtGreen) / 6.0);
                COPY[i][j].rgbtBlue = round((image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                             image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                                             image[i + 1][j + 1].rgbtBlue) / 6.0);
            }
            //if EDGE piece calculate new values
            else if ((0 < i < (n - 1)) && j == (m - 1))
            {
                COPY[i][j].rgbtRed = round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed +
                                            image[i][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed) / 6.0);
                COPY[i][j].rgbtGreen = round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                              image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                                              image[i + 1][j].rgbtGreen) / 6.0);
                COPY[i][j].rgbtBlue = round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                             image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                                             image[i + 1][j].rgbtBlue) / 6.0);
            }
            //if EDGE piece calculate new values
            else if (i == (n - 1) && (0 < j < (m - 1)))
            {
                COPY[i][j].rgbtRed = round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed +
                                            image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed) / 6.0);
                COPY[i][j].rgbtGreen = round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                              image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen +
                                              image[i][j + 1].rgbtGreen) / 6.0);
                COPY[i][j].rgbtBlue = round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                             image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue +
                                             image[i][j + 1].rgbtBlue) / 6.0);
            }
            //else calculate middle value
            else
            {
                COPY[i][j].rgbtRed = round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed +
                                            image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i][j].rgbtRed +
                                            image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed +
                                            image[i + 1][j + 1].rgbtRed) / 9.0);
                COPY[i][j].rgbtGreen = round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                              image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen +
                                              image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                              image[i + 1][j + 1].rgbtGreen) / 9.0);
                COPY[i][j].rgbtBlue = round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                             image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue +
                                             image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                                             image[i + 1][j + 1].rgbtBlue) / 9.0);
            }
        }
    }
    //assign new values from COPY array
    for (int i = 0, n = height; i < n; i++)
    {
        for (int j = 0, m = width; j < m; j++)
        {
            image[i][j] = COPY[i][j];
        }
    }

    return;
}
