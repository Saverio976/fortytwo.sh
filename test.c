#include <stdio.h>
int main(int ac, char **argv)
{
    if (ac == 1)
        return (0);
    printf("%s\n", argv[1]);
    return (0);
}