/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** action key of arrow
*/

#include <stdbool.h>
#include <unistd.h>
#include "history.h"
#include "loop.h"
#include "my_puts.h"
#include "my_strings.h"
#include "mysh.h"
#include "mysh_struct.h"

//TODO: itter through history
bool use_key_up(shell_t *shell, __attribute__((unused)) int *cur_pos,
    int *cur_nb_hist)
{
    const char *hist_line = get_history_line(shell->env, *cur_nb_hist - 1);

    if (hist_line == NULL) {
        my_printf("\nNo more history backward\n");
        if (isatty(0)) {
            print_prompt(shell);
            my_putstr(shell->last_input);
        }
        return (false);
    }
    clear_input(shell, cur_pos);
    free_secure(shell->last_input);
    *cur_nb_hist -= 1;
    *cur_pos = 0;
    shell->last_input = my_strstrip(hist_line, "\n ");
    shell->last_input_len = my_strlen(shell->last_input);
    display_input(shell, cur_pos);
    return (false);
}

bool use_key_down(shell_t *shell, __attribute__((unused)) int *cur_pos,
    int *cur_nb_hist)
{
    const char *hist_line = get_history_line(shell->env, *cur_nb_hist + 1);

    if (hist_line == NULL) {
        my_printf("\nNo more history forward\n");
        if (isatty(0)) {
            print_prompt(shell);
            my_putstr(shell->last_input);
        }
        return (false);
    }
    clear_input(shell, cur_pos);
    free_secure(shell->last_input);
    *cur_nb_hist += 1;
    *cur_pos = 0;
    shell->last_input = my_strstrip(hist_line, "\n ");
    shell->last_input_len = my_strlen(shell->last_input);
    display_input(shell, cur_pos);
    return (false);
}

bool use_key_left(__attribute__((unused)) shell_t *shell, int *cur_pos,
    __attribute__((unused)) int *cur_nb_hist)
{
    if (*cur_pos <= 0) {
        return (false);
    }
    my_putchar('\b');
    *cur_pos -= 1;
    return (false);
}

bool use_key_right(shell_t *shell, int *cur_pos,
    __attribute__((unused)) int *cur_nb_hist)
{
    if (my_strlen(shell->last_input) <= *cur_pos ||
            shell->last_input == NULL) {
        return (false);
    }
    my_putchar(shell->last_input[*cur_pos]);
    *cur_pos += 1;
    return (false);
}
