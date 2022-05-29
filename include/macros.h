/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** define message errors
*/

#ifndef MACROS_H_
    #define MACROS_H_

    #define AMBIGUOUS_OU_ERR "Ambiguous output redirect.\n"
    #define AMBIGUOUS_IN_ERR "Ambiguous input redirect.\n"
    #define MISSING_ERR "Missing name for redirect.\n"

    #ifdef __unix__
        #define INPUT_STDIN_PATH "/proc/self/fd/0"
    #elif defined(_WIN32) || defined(WIN32)
        #define INPUT_STDIN_PATH "con"
    #else
        #define INPUT_STDIN_PATH ""
    #endif

#endif
