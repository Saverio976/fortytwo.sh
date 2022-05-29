/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** redirect utils function to read from file
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "macros.h"

int redirect_input(const char *file)
{
    int saved_input = -1;
    int fd = 0;

    fd = open(file, O_RDONLY);
    if (fd <= 0) {
        return (-1);
    }
    saved_input = dup(0);
    dup2(fd, 0);
    freopen(file, "r", stdin);
    close(fd);
    return (saved_input);
}

int ends_redirect_input(int saved_input)
{
    if (saved_input == -1) {
        return (0);
    }
    dup2(saved_input, 0);
    freopen(INPUT_STDIN_PATH, "r", stdin);
    close(saved_input);
    return (0);
}
