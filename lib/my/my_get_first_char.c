/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** my_get_first_char.c
*/

#include <stddef.h>
int my_strlen(char const *str);
int is_separator(char const *separators, char letter);

char my_get_last_char(char const *str, char const *skip_char)
{
    size_t len = my_strlen(str);

    for (int i = len - 1; i >= 0; i--)
        if (!is_separator(skip_char, str[i]))
            return str[i];
    return 0;
}

char my_get_first_char(char const *str, char const *skip_char)
{
    for (size_t i = 0; str[i]; i++)
        if (!is_separator(skip_char, str[i]))
            return str[i];
    return 0;
}
