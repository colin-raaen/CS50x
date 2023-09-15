#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //ask for users name
    string name = get_string("What is your name? \n");
    //say hello user
    printf("hello, %s\n", name);
}