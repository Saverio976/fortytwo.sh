/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** action key of arrow
*/

#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include "history.h"
#include "loop.h"
#include "my_puts.h"
#include "my_strings.h"
#include "mysh.h"
#include "mysh_struct.h"

static const char history_backward[] = "No more history backward";
static const char history_forward[] = "No more history forward";

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

//TODO: itter through history
bool use_key_up(shell_t *shell, __attribute__((unused)) int *cur_pos,
    int *cur_nb_hist)
{
    int nb_hist = *cur_nb_hist - 1;
    char *hist_line = get_history_line(shell->env, nb_hist);

    if (hist_line == NULL) {
        return (reset_prompt_input(shell, history_backward, cur_pos));
    }
    clear_input(shell, cur_pos, 0);
    free_secure(shell->last_input);
    *cur_nb_hist = nb_hist;
    shell->last_input = my_strstrip(hist_line, "\n ");
    free(hist_line);
    shell->last_input_len = my_strlen(shell->last_input);
    display_input(shell, cur_pos);
    return (false);
}

bool use_key_down(shell_t *shell, __attribute__((unused)) int *cur_pos,
    int *cur_nb_hist)
{
    int nb_hist = *cur_nb_hist + 1;
    char *hist_line = get_history_line(shell->env, nb_hist);

    if (hist_line == NULL) {
        return (reset_prompt_input(shell, history_forward, cur_pos));
    }
    clear_input(shell, cur_pos, 0);
    free_secure(shell->last_input);
    *cur_nb_hist = nb_hist;
    *cur_pos = 0;
    shell->last_input = my_strstrip(hist_line, "\n ");
    free(hist_line);
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
