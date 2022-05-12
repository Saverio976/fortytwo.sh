/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** get colors header
*/

#ifndef COLORS_MYSH_H_
    #define COLORS_MYSH_H_

/**
** @brief get escape code for no color
**
** @return escape code
**/
const char *get_reset(void);

/**
** @brief get 'dark' 'true' color of key
**
** @param key could be : {"green","red","blue","cyan","orange","purple","gray"}
**
** @return "" if not find, the escape code otherwise
**/
const char *get_color(const char *key);

/**
** @brief get 'light' color of key
**
** @param key could be : {"green","red","blue","cyan","yellow","purple","gray"}
**
** @return
**/
const char *get_light_color(const char *key);

#endif
