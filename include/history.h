/*
** EPITECH PROJECT, 2022
** fortytwo.sh
** File description:
** history
*/

#ifndef HISTORY_H
    #define HISTORY_H

    #include "my_dico.h"

/**
** @brief return $HISTFILE or set and return default value
**
** @param env environment already parsed char **env
**
** @return histfile path
**/
char *get_history_file(dico_t *env);

/**
** @brief count number of lines in a file
**
** @param file path
**
** @return number of lines
**/
int count_file_lines(const char *path);

/**
** @brief increment command history size
**
** @param env environment already parsed char **env
** @param increment number to add to history size
**
** @return new history size
**/
int inc_history_size(dico_t *env, int increment);

/**
** @brief get a line from histfile (must be free'd)
**
** @param env environment already parsed char **env
** @param line_nb number of the line to retrieve (starting at 1)
**
** @return line or NULL if not found
**/
char *get_history_line(dico_t *env, int line_nb);

/**
** @brief add line to histfile
**
** @param env environment already parsed char **env
** @param line line to add at the end of histfile
**
** @return 0 or a negative value in case of a error
**/
int add_to_hist(dico_t *env, char *line);

#endif /* history.h */
