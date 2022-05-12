/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** the main entry point for the project
*/

#include <stddef.h>
#include "my_dico.h"
#include "my_strings.h"
#include "mysh.h"

int main(int ac, char *const av[], char *const env[])
{
    (void)ac;
    (void)av;
    (void)env;
#include "prompt.h"
    display_prompt("\\d\n");
}
