/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** autocompletion
*/

#include "mysh.h"
char *my_str_cat_char(char *str, int c, int cursor);

static void get_world(char **input, var_s *var)
{
    var_node *node = DICO->head;
    int len = my_strlen(*input);

    if (len == 0)
        return;
    for (; node != NULL; node = node->next) {
        if (my_strncmp(node->name, *input, len) == 0) {
            free(*input);
            *input = my_strdup(node->name);
            return;
        }
    }
}

void handle_autocompletion(int c, char **input, var_s *var, int *cursor)
{
    if (c != '\t') {
        *input = my_str_cat_char(*input, (char)c, *cursor);
        return;
    }
    if (var == NULL)
        return;
    get_world(input, var);

}
