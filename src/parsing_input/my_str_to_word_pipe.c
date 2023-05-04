/*
** EPITECH PROJECT, 2022
** B-PSU-200-REN-2-1-42sh-arthur.doriel
** File description:
** my_str_to_word_pipe.c
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "my.h"

int check_for_double_pipe(char *input)
{
    for (int i = 0; i < my_strlen(input); i++) {
        if (input[i] == '|' && input[i + 1] == '|')
            return 1;
    }
    return 0;
}

static int is_sep(char const *separators, char letter, char after, char before)
{
    if (separators == NULL)
        return 0;
    for (int i = 0; separators[i]; i++) {
        if (separators[i] == letter && letter == after)
            return 0;
        if (separators[i] == letter && letter == before)
            return 0;
        if (separators[i] == letter)
            return 1;
    }
    return 0;
}

static int count(char const *str, char *separators)
{
    int count = 0;
    size_t len = my_strlen(str);

    if (str == NULL)
        return 0;
    for (size_t i = 0; i < len; i++) {
        if (is_sep(separators, str[i], str[i + 1], str[i - 1]))
            count += 1;
    }
    return count + (len > 0 &&
    !is_sep(separators, str[len - 1], str[len - 2], str[len]));
}

static int fill(char **tab, size_t len, char const *str, char *separators)
{
    int z = 0;
    int check;
    size_t save;

    for (size_t i = 0; i < len; i++) {
        check = 0;
        save = i;
        for (; is_sep(separators, str[i], str[i + 1], str[i - 1]) &&
        i < len; i++, save++);
        for (; !is_sep(separators, str[i], str[i + 1], str[i - 1]) &&
        i < len; check++, i++);
        tab[z] = malloc(sizeof(char) * (check + 1));
        if (tab[z] == NULL)
            return 84;
        for (int j = 0; j != check; save++, j++)
            tab[z][j] = str[save];
        tab[z][check] = '\0';
        z++;
    }
    return 0;
}

char **my_str_to_word_pipe(char const *str, char *separators)
{
    size_t len = my_strlen(str);
    int nb_word = count(str, separators);
    char **tab = malloc(sizeof(char *) * (nb_word + 1));

    for (int i = 0; i <= nb_word; i++)
        tab[i] = NULL;
    if (tab == NULL || str == NULL || str[0] == '\0') {
        free(tab);
        return NULL;
    }
    if (fill(tab, len, str, separators) == 84) {
        free_tab(tab);
        return NULL;
    }
    if (tab[nb_word - 1] != NULL && tab[nb_word -1][0] == '\0')
        tab[nb_word -1] = NULL;
    tab[nb_word] = NULL;
    return tab;
}
