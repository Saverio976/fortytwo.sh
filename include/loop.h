/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** header for the loop subfolder
*/

#ifndef SH42_LOOP_H_
    #define SH42_LOOP_H_

    #include "mysh_struct.h"

bool use_key_tab(shell_t *shell, int *cur_pos);
bool use_key_ctrld(shell_t *shell, int *cur_pos);
bool use_key_backspace(shell_t *shell, int *cur_pos);
bool use_key_up(shell_t *shell, int *cur_pos, int *cur_nb_hist);
bool use_key_down(shell_t *shell, int *cur_pos, int *cur_nb_hist);
bool use_key_left(shell_t *shell, int *cur_pos, int *cur_nb_hist);
bool use_key_right(shell_t *shell, int *cur_pos, int *cur_nb_hist);

void display_input(shell_t *shell, int *current_pos);
void clear_input(shell_t *shell, int *current_pos, int to_go);
bool reset_prompt_input(shell_t *shell, const char *to_print, int *cur_pos);
void display_completion(shell_t *shell, int *current_pos, list_t *comlete);

bool get_line_input(shell_t *shell);

void free_secure(void *data);

#endif
