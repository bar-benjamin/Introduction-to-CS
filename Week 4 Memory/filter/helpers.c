#include "helpers.h"
#include "math.h"
#include "string.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            // get original RGB values
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;
            
            // average RGB values to determine what shade of gray to make the new pixel
            int gray = round((red + green + blue) / 3.0);
            
            // equal values of red green and blue results a shade of gray
            image[i][j].rgbtRed = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtBlue = gray;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    
    for (int i = 0; i < height; ++i)
    {
        // iterate over half of the columns
        for (int j = 0; j < width / 2; ++j)
        {
            // swap pixels on the left side to the right, and vice versa.
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // The new value of each pixel would be the average of the values
    // of all of the pixels that are within 1 row and column of the original pixel
    RGBTRIPLE temp[height][width];
    
    // creates a copy of image to loop over
    memcpy(temp, image, sizeof(RGBTRIPLE) * height * width);
    
    for (int i = 0; i < height; ++i)
    {
        // iterate over half of the columns
        for (int j = 0; j < width; ++j)
        {
            int red = 0, green = 0, blue = 0, num_of_pixels = 0;
            
            // scanning the valid(withing bounds) neighbors around
            for (int k = -1; k <= 1; ++k) 
            {
                for (int l = -1; l <= 1; ++l) 
                {
                    if ((i + k >= 0) && (i + k <= height - 1) &&
                        (j + l >= 0) && (j + l <= width - 1))
                    {
                        // sum all the values of all pixels within 1 row and col
                        red += temp[i + k][j + l].rgbtRed;
                        green += temp[i + k][j + l].rgbtGreen;
                        blue += temp[i + k][j + l].rgbtBlue;
                        ++num_of_pixels;
                    }
                }
            }
            
            // blur the original pixels
            image[i][j].rgbtRed = round(red / (float) num_of_pixels);
            image[i][j].rgbtGreen = round(green / (float) num_of_pixels);
            image[i][j].rgbtBlue = round(blue / (float) num_of_pixels);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // The new value of each pixel would be the original multiplied by the
    // corresponding value in the Gx kernel, and take the sum of the resulting values
    RGBTRIPLE temp[height][width];
    int g_x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int g_y[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    
    // creates a copy of image to loop over
    memcpy(temp, image, sizeof(RGBTRIPLE) * height * width);
    
    for (int i = 0; i < height; ++i)
    {
        // iterate over half of the columns
        for (int j = 0; j < width; ++j)
        {
            int red_x = 0, green_x = 0, blue_x = 0;
            int red_y = 0, green_y = 0, blue_y = 0;
            
            // scanning the valid(withing bounds) neighbors around
            for (int k = -1; k <= 1; ++k) 
            {
                for (int l = -1; l <= 1; ++l) 
                {
                    if ((i + k >= 0) && (i + k <= height - 1) &&
                        (j + l >= 0) && (j + l <= width - 1))
                    {
                        // sum all the values of all pixels within 1 row and col
                        red_x += temp[i + k][j + l].rgbtRed * g_x[k + 1][l + 1];
                        green_x += temp[i + k][j + l].rgbtGreen * g_x[k + 1][l + 1];
                        blue_x += temp[i + k][j + l].rgbtBlue * g_x[k + 1][l + 1];
                            
                        red_y += temp[i + k][j + l].rgbtRed * g_y[k + 1][l + 1];
                        green_y += temp[i + k][j + l].rgbtGreen * g_y[k + 1][l + 1];
                        blue_y += temp[i + k][j + l].rgbtBlue * g_y[k + 1][l + 1];
                    }
                }
            }
            
            // applying Sobel filter algorithm
            int red = round(sqrt(pow(red_x, 2) + pow(red_y, 2)));
            int green = round(sqrt(pow(green_x, 2) + pow(green_y, 2)));
            int blue = round(sqrt(pow(blue_x, 2) + pow(blue_y, 2)));
            
            // blur the original pixels
            image[i][j].rgbtRed = red < 255 ? red : 255;
            image[i][j].rgbtGreen = green < 255 ? green : 255;
            image[i][j].rgbtBlue = blue < 255 ? blue : 255;
        }
    }
}
