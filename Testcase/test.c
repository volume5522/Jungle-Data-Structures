#include <stdio.h>

int no_return()
{
    return 1;
}
int main()
{
    int result = no_return();
    printf("Result=%d\n",result);
}