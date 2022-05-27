/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** react to key in input
*/

#include <stdbool.h>
#include <unistd.h>
#include "my_puts.h"
#include "my_strings.h"
#include "mysh.h"
#include "mysh_struct.h"

//TODO: itter through history
bool use_key_up(shell_t *shell)
{
    if (shell->last_input == NULL) {
        return (false);
    }
    my_printf("\nHistory arrow not inplemented...\n");
    if (isatty(0)) {
        print_prompt(shell);
        my_putstr(shell->last_input);
    }
    return (false);
}

//TODO: complete binary/path
bool use_key_tab(shell_t *shell)
{
    if (shell->last_input == NULL) {
        return (false);
    }
    my_printf("\nCompletion not inplemented...\n");
    if (isatty(0)) {
        print_prompt(shell);
        my_putstr(shell->last_input);
    }
    return (false);
}

bool use_key_ctrld(shell_t *shell)
{
    if (shell->last_input == NULL) {
        shell->is_end = true;
        return (true);
    }
    my_printf("\nCompletion not inplemented...\n");
    if (isatty(0)) {
        print_prompt(shell);
        my_putstr(shell->last_input);
    }
    return (false);
}

bool use_key_backspace(shell_t *shell)
{
    if (my_strlen(shell->last_input) <= 0) {
        return (false);
    }
    my_putchar('\b');
    my_putchar(' ');
    my_putchar('\b');
    shell->last_input[my_strlen(shell->last_input) - 1] = '\0';
    return (false);
}
