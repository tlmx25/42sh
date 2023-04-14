/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** manage_local_variable.c
*/

#include "mysh.h"

void print_local_variable(UNU char const **arg, var_s *var)
{
    if (LOCAL_VAR == NULL)
        return;
    for (var_node *node = LOCAL_VAR->head; node != NULL; node = node->next)
        my_printf("%s=%s\n", node->name, node->var);
}

void set_local_var(const char **info, var_s *var)
{
    var_node *node;
    if (my_arrsize(info) == 1) {
        print_local_variable(info, var);
        return;
    }
    if (!my_str_isalpha_env(info[1], "set: ")) {
        STATUS = 1;
        return;
    }
    if ((node = find_node(info[1], LOCAL_VAR)) != NULL) {
        free(node->var);
        node->var = my_strdup(info[2]);
    } else
        add_var(info, LOCAL_VAR);
}
