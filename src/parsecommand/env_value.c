/*
** EPITECH PROJECT, 2022
** B-PSU-210-TLS-2-1-42sh-xavier.mitault
** File description:
** env_value
*/

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "my_list.h"
#include "mysh_struct.h"
#include "my_strings.h"
#include "mysh.h"
#include "my_wordarray.h"
#include "globbings.h"

char *tab_to_str(char **tab, bool need_free)
{
    char *str = NULL;
    int i = 0;
    int size = 0;

    size = my_wordarray_size(tab) + my_wordarray_len(tab);
    str = my_calloc(size + 2);
    if (!str)
        return (NULL);
    while (tab[i]) {
        str = my_strcat(str, tab[i]);
        str = my_strcat(str, " ");
        i++;
    }
    if (need_free == true) {
        my_wordarray_free(tab);
    }
    return str;
}

static char *check_env_value(int pos[2], char *str, char **tab, dico_t *dico)
{

    if (tab[pos[0]][pos[1]] == '$' && str[pos[0] + 1] != '\0') {
        str = dico_t_get_value(dico, tab[pos[0]] + pos[1] + 1);
        if (str == NULL) {
            my_puterror(tab[pos[0]] + pos[1] + 1, "Undefined variable.\n");
            free(tab[pos[0]]);
            tab[pos[0]] = strdup(" ");
            pos[1] = 0;
            return (NULL);
        } else {
            free(tab[pos[0]]);
            tab[pos[0]] = strdup(str);
        }
    }
    return (tab[pos[0]]);
}

char *replace_value_env(dico_t *dico, char *str, shell_t *shell)
{
    char **tab = NULL;
    char *cmd = NULL;
    char *tmp = (void *) 1;
    int pos[2] = {0};

    tab = my_wordarray_from_str(str, ' ');
    if (tab == NULL)
        return (NULL);
    for (pos[0] = 0; tab[pos[0]] != NULL && tmp; pos[0]++) {
        for (pos[1] = 0; tab[pos[0]][pos[1]] != '\0' && tmp; pos[1]++) {
            tmp = check_env_value(pos, str, tab, dico);
        }
        tab[pos[0]] = globbing_entry(tab[pos[0]]);
    }
    if (tmp == NULL) {
        my_wordarray_free(tab);
        shell->status_code = 1;
        return NULL;
    }
    cmd = tab_to_str(tab, true);
    return cmd;
}
