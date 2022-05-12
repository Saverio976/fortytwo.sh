/*
** EPITECH PROJECT, 2022
** LIBFS
** File description:
** get only the filename of a path
*/

#include <stddef.h>
#include "my_macro.h"
#include "my_strings.h"

const char *get_filename(const char *path, char delim)
{
    int last = 0;
    int is_start_file = FALSE;

    if (path == NULL) {
        return (NULL);
    }
    last = my_strlen(path);
    if (path[last - 1] == delim && path[last - 2] != '\\') {
        return (NULL);
    }
    for (int i = last - 1; is_start_file == FALSE; i--) {
        if (i == 0 || (path[i] == delim && path[i - 1] != '\\')) {
            return (path + i + 1);
        }
    }
    return (NULL);
}
