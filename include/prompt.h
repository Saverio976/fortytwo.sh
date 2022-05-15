/*
** EPITECH PROJECT, 2022
** fortytwo.sh
** File description:
** prompt
*/

#ifndef PROMPT_H_
    #define PROMPT_H_

    #ifndef _GNU_SOURCE
        #define _GNU_SOURCE 1
    #endif

    #include <stddef.h>
    #include "my_dico.h"

    #define UNUSED __attribute__((unused))
    #define PROMPT_FUN(name) int (name)(UNUSED dico_t *env, \
            UNUSED const char *str)

UNUSED typedef struct fun_s {
    char c;
    PROMPT_FUN(*fun);
} fun_t;

enum PROMPT_OPT {
    PROMPT_ERROR = -1,
    PROMPT_A,
    PROMPT_D,
    PROMPT_CAP_D,
    PROMPT_E,
    PROMPT_H,
    PROMPT_CAP_H,
    PROMPT_J,
    PROMPT_L,
    PROMPT_N,
    PROMPT_R,
    PROMPT_S,
    PROMPT_T,
    PROMPT_CAP_T,
    PROMPT_AT,
    PROMPT_CAP_A,
    PROMPT_U,
    PROMPT_W,
    PROMPT_CAP_W,
    PROMPT_DOLLAR,
    PROMPT_BACKSLASH,
    PROMPT_OCTAL,
    PROMPT_NB
};

PROMPT_FUN(display_prompt_a);
PROMPT_FUN(display_prompt_d);
PROMPT_FUN(display_prompt_cap_d);
PROMPT_FUN(display_prompt_e);
PROMPT_FUN(display_prompt_h);
PROMPT_FUN(display_prompt_cap_h);
PROMPT_FUN(display_prompt_j);
PROMPT_FUN(display_prompt_l);
PROMPT_FUN(display_prompt_n);
PROMPT_FUN(display_prompt_r);
PROMPT_FUN(display_prompt_s);
PROMPT_FUN(display_prompt_t);
PROMPT_FUN(display_prompt_cap_t);
PROMPT_FUN(display_prompt_at);
PROMPT_FUN(display_prompt_cap_a);
PROMPT_FUN(display_prompt_u);
PROMPT_FUN(display_prompt_w);
PROMPT_FUN(display_prompt_cap_w);
PROMPT_FUN(display_prompt_dollar);
PROMPT_FUN(display_prompt_backslash);
PROMPT_FUN(display_prompt_octal);
void print_time(const char *format);
char *get_substr(char *buf, size_t size, const char *str, char *const delim[2]);
void display_prompt(dico_t *env, const char *ps);

#endif /* prompt.h */
