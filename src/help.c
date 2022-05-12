/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** print help
*/

#include <stddef.h>
#include "mysh.h"
#include "my_puts.h"

static char help_message[4][100] = {
    "DESCRIPTION:",
    "\treproduce a minishell with redirections (`|`, `>`, `>>`, `<`, `<<`)",
    "OPTIONS:",
    "\t-h\tprint this message",
};

int print_help(const char exe[])
{
    my_printf("USAGE: %s\n", exe);
    for (int i = 0; i < 4; i++) {
        my_putstr(help_message[i]);
        my_putchar('\n');
    }
    return (0);
}
