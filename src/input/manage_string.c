/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** manage_string
*/

#include "mysh.h"

char *my_str_del_char(char *str, int cursor)
{
    int len = my_strlen(str);
    char *new_str;
    int j = 0;

    if (len == 0 || cursor == -1)
        return str;
    new_str = malloc(sizeof(char) * (len));
    if (new_str == NULL)
        return str;
    for (int i = 0; i < len; i++) {
        if (i == cursor)
            continue;
        new_str[j] = str[i];
        j++;
    }
    new_str[len - 1] = '\0';
    free(str);
    return new_str;
}

static char *my_str_cat_cpy(char *str, int cursor, int len, int c)
{
    int j = 0;
    char *new_str = malloc(sizeof(char) * (len + 2));

    if (new_str == NULL)
        return str;
    for (int i = 0; i < len; j++) {
        if (j == cursor && c != '\n') {
            new_str[j] = (char)c;
            continue;
        }
        new_str[j] = str[i];
        i++;
    }
    if (len == cursor || c == '\n')
        new_str[len] = (char)c;
    new_str[len + 1] = '\0';
    free(str);
    return new_str;
}

char *my_str_cat_char(char *str, int c, int cursor)
{
    int len = my_strlen(str);

    if (len == 0 && c == 127)
        return str;
    if (c == 127)
        return my_str_del_char(str, cursor - 1);
    return my_str_cat_cpy(str, cursor, len, c);
}
