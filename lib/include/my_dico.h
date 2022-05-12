/*
** EPITECH PROJECT, 2022
** libdico header
** File description:
** dico structure
*/

#ifndef LIB_DICO_H_
    #define LIB_DICO_H_

typedef struct dico_s dico_t;

struct dico_s {
    dico_t *next;
    dico_t *last;
    char key[255];
    void *value;
    void (*destroy)(void *data);
};

/**
** @brief create a dico node
** info : the key will be copied (and only the 254 first chars)
**
** @param key the key to acces the value
** @param value the value attached to the key
** @param destroy function to destroy the value
**
** @return a node
**/
dico_t *dico_t_create(char const *key, void *value,
    void (*destroy)(void *data));

/**
** @brief create a dico node and add it to the dico
** info : the key will be copied (and only the 254 first chars)
**
** @param dico dico in which the new node will be added
** @param key the key to access teh value
** @param value teh value attached to the key
** @param destroy function to destroy teh value
**
** @return the dico (or the new "node" if dico == NULL)
**/
dico_t *dico_t_add_data(dico_t *dico, char const *key,
        void *value, void (*destroy)(void *value));

/**
** @brief add a node to the dico
**
** @param dico the dico
** @param elem elem to add
**
** @return the dico (or the new "node" if dico == NULL)
**/
dico_t *dico_t_add_elem(dico_t *dico, dico_t *elem);

/**
** @brief remove a node from the dico and return it
**
** @param dico the dico in which the node is
** @param key key to reference the node
**
** @return the value of the node
**/
void *dico_t_pop_value(dico_t *dico, char const *key);

/**
** @brief remove a node from the dico and return it
**
** @param dico the dico in which the node is
** @param key key to reference teh node
**
** @return the dico_t node
**/
dico_t *dico_t_pop_elem(dico_t *dico, char const *key);

/**
** @brief delete totally a node
**
** @param dico the dico in which the node is
** @param key the key to reference the node
**
** @return the dico if remove execute well; NULL if there is any error
**/
dico_t *dico_t_rem(dico_t *dico, char const *key);

/**
** @brief delete the dico entirely
**
** @param dico teh dico to delete
**
** @return 1 if delete pass well; 0 if there is any error
**/
int dico_t_destroy(dico_t *dico);

/**
** @brief get the value of a node from a dico
**
** @param dico dico where the node is
** @param key the key to reference the node
**
** @return the value of the node; NULL if there is no key refer to node
**/
void *dico_t_get_value(dico_t *dico, char const *key);

/**
** @brief get the node from a dico
**
** @param dico the dico where teh node is
** @param key the key to reference teh node
**
** @return the node; NULL if there is no key refer to node
**/
dico_t *dico_t_get_elem(dico_t *dico, char const *key);

#endif
