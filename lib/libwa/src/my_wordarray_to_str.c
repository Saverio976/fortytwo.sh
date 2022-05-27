/*
** EPITECH PROJECT, 2022
** LIBMY
** File description:
** str to word array
*/

#include "my_strings.h"
#include "my_wordarray.h"
#include <stddef.h>

char *my_wordarray_to_str(char **wordarray)
{
    int i = 0;
    int len = my_wordarray_size(wordarray);
    int max = my_wordarray_len(wordarray);
    char *str = my_calloc(len);

    if (wordarray == NULL)
        return (NULL);
    while (i < max) {
        str = my_strcat(str, wordarray[i]);
        if (i < max - 1)
            str = my_strcat(str, " ");
        i++;
    }
    str = my_strcat(str, "\0");
    return (str);
}
