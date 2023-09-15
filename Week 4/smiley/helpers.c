#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    //for every row of pixel array
    for (int i = 0, n = height; i < n; i++)
    {
        //for every column of pixel array
        for (int j = 0, m = width; j < m; j++)
        {
            //if pixel is black
            if (image[i][j].rgbtBlue == 0 && image[i][j].rgbtGreen == 0 && image[i][j].rgbtRed == 0)
            {
                //assign redscale
                image[i][j].rgbtBlue = 0;
                image[i][j].rgbtGreen = 0;
                image[i][j].rgbtRed = 255;
            }

        }
    }
    return;
}
