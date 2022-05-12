/*
** EPITECH PROJECT, 2021
** LIBFILE
** File description:
** open a file in read only
*/

#include <fcntl.h>

int fs_open_ronly(char const *path)
{
    return (open(path, O_RDONLY));
}
