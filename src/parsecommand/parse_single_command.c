/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** execute on string os single command
*/

#include <stdlib.h>
#include "my_strings.h"
#include "my_wordarray.h"
#include "mysh_struct.h"
#include "mysh.h"
#include "my_puts.h"

void *free_command(command_t *command)
{
    if (command == NULL) {
        return (NULL);
    }
    if (command->redirect_to_file != NULL) {
        free(command->redirect_to_file);
    }
    if (command->file_to_input != NULL) {
        free(command->file_to_input);
    }
    if (command->binary != NULL) {
        free(command->binary);
    }
    if (command->arguments != NULL) {
        my_wordarray_free(command->arguments);
    }
    free(command->command);
    free(command);
    return (NULL);
}

static int set_values(command_t *cm, int *is_error, shell_t *shell)
{
    cm->binary = NULL;
    cm->arguments = NULL;
    cm->redirect_to_file = get_redirect_to_file(cm->command, is_error, cm);
    if (*is_error != 0) {
        return (-1);
    }
    cm->binary = get_binary_path(cm->command, shell);
    if (cm->binary == NULL) {
        return (-1);
    }
    cm->arguments = get_arguments_array(cm->command);
    if (cm->arguments == NULL) {
        return (-1);
    }
    return (0);
}

command_t *parse_single_command(const char *string, shell_t *shell)
{
    command_t *cm = NULL;
    int is_error = 0;

    cm = malloc(sizeof(command_t));
    if (cm == NULL) {
        return (NULL);
    }
    cm->command = my_strdup(string);
    cm->file_to_input = get_file_to_input(cm->command, &is_error, cm);
    if (is_error != 0) {
        free_command(cm);
        return (NULL);
    }
    if (set_values(cm, &is_error, shell) != 0) {
        free_command(cm);
        return (NULL);
    }
    return (cm);
}
