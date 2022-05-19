/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** minshell structs
*/

#ifndef MYSH_H_STRUCT_H_
    #define MYSH_H_STRUCT_H_

    #include <stdbool.h>
    #include <stddef.h>
    #include <fcntl.h>
    #include "my_dico.h"
    #include "my_list.h"

typedef struct command_s command_t;
typedef struct shell_s shell_t;

struct command_s {
    char *command;
    char *binary;
    char **arguments;
    char *redirect_to_file;
    int fd_redirect;
    int saved_stdout;
    char *file_to_input;
    int fd_input;
    int saved_stdin;
    enum type_mode {
        APPEND = O_APPEND,
        OVERWRITE = O_TRUNC
    } redirect_mode;
    pid_t pid_child;
};

struct shell_s {
    int status_code;
    char *last_input;
    list_t *command;
    list_t *alias;
    dico_t *env;
    bool is_end;
    bool almost_the_end;
    size_t last_input_len;
};

#endif
