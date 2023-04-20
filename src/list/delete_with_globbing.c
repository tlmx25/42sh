/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** delete_with_globbing
*/

#include "mysh.h"

static int check_name(char const *name, int mode, char const *node_name)
{
    int len = my_strlen(name);
    char *tmp;
    int value = 0;
    char *name_clean = my_clean_string((char *)name, "*", 0);

    if (mode == 2)
        value = (my_strncmp(name_clean, node_name, len) == 0) ? 1 : 0;
    if (mode == 3)
        value = my_str_in_str(node_name, name_clean);
    if (mode == 1) {
        tmp = my_strstr((char *)node_name, name_clean);
        value = (my_strcmp(tmp, name_clean) == 0) ? 1 : 0;
    }
    free(name_clean);
    return value;
}

void delete_with_globbing(char const *name, var_list *list)
{
    int mode = 0;
    var_node *next = NULL;

    if (my_get_first_char(name, " \t") == '*')
        mode = 1;
    if (my_get_last_char(name, " \t") == '*')
        mode = (mode == 1) ? 3 : 2;
    if (mode == 0) {
        delete_env_var(name, list);
        return;
    }
    for (var_node *node = list->head; node != NULL; node = next) {
        next = node->next;
        if (check_name(name, mode, node->name)) {
            delete_env_var(node->name, list);
        }
    }
}
