/*
** EPITECH PROJECT, 2022
** LIBMACRO
** File description:
** some usefull macro
*/

#ifndef MY_MACRO_H_
    #define MY_MACRO_H_

// get the absolute value
    #define ABSOL(x) ((x) < 0) ? ((x) * -1) : (x)

// get the max
    #define MAX(x, y) ((x > y) ? (x) : (y))

// get the min
    #define MIN(x, y) ((x < y) ? (x) : (y))

// define bool
    #define BOOL int
    #define TRUE 1
    #define FALSE 0

// redefine null
    #ifndef NULL
        #define NULL ((void *) 0)
    #endif

#endif
