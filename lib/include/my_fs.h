/*
** EPITECH PROJECT, 2021
** LIBMY
** File description:
** the file part of libmy
*/

#ifndef MY_FS_H_
    #define MY_FS_H_

/**
** @brief get the entire content of file path (if readable)
** @param path
** @return null if path is not readable; otherwise the content
**/
char *fs_get_content(char const *path);

/**
** @brief get size of the content of filepath (if stat can)
** @param path
** @return -1 if stat cant get size; the size else
**/
int fs_get_size(char const *path);

/**
** @brief open file path with read only
** @param path
** @return -1 if cant open; the file descriptor else
**/
int fs_open_ronly(char const *path);

/**
** @brief get the filename of a filepath-like
** @param path the path of the filepath-like
** @param delim delimiter using to separate folders inside the path
** @return pointer to the start of the filename in the path
**/
const char *get_filename(const char *path, char delim);

/**
** @brief join path with a delim
** @param delim the delimiter to use
** @param nb_path number of path after this parameter
** @param ... paths
** @return the new malloced char *
**/
char *join_path(char delim, int nb_path, ...);

#endif
