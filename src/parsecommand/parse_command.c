/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** parse char * to commands
*/

#include "my_list.h"
#include "mysh_struct.h"
#include "mysh.h"
#include "my_strings.h"

#include <stdio.h>
#include <stdlib.h>

static char *replace_tab_by_space(char *str)
{
    for (int i = 0; str[i] != '\0'; i ++)
        if (str[i] == '\t')
            str[i] = ' ';
    return (str);
}

static char *delete_at_end_and_beginning(char *str)
{
    int i = 0, j = 0, len = 0;
    char *new_str = NULL;

    len = my_strlen(str);
    new_str = malloc(sizeof(char) * (len + 1));
    for (i = 0; str[i] == ' ' || str[i] == ';'; i ++);
    for (j = 0; str[i] != '\0'; i ++, j ++)
        new_str[j] = str[i];
    new_str[j] = '\0';
    free(str);
    return (new_str);
}

static char *delete_useless_space(char *str)
{
    int i = 0, j = 0;
    char *new_str = NULL;

    new_str = malloc(sizeof(char) * (my_strlen(str) + 1));
    for (i = 0; str[i] != '\0'; i ++) {
        if (str[i + 1] != '\0' && str[i] == ' ' && str[i + 1] == ' ')
            continue;
        new_str[j] = str[i];
        j ++;
    }
    new_str[j] = '\0';
    free(str);
    return (new_str);
}

static char *delete_line_return(char *str)
{
    for (int i = my_strlen(str) - 1; i >= 0; i --)
        if (str[i] == '\n')
            str[i] = '\0';
        else
            break;
    return (str);
}

char *clear_str(char *str)
{
    str = replace_tab_by_space(str);
    str = delete_at_end_and_beginning(str);
    str = delete_useless_space(str);
    str = delete_line_return(str);
    return (str);
}

int parse_commands(char *string, shell_t *shell)
{
    char *newstring = my_strdup(string);
    newstring = clear_str(newstring);
    list_t_destroy(shell->command);
    shell->command = my_strsplit(newstring, ";");
    shell->command = remove_empty_commands(shell->command);
    return (0);
}
