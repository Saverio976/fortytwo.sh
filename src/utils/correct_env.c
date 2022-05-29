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

static const char ps1_custom[] = "\033[1;33m╭─\\A \033[1;36m\\u \033[0;34m->" \
                                    " \033[0;34m(\033[1;31m\\W\033[0;34m) " \
                                    "\033[1;33m✗\n╰─ ~ \033[0m ";

static const char nls_path_default[] = "/usr/share/locale/%L/LC_MESSAGES/" \
                                        "%N.cat:/usr/share/locale/%l/" \
                                        "LC_MESSAGES/%N.cat";

static dico_t *add_shelllvl(dico_t *env)
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

static dico_t *add_pwd_user(dico_t *env)
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

static dico_t *add_vars(dico_t *env)
{
    char *tmp = NULL;

    if (dico_t_get_value(env, "NLSPATH") == NULL) {
        tmp = my_strdup(nls_path_default);
        if (tmp == NULL) {
            return (env);
        }
        env = dico_t_add_data(env, "NLSPATH", tmp, free);
    }
    return (env);
}

dico_t *correct_env(dico_t *env)
{
    env = add_shelllvl(env);
    env = add_pwd_user(env);
    env = dico_t_rem(env, "OLDPWD");
    env = add_vars(env);
    env = dico_t_add_data(env, "PS1", my_strdup(ps1_custom), free);
    return (env);
}
