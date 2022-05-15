/*
** EPITECH PROJECT, 2022
** fortytwo.sh
** File description:
** prompt_flags_date
*/

#include <stdio.h>
#include <string.h>
#include "prompt.h"

// \d     the date in "Weekday Month Date" format (e.g., "Tue May 26")
PROMPT_FUN(display_prompt_d)
{
    print_time("%a %b %d");
    return 0;
}

// \D{format}
//        the format is passed to strftime(3) and the result is inserted
//        into the prompt string; an empty format results in  a  locale-
//        specific time representation.  The braces are required
PROMPT_FUN(display_prompt_cap_d)
{
    char format[256] = {0};

    if (!get_substr(format, sizeof format, str, (char*[]) {"{", "}"})) {
        printf("\\D");
        return 0;
    }
    print_time(format);
    return strlen(format) + 2;
}
