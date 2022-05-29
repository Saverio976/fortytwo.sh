/*
** EPITECH PROJECT, 2022
** fortytwo.sh
** File description:
** prompt_flags_char
*/

#include <stdio.h>
#include "prompt.h"

// \a     an ASCII bell character (07)
PROMPT_FUN(display_prompt_a)
{
    printf("%s", "\a");
    return 0;
}

// \e     an ASCII escape character (033)
PROMPT_FUN(display_prompt_e)
{
    printf("%s", "\033");
    return 0;
}

// \n     newline
PROMPT_FUN(display_prompt_n)
{
    printf("%s", "\n");
    return 0;
}

// \r     carriage return
PROMPT_FUN(display_prompt_r)
{
    printf("%s", "\r");
    return 0;
}

// \\     a backslash
PROMPT_FUN(display_prompt_backslash)
{
    printf("%s", "\\");
    return 0;
}
