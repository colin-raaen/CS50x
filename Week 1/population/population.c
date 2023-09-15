#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for start size
    int n;
    do
    {
        n = get_int("Start Size: ");
    }
    while (n < 9);

    //Prompt for end size
    int m;
    do
    {
        m = get_int("Ending Size: ");
    }
    while (m < n);

    //Calculate number of years until we reach threshold
    int new_pop = n;
    int years_req = 0;

    while (new_pop < m)
    {
        new_pop = (new_pop + (new_pop / 3) - (new_pop / 4));
        years_req++;
    }

    //Print number of years
    printf("Years: %i\n", years_req);
}
