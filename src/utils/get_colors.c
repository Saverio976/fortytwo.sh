/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** get color output escape sequence
*/

#include <stddef.h>
#include "my_strings.h"

static const char *key_light[] = {
    "green",
    "red",
    "blue",
    "cyan",
    "yellow",
    "purple",
    "gray"
};
static const char *value_light[] = {
    "\033[1;32m",
    "\033[1;31m",
    "\033[1;34m",
    "\033[1;36m",
    "\033[1;33m",
    "\033[1;35m",
    "\033[0;37m"
};

static const char *key_dark[] = {
    "green",
    "red",
    "blue",
    "cyan",
    "orange",
    "purple",
    "gray"
};
static const char *value_dark[] = {
    "\033[0;32m",
    "\033[0;31m",
    "\033[0;34m",
    "\033[0;36m",
    "\033[0;33m",
    "\033[0;35m",
    "\033[1;30m"
};

const char *get_light_color(const char *key)
{
    for (int i = 0; key_light[i] != NULL; i++) {
        if (my_strcmp(key, key_light[i]) == 0) {
            return (value_light[i]);
        }
    }
    return ("");
}

const char *get_color(const char *key)
{
    for (int i = 0; key_light[i] != NULL; i++) {
        if (my_strcmp(key, key_dark[i]) == 0) {
            return (value_dark[i]);
        }
    }
    return ("");
}

const char *get_reset(void)
{
    return ("\033[0m");
}
