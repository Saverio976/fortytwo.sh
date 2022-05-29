/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** the main entry point for the project
*/

#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include "my_dico.h"
#include "my_strings.h"
#include "mysh.h"

static int redirect_input(const char *file)
{
    int saved_input = -1;
    int fd = 0;

    fd = open(file, O_RDONLY);
    if (fd <= 0) {
        return (-1);
    }
    saved_input = dup(0);
    dup2(fd, 0);
    close(fd);
    return (saved_input);
}

static int ends_redirect_input(int saved_input)
{
    if (saved_input == -1) {
        return (0);
    }
    close(0);
    dup2(saved_input, 0);
    close(saved_input);
    return (0);
}

static int handle_batch_file(int ac, char *const av[], dico_t *env,
    int *saved_input)
{
    char *tmp = NULL;

    if (ac <= 1) {
        return (0);
    }
    if ((ac >= 3 && my_strcmp(av[1], "-b") == 0) ||
            my_strstartswith(av[1], "-") == 0) {
        tmp = (my_strstartswith(av[1], "-") == 1) ? av[2] : av[1];
        *saved_input = redirect_input(tmp);
        if (*saved_input < 0) {
            my_puterror(tmp, "No such file or directory.\n");
            dico_t_destroy(env);
            return (1);
        }
        return (0);
    }
    return (0);
}

int main(int ac, char *const av[], char *const env[])
{
    dico_t *dict = NULL;
    int status_code = 0;
    int saved_input = -1;

    if (ac == 2 && my_strcmp(av[1], "-h") == 0) {
        return (print_help(av[0]));
    }
    dict = parse_env(env);
    if (dict == NULL) {
        return (84);
    }
    if (handle_batch_file(ac, av, dict, &saved_input) == 1) {
        return (1);
    }
    status_code = entry_point(dict, (saved_input == -1) ? false : true);
    ends_redirect_input(saved_input);
    return (status_code);
}
