/*
** EPITECH PROJECT, 2022
** fortytwo.sh
** File description:
** history
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_dico.h"

char *get_history_file(dico_t *env)
{
    const char *file = dico_t_get_value(env, "HISTFILE");
    const char *home = NULL;
    char buf[PATH_MAX] = {0};
    char filename[] = ".trush_history";

    if (!file) {
        home = dico_t_get_value(env, "HOME");
        if (!home || strlen(home) > sizeof buf - sizeof filename)
            return NULL;
        strncpy(buf, home, sizeof buf);
        strcat(buf, "/.trush_history");
        dico_t_add_data(env, "HISTFILE", buf, &free);
    }
    return dico_t_get_value(env, "HISTFILE");
}

int count_file_lines(const char *path)
{
    FILE *file = fopen(path, "r");
    int nb_lines = 0;

    if (!file) {
        return -1;
    }
    while ((fscanf(file, "%*[^\n]"), fscanf(file, "%*c")) != EOF) {
        nb_lines++;
    }
    fclose(file);
    return nb_lines;
}

int inc_history_size(dico_t *env, int increment)
{
    static int cmd_number = 0;

    cmd_number += increment;
    if (cmd_number > increment)
        return cmd_number;
    cmd_number += count_file_lines(get_history_file(env));
    return cmd_number;
}

int add_to_hist(dico_t *env, char **command)
{
    const char *histfile = get_history_file(env);
    FILE *file = fopen(histfile, "a+");
    int i = 0;

    if (!file) {
        return -1;
    }
    fseek(file, -1, SEEK_END);
    if (fgetc(file) != '\n') {
        fprintf(file, "\n");
    }
    for (; command[i + 1]; i++) {
        fprintf(file, "%s ", command[i]);
    }
    fprintf(file, "%s\n", command[i]);
    inc_history_size(env, 1);
    fclose(file);
    return 0;
}
