/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** display_prompt
*/

#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include "prompt.h"

const fun_t PROMPT_FUNCTIONS[PROMPT_NB + 1] = {
    {'a',  &display_prompt_a},
    {'d',  &display_prompt_d},
    {'D',  &display_prompt_cap_d},
    {'e',  &display_prompt_e},
    {'h',  &display_prompt_h},
    {'H',  &display_prompt_cap_h},
    {'j',  &display_prompt_j},
    {'l',  &display_prompt_l},
    {'n',  &display_prompt_n},
    {'r',  &display_prompt_r},
    {'s',  &display_prompt_s},
    {'t',  &display_prompt_t},
    {'T',  &display_prompt_cap_t},
    {'@',  &display_prompt_at},
    {'A',  &display_prompt_cap_a},
    {'u',  &display_prompt_u},
    {'v',  &display_prompt_v},
    {'V',  &display_prompt_cap_v},
    {'w',  &display_prompt_w},
    {'W',  &display_prompt_cap_w},
    {'!',  &display_prompt_exclamation},
    {'#',  &display_prompt_pound},
    {'$',  &display_prompt_dollar},
    {'\\', &display_prompt_backslash},
    {'[',  &display_prompt_non_printing},
    {'\0', &display_prompt_octal},
    {0},
};

// \a     an ASCII bell character (07)
PROMPT_FUN(display_prompt_a)
{
    (void)str;
    printf("\a");
    return;
}

// \d     the date in "Weekday Month Date" format (e.g., "Tue May 26")
PROMPT_FUN(display_prompt_d)
{
    struct tm *tm = gmtime((time_t[]){time(NULL)});
    char buf[256] = {0};

    strftime(buf, sizeof buf, "%a %b %d", tm);
    printf(buf);
    return;
}

// \D{format}
//        the format is passed to strftime(3) and the result is inserted
//        into the prompt string; an empty format results in  a  locale-
//        specific time representation.  The braces are required
PROMPT_FUN(display_prompt_cap_d)
{
    return;
}

// \e     an ASCII escape character (033)
PROMPT_FUN(display_prompt_e)
{
    return;
}

// \h     the hostname up to the first `.'
PROMPT_FUN(display_prompt_h)
{
    return;
}

// \H     the hostname
PROMPT_FUN(display_prompt_cap_h)
{
    return;
}

// \j     the number of jobs currently managed by the shell
PROMPT_FUN(display_prompt_j)
{
    return;
}

// \l     the basename of the shell's terminal device name
PROMPT_FUN(display_prompt_l)
{
    return;
}

// \n     newline
PROMPT_FUN(display_prompt_n)
{
    (void)str;
    printf("\n");
    return;
}

// \r     carriage return
PROMPT_FUN(display_prompt_r)
{
    return;
}

// \s     the name of the shell, the basename of $0 (the portion follow‐
//        ing the final slash)
PROMPT_FUN(display_prompt_s)
{
    return;
}

// \t     the current time in 24-hour HH:MM:SS format
PROMPT_FUN(display_prompt_t)
{
    return;
}

// \T     the current time in 12-hour HH:MM:SS format
PROMPT_FUN(display_prompt_cap_t)
{
    return;
}

// \@     the current time in 12-hour am/pm format
PROMPT_FUN(display_prompt_at)
{
    return;
}

// \A     the current time in 24-hour HH:MM format
PROMPT_FUN(display_prompt_cap_a)
{
    return;
}

// \u     the username of the current user
PROMPT_FUN(display_prompt_u)
{
    return;
}

// \v     the version of bash (e.g., 2.00)
PROMPT_FUN(display_prompt_v)
{
    return;
}

// \V     the release of bash, version + patch level (e.g., 2.00.0)
PROMPT_FUN(display_prompt_cap_v)
{
    return;
}

// \w     the current working directory, with $HOME abbreviated  with  a
//        tilde (uses the value of the PROMPT_DIRTRIM variable)
PROMPT_FUN(display_prompt_w)
{
    return;
}

// \W     the  basename of the current working directory, with $HOME ab‐
//        breviated with a tilde
PROMPT_FUN(display_prompt_cap_w)
{
    return;
}

// \!     the history number of this command
PROMPT_FUN(display_prompt_exclamation)
{
    return;
}

// \#     the command number of this command
PROMPT_FUN(display_prompt_pound)
{
    return;
}

// \$     if the effective UID is 0, a #, otherwise a $
PROMPT_FUN(display_prompt_dollar)
{
    return;
}

// \nnn   the character corresponding to the octal number nnn
PROMPT_FUN(display_prompt_octal)
{
    return;
}

// \\     a backslash
PROMPT_FUN(display_prompt_backslash)
{
    return;
}

// \[     begin a sequence of non-printing characters,  which  could  be
//        used to embed a terminal control sequence into the prompt
// \]     end a sequence of non-printing characters
PROMPT_FUN(display_prompt_non_printing)
{
    return;
}

void print_opt(const char *str)
{
    if (isdigit(*str)) {
        PROMPT_FUNCTIONS[PROMPT_OCTAL].fun(str);
        return;
    }
    for (int i = 0; PROMPT_FUNCTIONS[i].c; i++) {
        if (*str == PROMPT_FUNCTIONS[i].c) {
            PROMPT_FUNCTIONS[i].fun(str);
            return;
        }
    }
    printf("\\%c", *str);
}

void display_prompt(const char *ps)
{
    for (; *ps; ps++) {
        if (*ps == '\\') {
            print_opt(++ps);
        } else {
            printf("%c", *ps);
        }
    }
    fflush(stdout);
}
