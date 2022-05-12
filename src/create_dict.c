/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** create a dict from env
*/

#include <stdlib.h>
#include "my_conversions.h"
#include "my_dico.h"
#include "my_strings.h"
#include "my_macro.h"

static char *get_value_env(const char *string)
{
    int i = 0;
    char *value = NULL;

    if (string == NULL) {
        return (NULL);
    }
    while (string[i] != '\0' && string[i] != '=') {
        i++;
    }
    if (string[i] == '\0') {
        return (NULL);
    }
    i++;
    value = my_strdup(string + i);
    if (value == NULL) {
        return (NULL);
    }
    return (value);
}

static char *split_equal(const char *string)
{
    int i = 0;
    static char key[256] = {0};

    while (string[i] != '=' && string[i] != '\0') {
        i++;
    }
    if (string[i] == '\0') {
        return (NULL);
    }
    if (my_strncpy(key, string, MIN(i, 255)) == NULL) {
        return (NULL);
    }
    key[MIN(i, 255)] = '\0';
    return (key);
}

dico_t *correct_env(dico_t *env)
{
    dico_t *shlvl = NULL;
    char *tmp = NULL;
    int nb = 0;

    if (env == NULL) {
        return (NULL);
    }
    shlvl = dico_t_get_elem(env, "SHLVL");
    if (shlvl == NULL) {
        tmp = my_strdup("1");
        if (tmp == NULL) {
            return (env);
        }
        env = dico_t_add_data(env, "SHLVL", tmp, &free);
    } else {
        nb = my_atoi(shlvl->value);
        free(shlvl->value);
        shlvl->value = my_itoa(nb + 1);
    }
    return (env);
}

dico_t *parse_env(char *const env[])
{
    dico_t *dict = NULL;
    char *value = NULL;
    char *key = NULL;

    if (env == NULL) {
        return (NULL);
    }
    for (int i = 0; env[i] != NULL; i++) {
        value = get_value_env(env[i]);
        if (value == NULL) {
            continue;
        }
        key = split_equal(env[i]);
        if (key != NULL) {
            dict = dico_t_add_data(dict, key, value, &free);
        } else {
            free(value);
        }
    }
    return (correct_env(dict));
}
