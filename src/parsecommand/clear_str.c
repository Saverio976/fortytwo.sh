/*
** EPITECH PROJECT, 2022
** fortytwo.sh
** File description:
** clear_str
*/

#include "my_clear_str.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *replace_tab_by_space(char *str)
{
    for (int i = 0; str[i] != '\0'; i ++)
        if (str[i] == '\t')
            str[i] = ' ';
    return (str);
}

static word_list_t *add_word(word_list_t *list, char *word)
{
    word_list_t *tmp = list;
    word_list_t *new_word = malloc(sizeof(word_list_t));

    if (new_word == NULL || word == NULL)
        return (list);
    new_word->word = strdup(word);
    new_word->next = NULL;
    if (list == NULL) {
        return (new_word);
    }
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = new_word;
    return (list);
}

static void free_list(word_list_t *list)
{
    word_list_t *tmp = list;
    word_list_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        free(tmp->word);
        free(tmp);
        tmp = next;
    }
}

static char *list_to_str(word_list_t *list)
{
    int size = 0;
    char *str = NULL;
    word_list_t *tmp = list;

    while (tmp != NULL) {
        size += (strlen(tmp->word) + 1);
        tmp = tmp->next;
    }
    str = malloc(sizeof(char) * (size + 1));
    if (str == NULL)
        return (NULL);
    str[0] = '\0';
    tmp = list;
    while (tmp != NULL) {
        strcat(str, tmp->word);
        if (tmp->next != NULL)
            strcat(str, " ");
        tmp = tmp->next;
    }
    return (str);
}

char *clear_str(char *str)
{
    int size = 0;
    char *word = NULL;
    word_list_t *list = NULL;

    replace_tab_by_space(str);
    for (int i = 0; str[i] != '\0'; i ++, size = 0) {
        if (str[i] == ' '  || str[i] == '\n')
            continue;
        if (str[i] == '"' || str[i] == '\'') {
            word = find_word_quotes(&str[i], &size);
        } else {
            word = find_word(&str[i], &size);
        }
        list = add_word(list, word);
        i += size - 1;
        free(word);
    }
    str = list_to_str(list);
    free_list(list);
    return (str);
}
