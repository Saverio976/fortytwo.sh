/*
** EPITECH PROJECT, 2022
** fortytwo.sh
** File description:
** prompt_flags_history
*/

#include <stdio.h>
#include "history.h"
#include "prompt.h"

// \!     the history number of this command
PROMPT_FUN(display_prompt_exclamation)
{
    printf("%d", inc_history_size(env, 0));
    return 0;
}
