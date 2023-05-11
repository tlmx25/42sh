/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** prompt_color
*/

#include "mysh.h"

static const var_node color[] = {
        {"R", "\e[31m", NULL, NULL},
        {"G", "\e[32m", NULL, NULL},
        {"Y", "\e[33m", NULL, NULL},
        {"C", "\e[34m", NULL, NULL},
        {"V", "\e[35m", NULL, NULL},
        {"c", "\e[36m", NULL, NULL},
        {"g", "\e[37m", NULL, NULL},
        {"O", "\e[7m", NULL, NULL},
        {"o", "\e[8m", NULL, NULL},
        {"F", "\e[9m", NULL, NULL},
};

int is_color(char **tmp, char flag)
{
    for (size_t i = 0; i < ARRAY_LENGTH(color); i++) {
        if (flag == color[i].name[0]) {
            *tmp = my_strcat_free(*tmp, color[i].var, 1, 0);
            return 1;
        }
    }
    return 0;
}
