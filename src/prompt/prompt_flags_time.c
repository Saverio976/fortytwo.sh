/*
** EPITECH PROJECT, 2022
** prompt
** File description:
** prompt_flags_time
*/

#include <time.h>
#include "prompt.h"

// \t     the current time in 24-hour HH:MM:SS format
PROMPT_FUN(display_prompt_t)
{
    print_time("%T");
    return 0;
}

// \T     the current time in 12-hour HH:MM:SS format
PROMPT_FUN(display_prompt_cap_t)
{
    print_time("%I:%M:%S");
    return 0;
}

// \@     the current time in 12-hour am/pm format
PROMPT_FUN(display_prompt_at)
{
    print_time("%I:%M %p");
    return 0;
}

// \A     the current time in 24-hour HH:MM format
PROMPT_FUN(display_prompt_cap_a)
{
    print_time("%H:%M");
    return 0;
}
