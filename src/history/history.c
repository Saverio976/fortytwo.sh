/*
** EPITECH PROJECT, 2022
** fortytwo.sh
** File description:
** history
*/

#include <stdio.h>
#include <stdlib.h>
#include "my_fs.h"
#include "my_dico.h"

char *get_history_file(dico_t *env)
{
    const char *file = dico_t_get_value(env, "HISTFILE");
    const char *home = NULL;
    char *buf = NULL;
    char filename[] = ".thrush_history";

    if (!file) {
        home = dico_t_get_value(env, "HOME");
        if (!home)
            return NULL;
        buf = join_path('/', 2, home, filename);
        if (!buf)
            return NULL;
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
    int histfile_size = 0;

    cmd_number += increment;
    if (cmd_number > increment)
        return cmd_number;
    histfile_size = count_file_lines(get_history_file(env));
    if (histfile_size > 0)
        cmd_number += histfile_size;
    return cmd_number;
}

char *get_history_line(dico_t *env, int line_nb)
{
    const char *histfile = get_history_file(env);
    FILE *file = fopen(histfile, "r");
    char *line = NULL;

    if (!file) {
        return NULL;
    }
    while(--line_nb) {
        if ((fscanf(file, "%*[^\n]"), fscanf(file, "%*c")) == EOF) {
            fclose(file);
            return NULL;
        }
    }
    if (getline(&line, (size_t[]) {0}, file) < 0) {
        free(line);
        line = NULL;
    }
    fclose(file);
    return line;
}

int add_to_hist(dico_t *env, const char *line)
{
    const char *histfile = get_history_file(env);
    FILE *file = fopen(histfile, "a+");

    if (!file) {
        return -1;
    }
    fseek(file, -1, SEEK_END);
    if (fgetc(file) != '\n') {
        fputs("\n", file);
    }
    fprintf(file, "%s\n", line);
    inc_history_size(env, 1);
    fclose(file);
    return 0;
}
