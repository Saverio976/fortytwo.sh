/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** react to key in input
*/

#include <stdbool.h>
#include <unistd.h>
#include "my_list.h"
#include "my_macro.h"
#include "my_wordarray.h"
#include "my_puts.h"
#include "my_strings.h"
#include "mysh.h"
#include "mysh_struct.h"
#include "loop.h"
#include "complete.h"

char *tab_to_str(char **tab, bool need_free);

static void modif_completion_str(shell_t *shell, int *cur_pos, list_t *comp)
{
    char **arr = NULL;
    int len = 0;
    char *tmp = NULL;

    if (list_t_len(comp) <= 0) {
        return;
    }
    arr = my_wordarray_from_str(shell->last_input, ' ');
    if (arr == NULL) {
        return;
    }
    len = my_wordarray_len(arr);
    free_secure(arr[len - 1]);
    arr[MAX(len - 1, 0)] = my_strdup(comp->data);
    tmp = tab_to_str(arr, true);
    free_secure(shell->last_input);
    shell->last_input = my_strstrip(tmp, " ");
    shell->last_input_len = my_strlen(shell->last_input);
    free_secure(tmp);
}

bool use_key_tab(shell_t *shell, __attribute__((unused)) int *cur_pos)
{
    list_t *all = NULL;

    if (my_strlen(shell->last_input) <= 0) {
        return (false);
    }
    all = complete_this(shell->last_input, shell->env);
    if (list_t_len(all) <= 0) {
        return (false);
    }
    if (list_t_len(all) == 1) {
        clear_input(shell, cur_pos, 0);
        modif_completion_str(shell, cur_pos, all);
        display_input(shell, cur_pos);
        list_t_destroy(all);
        return (false);
    }
    display_completion(shell, cur_pos, all);
    list_t_destroy(all);
    return (false);
}

bool use_key_ctrld(shell_t *shell, __attribute__((unused)) int *cur_pos)
{
    list_t *all = NULL;

    if (my_strlen(shell->last_input) <= 0) {
        shell->is_end = true;
        return (true);
    }
    all = complete_this(shell->last_input, shell->env);
    display_completion(shell, cur_pos, all);
    list_t_destroy(all);
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
