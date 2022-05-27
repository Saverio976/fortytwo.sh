/*
** EPITECH PROJECT, 2022
** fortytwo.sh
** File description:
** my_clear_str
*/

#ifndef MY_CLEAR_STR_H_
    #define MY_CLEAR_STR_H_

typedef struct word_list_s {
    char *word;
    struct word_list_s *next;
} word_list_t;

/**
** @brief main function to clear a string
** @param string
** @return cleared string
**/
char *clear_str(char *str);

/**
** @brief add a list of word in a string
** @param string
** @param int
** @return word or null if error
**/
char *find_word_quotes(char *str, int *size);

/**
** @brief add a list of word in a string
** @param string
** @param int
** @return word or null if error
**/
char *find_word(char *str, int *size);

#endif
