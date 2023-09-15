#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open input file
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 2;
    }
    //create output file
    FILE *outptr = NULL;

    //create buffer
    BYTE *buffer = malloc(BLOCK_SIZE);
    if (buffer == NULL)
    {
        printf("Not enough memory\n");
        fclose(inptr);
        return 4;
    }
    char *output_name = malloc(8 * sizeof(char));
    if (output_name == NULL)
    {
        printf("Not enough memory\n");
        fclose(inptr);
        return 6;
    }
    int JPEG_counter = 0;

    while (fread(buffer, 1, BLOCK_SIZE, inptr) == BLOCK_SIZE)
    {
        // Ensure infile is a JPEG file header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //close output file if its open
            if (outptr != NULL)
            {
                fclose(outptr);
            }

            //Create new JPEG file
            sprintf(output_name, "%03i.jpg", JPEG_counter);

            //Open new JPEG file
            outptr = fopen(output_name, "w");

            if (outptr == NULL)
            {
                printf("could not create jpeg file\n");
                return 5;
            }

            //write to new JPEG file
            fwrite(buffer, 1, BLOCK_SIZE, outptr);

            JPEG_counter += 1;
        }
        else if (JPEG_counter > 0)
        {
            //write to new JPEG file
            fwrite(buffer, 1, BLOCK_SIZE, outptr);
        }
    }
    //close card.raw and last JPEG
    free(buffer);
    free(output_name);
    fclose(outptr);
    fclose(inptr);
    return 0;
}