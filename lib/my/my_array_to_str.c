/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** my_array_to_str.c
*/

#include <stddef.h>
#include <stdlib.h>
#include "my.h"

char *my_array_to_str(char const **array)
{
    char *str = NULL;
    char *str_tmp;

    if (array == NULL)
        return NULL;
    for (size_t i = 0; array[i]; i++) {
        str_tmp = str;
        str = my_strcat(str, array[i]);
        if (str_tmp != NULL)
            free(str_tmp);
    }
    return str;
}
