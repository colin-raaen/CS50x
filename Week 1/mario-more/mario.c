#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //prompt user for pyramid height between 1 and 8
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    //for each row
    for (int i = 0; i < n; i++)
    {
        //for each column left-aligned
        for (int j = 2; j <= (n - i); j++)
        {
            //print space
            printf(" ");
        }

        //for each column right-aligned
        for (int k = 0; k <= i; k++)
        {
            //print a brick
            printf("#");
        }
        printf("  ");

        //for each column left-aligned
        for (int l = 0; l <= i; l++)
        {
            //print a brick
            printf("#");
        }
        //move to next row
        printf("\n");
    }
}