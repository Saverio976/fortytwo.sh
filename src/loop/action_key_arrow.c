/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** action key of arrow
*/

#include <stdbool.h>
#include <unistd.h>
#include "my_puts.h"
#include "my_strings.h"
#include "mysh.h"
#include "mysh_struct.h"

//TODO: itter through history
bool use_key_up(shell_t *shell, __attribute__((unused)) int *cur_pos)
{
    if (shell->last_input == NULL) {
        return (false);
    }
    my_printf("\nHistory arrow Up not inplemented...\n");
    if (isatty(0)) {
        print_prompt(shell);
        my_putstr(shell->last_input);
    }
    return (false);
}

bool use_key_down(shell_t *shell, __attribute__((unused)) int *cur_pos)
{
    if (shell->last_input == NULL) {
        return (false);
    }
    my_printf("\nHistory arrow Down not inplemented...\n");
    if (isatty(0)) {
        print_prompt(shell);
        my_putstr(shell->last_input);
    }
    return (false);
}

bool use_key_left(__attribute__((unused)) shell_t *shell, int *cur_pos)
{
    if (*cur_pos <= 0) {
        return (false);
    }
    my_putchar('\b');
    *cur_pos -= 1;
    return (false);
}

bool use_key_right(shell_t *shell, int *cur_pos)
{
    if (my_strlen(shell->last_input) <= *cur_pos ||
            shell->last_input == NULL) {
        return (false);
    }
    my_putchar(shell->last_input[*cur_pos]);
    *cur_pos += 1;
    return (false);
}
