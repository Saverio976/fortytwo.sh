/*
** EPITECH PROJECT, 2022
** fortytwo.sh
** File description:
** display_prompt
*/

#include "prompt.h"
#include <ctype.h>
#include <limits.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
    {'w',  &display_prompt_w},
    {'W',  &display_prompt_cap_w},
    {'$',  &display_prompt_dollar},
    {'\\', &display_prompt_backslash},
    {'\0', &display_prompt_octal},
    {0},
};

// \a     an ASCII bell character (07)
PROMPT_FUN(display_prompt_a)
{
    printf("\a");
    return 0;
}

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

    if (!get_substring(format, str, "{", "}")) {
        printf("\\D");
        return 0;
    }
    print_time(format);
    return strlen(format) + 2;
}

// \e     an ASCII escape character (033)
PROMPT_FUN(display_prompt_e)
{
    printf("\033");
    return 0;
}

// \h     the hostname up to the first `.'
PROMPT_FUN(display_prompt_h)
{
    char buf[256] = {0};
    char *dot = NULL;

    gethostname(buf, sizeof buf);
    if ((dot = strchr(buf, '.'))) {
        *dot = '\0';
    }
    printf(buf);
    return 0;
}

// \H     the hostname
PROMPT_FUN(display_prompt_cap_h)
{
    char buf[256] = {0};

    gethostname(buf, sizeof buf);
    printf(buf);
    return 0;
}

// \j     the number of jobs currently managed by the shell
PROMPT_FUN(display_prompt_j)
{
    printf("\\j");
    return 0;
}

// \l     the basename of the shell's terminal device name
PROMPT_FUN(display_prompt_l)
{
    char buf[256];

    strcpy(buf, ttyname(STDOUT_FILENO));
    printf(basename(buf));
    return 0;
}

// \n     newline
PROMPT_FUN(display_prompt_n)
{
    printf("\n");
    return 0;
}

// \r     carriage return
PROMPT_FUN(display_prompt_r)
{
    printf("\r");
    return 0;
}

// \s     the name of the shell, the basename of $0 (the portion follow‐
//        ing the final slash)
PROMPT_FUN(display_prompt_s)
{
    char buf[256];

    strcpy(buf, program_invocation_name);
    printf(basename(buf));
    return 0;
}

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

// \u     the username of the current user
PROMPT_FUN(display_prompt_u)
{
    printf(getlogin());
    return 0;
}

// \w     the current working directory, with $HOME abbreviated  with  a
//        tilde (uses the value of the PROMPT_DIRTRIM variable)
PROMPT_FUN(display_prompt_w)
{
    const char *home = get_var_value(envp, "HOME");
    size_t homelen = strlen(home);
    char cwd[PATH_MAX] = {0};

    getcwd(cwd, sizeof cwd);
    if (strncmp(home, cwd, homelen) == 0) {
        printf("~");
        printf(cwd + homelen);
    } else
        printf(cwd);
    return 0;
}

// \W     the  basename of the current working directory, with $HOME ab‐
//        breviated with a tilde
PROMPT_FUN(display_prompt_cap_w)
{
    const char *home = get_var_value(envp, "HOME");
    char cwd[PATH_MAX] = {0};

    getcwd(cwd, sizeof cwd);
    if (strcmp(home, cwd) == 0) {
        printf("~");
    } else
        printf(basename(cwd));
    return 0;
}

// \$     if the effective UID is 0, a #, otherwise a $
PROMPT_FUN(display_prompt_dollar)
{
    if (geteuid() == 0) {
        printf("#");
    } else {
        printf("$");
    }
    return 0;
}

// \nnn   the character corresponding to the octal number nnn
PROMPT_FUN(display_prompt_octal)
{
    char *endptr = NULL;

    printf("%c", (int)strtol(str, &endptr, 8) % 256);
    return endptr - str - 1;
}

// \\     a backslash
PROMPT_FUN(display_prompt_backslash)
{
    printf("\\");
    return 0;
}

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
