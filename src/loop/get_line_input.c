/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** handle arrow key and input of user
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include "my_puts.h"
#include "my_strings.h"
#include "mysh_struct.h"
#include "loop.h"

static const int capacity_size_add = 10;

static const int number_action_key = 4;

int key_action_key[] = {
    '\033',
    '\t',
    4,
    127
};

bool (*value_action_key[])(shell_t *shell) = {
    use_key_up,
    use_key_tab,
    use_key_ctrld,
    use_key_backspace
};

void free_secure(void *data)
{
    if (data == NULL) {
        return;
    }
    free(data);
}

static bool add_char_to_input(shell_t *shell, char c)
{
    char *tmp = shell->last_input;
    char tab[2] = {c, '\0'};

    if (my_strlen(tmp) + 2 >= (int) shell->last_input_len) {
        shell->last_input_len += capacity_size_add;
        shell->last_input = my_calloc(shell->last_input_len);
        my_strcpy(shell->last_input, tmp);
        free_secure(tmp);
    }
    my_strcat(shell->last_input, tab);
    my_putchar(c);
    if (c == '\n') {
        return (true);
    }
    return (false);
}

static bool handle_input(shell_t *shell)
{
    int ch = 0;

    ch = getchar();
    if (ch == -1) {
        return (false);
    }
    for (int i = 0; i < number_action_key; i++) {
        if (ch == key_action_key[i] && value_action_key[i] != NULL) {
            return (value_action_key[i](shell));
        }
    }
    return (add_char_to_input(shell, ch));
}

// inspiration from :
// https://stackoverflow.com/questions/31963835/how-to-read-
// terminals-input-buffer-immediately-after-keypress
static void setup_input_not_buffer(struct termios terms[2], int *saved_input,
    bool is_start)
{
    if (is_start == true) {
        tcgetattr(0, terms + 0);
        terms[1] = terms[0];
        terms[1].c_lflag &= ~(ICANON | ECHO);
        tcsetattr(0, TCSANOW, terms + 1);
        *saved_input = fcntl(0, F_GETFL, 0);
        fcntl(0, F_SETFL, *saved_input | O_NONBLOCK);
    } else {
        tcsetattr(0, TCSANOW, terms + 0);
        fcntl(0, F_SETFL, *saved_input);
    }
}

bool get_line_input(shell_t *shell)
{
    struct termios terms[2] = {0};
    int saved_input = 0;

    if (isatty(0) == 0) {
        if (getline(&shell->last_input, &shell->last_input_len, stdin) <= 0) {
            shell->is_end = true;
            return (false);
        }
        return (true);
    }
    setup_input_not_buffer(terms, &saved_input, true);
    while (handle_input(shell) != true);
    setup_input_not_buffer(terms, &saved_input, false);
    return (true);
}
