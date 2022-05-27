/*
** EPITECH PROJECT, 2022
** B-PSU-210-TLS-2-1-42sh-xavier.mitault
** File description:
** env_value
*/

#include <string.h>
#include <stdlib.h>
#include "my_list.h"
#include "mysh_struct.h"
#include "my_strings.h"
#include "mysh.h"
#include "my_wordarray.h"

char *tab_to_str(char **tab)
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
    return str;
}

static void check_env_value(int pos[2], char *str, char **tab, dico_t *dico)
{
    if (tab[pos[0]][pos[1]] == '$' && str[pos[0] + 1] != '\0') {
        str = dico_t_get_value(dico, tab[pos[0]] + pos[1] + 1);
        if (str == NULL) {
            free(tab[pos[0]]);
            tab[pos[0]] = my_strdup(" ");
        } else {
            free(tab[pos[0]]);
            tab[pos[0]] = strdup(str);
        }
    }
}

char *replace_value_env(dico_t *dico, char *str)
{
    char **tab = NULL;
    char *cmd = NULL;
    int pos[2] = {0};

    tab = my_wordarray_from_str(str, ' ');
    for (pos[0] = 0; tab[pos[0]] != NULL; pos[0]++) {
        for (pos[1] = 0; tab[pos[0]][pos[1]] != '\0'; pos[1]++) {
            check_env_value(pos, str, tab, dico);
        }
    }
    cmd = tab_to_str(tab);
    my_wordarray_free(tab);
    return cmd;
}
