#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height = get_int("Height: ");
    while (height < 1 || height > 8) // validating the user input
    { 
        height = get_int("Height: ");
    }
    
    for (int row = 1; row <= height; ++row) // starts from row=1 so first line won't be empty (hashes < row)
    { 
        for (int spaces = 0; spaces < height - row; ++spaces) // calculate how many spaces to print for current row 
        {
            printf(" ");
        }
        
        int hashes; // row number = hashes number to print
        for (hashes = 0; hashes < row; ++hashes) // L.H.S hashes for current row 
        {
            printf("#");
        }
        printf("  "); // the spaces between the hashes on each side
        for (hashes = 0; hashes < row; ++hashes) // R.H.S hashes for current row
        {
            printf("#");
        }
        printf("\n"); // form the pyramid by going down a line
    }
}
