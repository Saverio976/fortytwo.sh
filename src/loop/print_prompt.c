/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** print a nice prompt
*/

#include <stddef.h>
#include "my_dico.h"
#include "my_puts.h"
#include "mysh_struct.h"
#include "mysh.h"
#include "colors.h"

static const char *get_right_status_color(int status)
{
    if (status == 0) {
        return (get_color("green"));
    }
    return (get_color("red"));
}

static int print_prompt_default(shell_t *shell)
{
    char *home = NULL;
    char *pwd = NULL;

    my_putstr("\x1b[\x36 q");
    home = dico_t_get_value(shell->env, "USER");
    pwd = dico_t_get_value(shell->env, "PWD");
    my_printf("╭─%s[%d]%s", get_right_status_color(shell->status_code),
        shell->status_code, get_reset());
    if (home != NULL) {
        my_printf("~%s{@%s}%s", get_color("cyan"), home, get_reset());
    }
    if (pwd != NULL) {
        my_printf("~%s(%s)%s", get_color("purple"), pwd, get_reset());
    }
    my_putstr("\n╰─$ ");
    return (0);
}

int print_prompt(shell_t *shell)
{
    const char *ps1 = NULL;

    if (shell == NULL) {
        return (0);
    }
    ps1 = dico_t_get_value(shell->env, "PS1");
    if (ps1 == NULL) {
        return (print_prompt_default(shell));
    }
    display_prompt(shell->env, ps1);
    return (0);
}
