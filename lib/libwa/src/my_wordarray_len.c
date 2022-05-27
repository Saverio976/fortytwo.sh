/*
** EPITECH PROJECT, 2022
** LIBMY
** File description:
** get length of word array
*/

#include <stddef.h>

int my_wordarray_size(char **wordarray)
{
    int i = 0;
    int y = 0;

    if (wordarray == NULL)
        return (0);
    for (; wordarray[i] != NULL; i++)
        for(; wordarray[i][y] != '\0'; y++);
    return (y);
}

/**
** @brief get length of null terminated 2d array
** @param array
** @return 0 if array is null; else the length
**/
int my_wordarray_len(char *const *array)
{
    int i = 0;

    if (array == NULL) {
        return (0);
    }
    for (; array[i] != NULL; i++);
    return (i);
}
