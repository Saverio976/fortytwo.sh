/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** header for the loop subfolder
*/

#ifndef SH42_LOOP_H_
    #define SH42_LOOP_H_

    #include "mysh_struct.h"

bool use_key_tab(shell_t *shell);
bool use_key_up(shell_t *shell);
bool use_key_ctrld(shell_t *shell);
bool use_key_backspace(shell_t *shell);

bool get_line_input(shell_t *shell);

#endif
