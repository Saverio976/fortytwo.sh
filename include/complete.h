/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** header for the complete part
*/

#ifndef COMPETE_42SH_H_
    #define COMPETE_42SH_H_

    #include "my_list.h"
    #include "my_dico.h"

list_t *complete_this(char *string, dico_t *env);

list_t *remove_same(list_t *all);

#endif
