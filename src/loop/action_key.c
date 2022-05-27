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

void display_input(shell_t *shell, int *current_pos)
{
    for (int i = 0; i < *current_pos - 1; i++) {
        my_putchar('\b');
        my_putchar(' ');
        my_putchar('\b');
    }
    my_putstr(shell->last_input);
    for (int i = my_strlen(shell->last_input); i > *current_pos; i--) {
        my_putchar('\b');
    }
}

//TODO: complete binary/path
bool use_key_tab(shell_t *shell, __attribute__((unused)) int *cur_pos)
{
    if (my_strlen(shell->last_input) <= 0) {
        return (false);
    }
    my_printf("\nCompletion not inplemented...\n");
    if (isatty(0)) {
        print_prompt(shell);
        my_putstr(shell->last_input);
    }
    return (false);
}

bool use_key_ctrld(shell_t *shell, __attribute__((unused)) int *cur_pos)
{
    if (my_strlen(shell->last_input) <= 0) {
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

bool use_key_backspace(shell_t *shell, int *cur_pos)
{
    int tmp_len = my_strlen(shell->last_input);

    if (tmp_len <= 0 || *cur_pos <= 0) {
        return (false);
    }
    for (int i = 0; i < tmp_len; i++) {
        my_putchar('\b');
        my_putchar(' ');
        my_putchar('\b');
    }
    *cur_pos -= 1;
    for (int i = 0; i < tmp_len - 2; i++) {
        my_putchar(' ');
    }
    my_strreminsert(shell->last_input, *cur_pos);
    display_input(shell, cur_pos);
    return (false);
}
