/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** my_get_first_char.c
*/

int is_separator(char const *separators, char letter);

char my_get_first_char(char const *str, char const *skip_char)
{
    for (int i = 0; str[i]; i++)
        if (!is_separator(skip_char, str[i]))
            return str[i];
    return 0;
}
