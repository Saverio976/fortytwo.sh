/*
** EPITECH PROJECT, 2022
** libdico header
** File description:
** dico structure
*/

#ifndef LIB_LIST_H_
    #define LIB_LIST_H_

    #include <stddef.h>

typedef struct list_s list_t;

struct list_s {
    list_t *next;
    list_t *last;
    void *data;
    void (*destroy)(void *data);
};

list_t *list_t_add(list_t *list, void *data, void (*destroy)(void *data));

int list_t_destroy(list_t *list);

list_t *dico_t_get_node(list_t *list, int index);

void *dico_t_get_data(list_t *list, int index);

list_t *list_t_insert(list_t *list, int status, void *data,
        void (*destroy)(void *data));

int list_t_len(list_t *list);

#endif
