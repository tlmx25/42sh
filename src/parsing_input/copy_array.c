/*
** EPITECH PROJECT, 2022
** B-PSU-200-REN-2-1-42sh-arthur.doriel
** File description:
** copy_array.c
*/

#include "mysh.h"

char** copystringarray(char** source)
{
    int size = 0;
    char **destination;
    if (source == NULL)
        return NULL;
    while (source[size] != NULL)
        size++;
    destination = (char**)malloc((size + 1) * sizeof(char*));
    for (int i = 0; i < size; i++) {
        if (source[i] != NULL)
            destination[i] = strdup(source[i]);
        else
            destination[i] = NULL;
    }
    destination[size] = NULL;
    return destination;
}
