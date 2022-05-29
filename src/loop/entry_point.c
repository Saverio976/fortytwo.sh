/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** setup the shell and call loop
*/

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "my_dico.h"
#include "my_fs.h"
#include "mysh_struct.h"
#include "mysh.h"
#include "loop.h"

shell_t *add_config(shell_t *shell)
{
    const char to_add[] = ".thrushrc";
    const char *home = dico_t_get_value(shell->env, "HOME");
    char *tmp = NULL;
    int saved_input = 0;

    if (home == NULL) {
        return (shell);
    }
    tmp = join_path('/', 2, home, to_add);
    if (tmp == NULL || access(tmp, R_OK) != 0) {
        free_secure(tmp);
        return (shell);
    }
    saved_input = redirect_input(tmp);
    free(tmp);
    for (shell->is_end = false; shell->is_end != true; loop(shell));
    ends_redirect_input(saved_input);
    return (shell);
}

shell_t *create_shell(dico_t *env, bool is_file)
{
    shell_t *shell = NULL;

    shell = malloc(sizeof(shell_t));
    if (shell == NULL) {
        return (NULL);
    }
    shell->status_code = 0;
    shell->is_end = false;
    shell->almost_the_end = false;
    shell->last_input = NULL;
    shell->last_input_len = 0;
    shell->command = NULL;
    shell->alias = NULL;
    shell->env = env;
    add_config(shell);
    shell->status_code = 0;
    shell->almost_the_end = false;
    shell->is_end = false;
    shell->is_file = is_file;
    return (shell);
}

void destroy_shell(shell_t *shell)
{
    if (shell == NULL) {
        return;
    }
    if (shell->env != NULL) {
        dico_t_destroy(shell->env);
    }
    if (shell->command != NULL) {
        list_t_destroy(shell->command);
    }
    if (shell->alias != NULL) {
        list_t_destroy(shell->alias);
    }
    if (shell->last_input != NULL) {
        free(shell->last_input);
    }
    free(shell);
}

int entry_point(dico_t *env, bool is_file)
{
    shell_t *shell = NULL;
    int ret_code = 0;

    shell = create_shell(env, is_file);
    if (shell == NULL) {
        return (84);
    }
    while (shell->is_end == false) {
        ret_code = loop(shell);
    }
    if (isatty(0) == 0) {
        ret_code = shell->status_code;
    } else {
        ret_code = (shell->status_code == 0) ? 0 : 84;
    }
    destroy_shell(shell);
    return (ret_code);
}
