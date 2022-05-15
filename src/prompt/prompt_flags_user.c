/*
** EPITECH PROJECT, 2022
** fortytwo.sh
** File description:
** prompt_flags_user
*/

#include <libgen.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "prompt.h"

// \h     the hostname up to the first `.'
PROMPT_FUN(display_prompt_h)
{
    char buf[256] = {0};
    char *dot = NULL;

    gethostname(buf, sizeof buf);
    dot = strchr(buf, '.');
    if (dot) {
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
