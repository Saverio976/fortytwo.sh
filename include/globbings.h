/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** header for globbings
*/

#ifndef GLOBBINGS_H_
    #define GLOBBINGS_H_

typedef struct my_files_s {
    char *name;
    struct my_files_s *next;
    struct my_files_s *prev;
} my_files_t;

void globbing_entry(char *str);
void free_list(my_files_t *files);
void check_size(my_files_t **files, char *str);
void check_letters(my_files_t **my_files, char *str);
void check_brakets(my_files_t **my_files, char *str);
void delete_tmp(my_files_t *delete, my_files_t **files);

#endif