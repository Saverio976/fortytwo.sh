/*
** EPITECH PROJECT, 2022
** fortytwo.sh
** File description:
** utils
*/

#include <stdio.h>
#include <string.h>
#include <sys/param.h>
#include <time.h>

void print_time(const char *format)
{
    struct tm *tm;
    char buf[256] = {0};

    tm = localtime((time_t[]) {time(NULL)});
    strftime(buf, sizeof buf, format, tm);
    printf(buf);
}

char *get_substr(char *buf, size_t size, const char *str, char *const delim[2])
{
    const char *end = NULL;
    size_t startlen = strlen(delim[0]);
    size_t substr_len = 0;
    size_t buflen = 0;

    if (strncmp(str, delim[0], startlen)) {
        return NULL;
    }
    str += startlen;
    end = strstr(str, delim[1]);
    if (!end) {
        return NULL;
    }
    substr_len = end - str;
    buflen = MIN(substr_len, size - 1);
    strncpy(buf, str, buflen);
    buf[buflen] = '\0';
    return buf;
}
