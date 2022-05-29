/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** print help
*/

#include <stddef.h>
#include "mysh.h"
#include "my_puts.h"

static char help_message[8][100] = {
    "DESCRIPTION:",
    "\treproduce a minishell with redirections (`|`, `>`, `>>`, `<`, `<<`)",
    "\tcompletion with `tab` and command history with arrow up and down",
    "\tyou can use arrow left and right to edit your line",
    "\t you can specify a file to take as stdin",
    "OPTIONS:",
    "\t-h\tprint this message",
    "\t-b file\tread this file instead of stdin"
};

int print_help(const char exe[])
{
    my_printf("USAGE: %s [[-b file] | file]\n", exe);
    for (int i = 0; i < 4; i++) {
        my_putstr(help_message[i]);
        my_putchar('\n');
    }
    return (0);
}
