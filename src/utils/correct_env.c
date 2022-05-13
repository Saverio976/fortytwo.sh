/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** correct the env values
*/

#include <stdlib.h>
#include <unistd.h>
#include "my_conversions.h"
#include "my_dico.h"
#include "my_strings.h"

dico_t *add_shelllvl(dico_t *env)
{
    dico_t *shlvl = NULL;
    char *tmp = NULL;
    int nb = 0;

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

dico_t *add_pwd_user(dico_t *env)
{
    dico_t *pwd = dico_t_get_elem(env, "PWD");
    dico_t *user = NULL;
    char buff[256] = {0};

    if (pwd == NULL && getcwd(buff, 255) != NULL) {
        env = dico_t_add_data(env, "PWD", my_strdup(buff), &free);
    }
    for (int i = 0; i < 256; i++) {
        buff[i] = '\0';
    }
    user = dico_t_get_elem(env, "USER");
    if (user == NULL && getlogin_r(buff, 255) >= 0) {
        env = dico_t_add_data(env, "USER", my_strdup(buff), &free);
    }
    return (env);
}

dico_t *correct_env(dico_t *env)
{
    env = add_shelllvl(env);
    env = add_pwd_user(env);
    env = dico_t_rem(env, "OLDPWD");
    return (env);
}
