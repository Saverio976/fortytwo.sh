/*
** EPITECH PROJECT, 2022
** fortytwo.sh
** File description:
** display_prompt
*/

#include <ctype.h>
#include <stdio.h>
#include "prompt.h"

const fun_t PROMPT_FUNCTIONS[PROMPT_NB + 1] = {
    {'a', &display_prompt_a},
    {'d', &display_prompt_d},
    {'D', &display_prompt_cap_d},
    {'e', &display_prompt_e},
    {'h', &display_prompt_h},
    {'H', &display_prompt_cap_h},
    {'j', &display_prompt_j},
    {'l', &display_prompt_l},
    {'n', &display_prompt_n},
    {'r', &display_prompt_r},
    {'s', &display_prompt_s},
    {'t', &display_prompt_t},
    {'T', &display_prompt_cap_t},
    {'@', &display_prompt_at},
    {'A', &display_prompt_cap_a},
    {'u', &display_prompt_u},
    {'w', &display_prompt_w},
    {'W', &display_prompt_cap_w},
    {'$', &display_prompt_dollar},
    {'\\', &display_prompt_backslash},
    {'\0', &display_prompt_octal},
    {0},
};

static int print_opt(char *const *envp, const char *str)
{
    if (isdigit(*str)) {
        return PROMPT_FUNCTIONS[PROMPT_OCTAL].fun(envp, str);
    }
    for (int i = 0; PROMPT_FUNCTIONS[i].c; i++) {
        if (*str == PROMPT_FUNCTIONS[i].c) {
            return PROMPT_FUNCTIONS[i].fun(envp, str + 1);
        }
    }
    printf("\\%c", *str);
    return 0;
}

void display_prompt(char *const *envp, const char *ps)
{
    size_t printed = 0;

    if (!envp || !ps)
        return;
    for (; *ps; ps++) {
        if (*ps == '\\') {
            printed = print_opt(envp, ++ps);
            ps += printed;
        } else {
            printf("%c", *ps);
        }
    }
    fflush(stdout);
}
