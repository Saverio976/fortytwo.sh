/*
** EPITECH PROJECT, 2021
** LIBMY
** File description:
** compare two str an return 0 if eq
*/

#include "my_macro.h"
#include "my_strings.h"

int my_strcmp(char const *s1, char const *s2)
{
    char a;
    char b;
    int lengths[2] = {0, 0};
    int sub = 0;
    int max = 0;

    lengths[0] = my_strlen(s1);
    lengths[1] = my_strlen(s2);
    if (lengths[0] == -1 || lengths[1] == -1) {
        return (84);
    }
    max = MAX(lengths[0], lengths[1]);
    for (int i = 0; sub == 0 && i < max; i++) {
        a = (i >= lengths[0]) ? '\0' : s1[i];
        b = (i >= lengths[1]) ? '\0' : s2[i];
        sub = a - b;
    }
    return (sub);
}
