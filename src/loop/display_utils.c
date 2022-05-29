/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** utils function for display and prompt
*/

#include <unistd.h>
#include "my_list.h"
#include "my_puts.h"
#include "my_strings.h"
#include "mysh_struct.h"
#include "mysh.h"
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

bool reset_prompt_input(shell_t *shell, const char *to_print, int *cur_pos)
{
    my_printf("\n%s\n", to_print);
    if (isatty(0)) {
        print_prompt(shell);
        my_putstr(shell->last_input);
        *cur_pos = my_strlen(shell->last_input);
    }
    return (false);
}

void display_completion(shell_t *shell, int *current_pos, list_t *comlete)
{
    my_putstr("\nCompletions:\n");
    for (int i = 0; i < list_t_len(comlete); i++, comlete = comlete->next) {
        my_printf("%s\n", comlete->data);
    }
    if (isatty(0)) {
        print_prompt(shell);
        my_putstr(shell->last_input);
        *current_pos = my_strlen(shell->last_input);
    }
}
