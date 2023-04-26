/*
** EPITECH PROJECT, 2022
** my_strlen
** File description:
** count number of char in str
*/

#include <stddef.h>

int my_strlen(char const *str)
{
    int count = 0;

    if (str == NULL)
        return 0;
    for (; str[count]; count++);
    return (count);
}
