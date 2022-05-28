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
#include "loop.h"

void display_input(shell_t *shell, int *current_pos)
{
    clear_input(shell, current_pos, *current_pos);
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

void clear_input(shell_t *shell, int *current_pos, int to_go)
{
    for (int i = *current_pos; i < my_strlen(shell->last_input); i++) {
        my_putchar(' ');
    }
    for (int i = 0; i < my_strlen(shell->last_input); i++) {
        my_putchar('\b');
        my_putchar(' ');
        my_putchar('\b');
    }
    *current_pos = 0;
    for (int i = 0; i < to_go; i++) {
        my_putchar(' ');
        *current_pos += 1;
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
    clear_input(shell, cur_pos, *cur_pos - 1);
    if (*cur_pos > 0) {
        my_putchar('\b');
    }
    my_strreminsert(shell->last_input, *cur_pos);
    display_input(shell, cur_pos);
    return (false);
}
