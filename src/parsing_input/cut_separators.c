/*
** EPITECH PROJECT, 2022
** B-PSU-200-REN-2-1-42sh-arthur.doriel
** File description:
** cut_separators.c
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "my.h"

static int is_separators(char letter, char after, char before)
{
    if ((letter == '&' && after == letter) ||
    (letter == '&' && before == letter))
        return 1;
    if ((letter == '|' && after == letter) ||
    (letter == '|' && before == letter))
        return 1;
    return 0;
}

static int count_words(char const *str)
{
    int count = 0;
    size_t len = my_strlen(str);

    if (str == NULL)
        return 0;
    for (size_t i = 0; i < len; i++) {
        if (is_separators(str[i], str[i + 1], str[i - 1]))
            count += 1;
    }
    return count + (len > 0 &&
    !is_separators(str[len - 1], str[len - 2], str[len]));
}

static int tab_fill(char **tab, size_t len, char const *str)
{
    int z = 0;
    int check;
    size_t save;

    for (size_t i = 0; i < len; i++) {
        check = 0;
        save = i;
        for (; is_separators(str[i], str[i + 1], str[i - 1]) &&
        i < len; i++, save++);
        for (; !is_separators(str[i], str[i + 1], str[i - 1]) &&
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

char **tab_cut_separators(char const *str)
{
    size_t len = my_strlen(str);
    int nb_word = count_words(str);
    char **tab = malloc(sizeof(char *) * (nb_word + 1));

    for (int i = 0; i <= nb_word; i++)
        tab[i] = NULL;
    if (tab == NULL || str == NULL || str[0] == '\0') {
        free(tab);
        return NULL;
    }
    if (tab_fill(tab, len, str) == 84) {
        free_tab(tab);
        return NULL;
    }
    if (tab[nb_word - 1] != NULL && tab[nb_word -1][0] == '\0')
        tab[nb_word -1] = NULL;
    tab[nb_word] = NULL;
    return tab;
}
