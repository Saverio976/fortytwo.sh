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
#include "history.h"
#include "my_puts.h"
#include "my_macro.h"
#include "my_strings.h"
#include "mysh_struct.h"
#include "loop.h"

static const int capacity_size_add = 10;

static const int number_action_key = 3;
static const int key_action_key[] = {
    '\t',
    4,
    127
};
static bool (*value_action_key[])(shell_t *shell, int *current_pos) = {
    use_key_tab,
    use_key_ctrld,
    use_key_backspace
};

static const int number_action_arrow = 4;
static const int key_action_arrow[] = {
    'A',
    'B',
    'C',
    'D'
};
static bool (*value_action_arrow[])(shell_t *shell, int *current_pos,
        int *cur_nb_hist) = {
    use_key_up,
    use_key_down,
    use_key_right,
    use_key_left
};

void free_secure(void *data)
{
    if (data == NULL) {
        return;
    }
    free(data);
}

static bool add_char_to_input(shell_t *shell, char c, int *current_pos)
{
    char *tmp = shell->last_input;

    if (my_strlen(tmp) + 2 >= (int) shell->last_input_len) {
        shell->last_input_len += capacity_size_add;
        shell->last_input = my_calloc(shell->last_input_len);
        my_strcpy(shell->last_input, tmp);
        free_secure(tmp);
    }
    if (c == '\n') {
        *current_pos = my_strlen(shell->last_input);
    }
    my_strinsert(shell->last_input, c, *current_pos);
    *current_pos += 1;
    display_input(shell, current_pos);
    if (c == '\n') {
        return (true);
    }
    return (false);
}

static bool handle_input(shell_t *shell, int *curpos, int *cur_nb_hist)
{
    int ch[3] = {0};

    ch[0] = getchar();
    if (ch[0] == -1) {
        return (false);
    }
    ch[2] = (ch[0] == '\033') ? getchar() : 0;
    ch[1] = (ch[0] == '\033') ? getchar() : 0;
    for (int i = 0; i < MAX(number_action_key, number_action_arrow); i++) {
        if (i < number_action_key && ch[0] == key_action_key[i]) {
            return (value_action_key[i](shell, curpos));
        } else if (i < number_action_arrow && ch[1] == key_action_arrow[i]) {
            return (value_action_arrow[i](shell, curpos, cur_nb_hist));
        }
    }
    return (add_char_to_input(shell, ch[0], curpos));
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
    int current_pos = 0;
    int cur_nb_hist = inc_history_size(shell->env, 0);

    if (isatty(0) == 0) {
        if (getline(&shell->last_input, &shell->last_input_len, stdin) <= 0) {
            shell->is_end = true;
            return (false);
        }
        return (true);
    }
    setup_input_not_buffer(terms, &saved_input, true);
    while (handle_input(shell, &current_pos, &cur_nb_hist) != true);
    setup_input_not_buffer(terms, &saved_input, false);
    return (true);
}
