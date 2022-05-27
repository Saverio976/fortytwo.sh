/*
** EPITECH PROJECT, 2022
** B-PSU-210-TLS-2-1-42sh-xavier.mitault
** File description:
** env_value
*/

#include "my_list.h"
#include "mysh_struct.h"
#include <string.h>
#include <stdlib.h>
#include "mysh.h"

int count_word(const char *str)
{
    int i = 0;
    int count = 0;

    while (str[i] != '\0') {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\0' &&
        str[i + 1] != ' ' && str[i + 1] != '\t') {
            count++;
        }
        i++;
    }
    return (count + 1);
}

int my_len_of_word(const char *str, int index)
{
    int i = index;

    while (str[i] && str[i] != ' ' && str[i] != '\t')
        i++;
    return i - index;
}

char **my_str_to_word_array(char const *str)
{
    char **tab = NULL;
    int k = 0;

    tab = malloc(sizeof(char **) * (count_word(str) + 1));
    if (!tab)
        return (NULL);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ' && str[i] != '\t') {
            tab[k] = malloc(sizeof(char) * my_len_of_word(str, i) + 1);
            strncpy(tab[k], &str[i], my_len_of_word(str, i));
            tab[k][my_len_of_word(str, i)] = '\0';
            i += my_len_of_word(str, i) - 1;
            k++;
        }
    }
    tab[k] = NULL;
    return tab;
}

char *tab_to_str(char **tab)
{
    char *str = NULL;
    int i = 0;

    str = malloc(sizeof(char) * (TODO));
    while (tab[i]) {
        str = strcat(str, tab[i]);
        str = strcat(str, " ");
        i++;
    }
    return str;
}

char *replace_value_env(dico_t *dico, char *str)
{   
    char *tmp = NULL;
    char **tab = NULL;
    char *cmd = NULL;

    cmd = malloc(sizeof(char) * (my_strlen(str) + 1));
    tab = my_str_to_word_array(str);
    for (int i = 0; tab[i] != NULL; i++) {
        for (int j = 0; tab[i][j] != '\0'; j++) {
            if (tab[i][j] == '$' && str[i + 1] != '\0') {
                str = dico_t_get_value(dico, tab[i] + j + 1);
                tmp = strdup(str);
                //tab[i] = strdup(' ');
                tab[i] = strdup(tmp);
            }
        }
    }
    my_wordarray_showln(tab);
    cmd = tab_to_str(tab);
    return cmd;
}
