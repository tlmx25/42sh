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
    if ((letter == '&' && (after == '&' || before == '&')) ||
        (letter == '|' && (after == '|' || before == '|'))) {
        return 1;
    }
    return 0;
}

static int count_words(char const *str)
{
    int count = 0;
    size_t len = my_strlen(str);

    if (str == NULL)
        return 0;
    for (size_t i = 0; i < len; i++) {
        if (i > 0 && i < len - 1 && is_separators(str[i], str[i + 1],
        str[i - 1]))
            count += 1;
    }
    if (len == 0) {
        return 0;
    } else if (len == 1) {
        return !is_separators(str[0], '\0', '\0');
    } else {
        return count + !is_separators(str[len - 1], str[len - 2], '\0');
    }
}

static int tab_fill(char **tab, size_t len, char const *str)
{
    int z = 0;
    int check;
    size_t save;

    for (size_t i = 0; i < len; i++) {
        check = 0;
        save = i;
        for (; i < len && is_separators(str[i], (i + 1 < len ? str[i + 1]
        : '\0'), (i > 0 ? str[i - 1] : '\0')); i++, save++);
        for (; i < len && !is_separators(str[i], (i + 1 < len ? str[i + 1]
        : '\0'), (i > 0 ? str[i - 1] : '\0')); check++, i++);
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
