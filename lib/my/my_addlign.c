/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** my_addlign.c
*/

#include <string.h>
#include <stdlib.h>
char *my_strdup(char const *src);
void my_puterror(char *error);

char **my_appendline(char **array, char *line) {
    int len = 0;
    char **new_array = NULL;

    while (array != NULL && array[len] != NULL)
        len++;
    if (line == NULL)
        return array;
    new_array = (char**)realloc(array, (len + 2) * sizeof(char*));
    if (new_array == NULL)
        return array;
    new_array[len] = my_strdup(line);
    new_array[len + 1] = NULL;
    return new_array;
}


char **my_addlign(char **tab, char *str, int key)
{
    char **temps;
    int j = 0;
    int count = 0;
    for (; tab[count]; count++);
    if (count < key)
        my_puterror("a key is superior to the size of tab");
    temps = malloc(sizeof(char *) * count + 2);
    for (int h = 0; tab[h]; h++, j++) {
        if (h == key) {
            temps[j] = my_strdup(str);
            j += 1;
        }
        temps[j] = my_strdup(tab[h]);
    }
    if (count == key) {
        temps[j] = my_strdup(str);
        j += 1;
    }
    temps[j] = 0;
    return temps;
}
