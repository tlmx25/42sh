/*
** EPITECH PROJECT, 2022
** emacs my_strcat
** File description:
** concatenate two str
*/

#include <stdio.h>
#include <stdlib.h>
#include "my.h"

int my_strlen(char const *str);

static void exit_strcat(char *dest, char *src, char free_dest, char free_src)
{
    if (free_dest == 1)
        free(dest);
    if (free_src == 1)
        free(src);
}

char *my_strcat_free(char *dest, char *src, char free_dest, char free_src)
{
    int i = my_strlen(dest);
    char *temps = my_calloc(sizeof(char) * ((i + my_strlen(src)) + 1));

    if (dest == NULL || src == NULL) {
        free(temps);
        temps = my_strdup((dest != NULL) ? dest : src);
        exit_strcat(dest, src, free_dest, free_src);
        return temps;
    }
    for (int x = 0; x <= (i + my_strlen(src)); x++)
        temps[x] = '\0';
    temps = my_strcpy(temps, dest);
    for (int j = 0; src[j] != '\0'; i++, j++)
        temps[i] = src[j];
    exit_strcat(dest, src, free_dest, free_src);
    return (temps);
}

char *my_strcat(char const *dest, char const *src)
{
    int i = my_strlen(dest);
    char *temps = my_calloc(sizeof(char) * ((i + my_strlen(src)) + 1));

    if (dest == NULL || src == NULL) {
        free(temps);
        return my_strdup((dest != NULL) ? dest : src);
    }
    for (int x = 0; x <= (i + my_strlen(src)); x++)
        temps[x] = '\0';
    temps = my_strcpy(temps, dest);
    for (int j = 0; src[j] != '\0'; i++, j++)
        temps[i] = src[j];
    return (temps);
}
