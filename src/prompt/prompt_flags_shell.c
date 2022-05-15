/*
** EPITECH PROJECT, 2022
** fortytwo.sh
** File description:
** prompt_flags_shell
*/

#include "prompt.h"
#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// \j     the number of jobs currently managed by the shell
PROMPT_FUN(display_prompt_j)
{
    printf("TODO: '\\j'");
    return 0;
}

// \l     the basename of the shell's terminal device name
PROMPT_FUN(display_prompt_l)
{
    printf(basename(ttyname(STDOUT_FILENO)));
    return 0;
}

// \s     the name of the shell, the basename of $0 (the portion follow‐
//        ing the final slash)
PROMPT_FUN(display_prompt_s)
{
    char buf[256] = {0};

    strncpy(buf, program_invocation_name, sizeof buf - 1);
    printf(basename(buf));
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
