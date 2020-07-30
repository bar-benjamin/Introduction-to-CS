#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isJpeg(unsigned char bytes[])
{
    return (bytes[0] == 0xff) && (bytes[1] == 0xd8) && (bytes[2] == 0xff) && ((bytes[3] & 0xf0) == 0xe0);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    // open memory card "card.raw"
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("File could not be opened for reading\n");
        return 1;
    }
    
    int counter = 0;
    FILE *img = NULL;
    char filename[8];
    unsigned char bytes[512];
    
    //// read a block of memory to detect JPEG file until end of memory card
    while (!feof(file) && fread(bytes, sizeof(unsigned char), 512, file) != 0)
    {
        // found a new jpeg file - close the current one
        if (img != NULL && isJpeg(bytes))
        {
            // close current .jpg after finished writing to it
            fclose(img);
        }
        
        // look for begining of a JPEG file
        if (isJpeg(bytes))
        {
            // open a new JPEG file
            sprintf(filename, "%03d.jpg", counter++);
            img = fopen(filename, "w");
            
            // write 512 bytes until a new JPEG is found
            fwrite(bytes, sizeof(unsigned char), 512, img);
        }
        // if already found a JPEG - keep writing to it
        else if (img != NULL)
        {
            fwrite(bytes, sizeof(unsigned char), 512, img);
        }
    }
    
    // closing the last image
    fclose(img);
    
    fclose(file);
    return 0;
}
