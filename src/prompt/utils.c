/*
** EPITECH PROJECT, 2022
** fortytwo.sh
** File description:
** utils
*/

#include <stdio.h>
#include <string.h>
#include <time.h>

void print_time(const char *format)
{
    struct tm *tm = localtime((time_t[]) {time(NULL)});
    char buf[256] = {0};

    strftime(buf, sizeof buf, format, tm);
    printf(buf);
}

const char *get_var_value(char *const *envp, const char *varname)
{
    size_t varlen = strlen(varname);

    for (; *envp; envp++) {
        if (strncmp(*envp, varname, varlen) && (*envp)[varlen] == '=') {
            return *envp + varlen + 1;
        }
    }
    return NULL;
}

char *get_substring(char *buf, const char *str,
        const char *start, const char *end)
{
    const char *endstr = NULL;
    size_t startlen = strlen(start);

    if (strncmp(str, start, startlen))
        return NULL;
    str += startlen;
    endstr = strstr(str, end);
    if (!endstr)
        return NULL;
    strncpy(buf, str, endstr - str);
    return buf;
}
