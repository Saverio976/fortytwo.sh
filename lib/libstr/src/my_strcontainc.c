/*
** EPITECH PROJECT, 2022
** LIBSTR
** File description:
** check if str contain c
*/

int my_strcontainc(char const *str, char const c)
{
    int is_found = 0;

    for (int i = 0; is_found == 0 && str[i] != '\0'; i++) {
        if (str[i] == c) {
            is_found = 1;
        }
    }
    return (is_found);
}
