/*
** EPITECH PROJECT, 2022
** LIBMY
** File description:
** get length of word array
*/

#include <stddef.h>

/**
** @brief get cumulative size of all strings
** @param array
** @return 0 if array is null; else the size of the array
**/
int my_wordarray_size(char **wordarray)
{
    int i = 0;
    int result = 0;

    if (wordarray == NULL)
        return (0);
    for (; wordarray[i] != NULL; i++)
        for(int y = 0; wordarray[i][y] != '\0'; y++)
            result++;
    return (result);
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
