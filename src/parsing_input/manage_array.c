/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** manage_array.c
*/

#include "mysh.h"

char *get_name(char const *str)
{
    size_t i = 0;
    size_t j = 0;
    char *name;

    if (str == NULL)
        return NULL;
    for (; str[i] && is_separator(" \t", str[i]); i++);
    for (j = i; str[j] && !is_separator(";<>| \t", str[j]); j++);
    name = my_strndup(&str[i], j - i);
    return name;

}

void erase_name(char **array)
{
    size_t i = 0;

    for (; array[1][i] && is_separator(" \t", array[1][i]); i++);
    for (; array[1][i] && !is_separator(";<>| \t", array[1][i]); i++)
        array[1][i] = ' ';
}
