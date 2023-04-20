/*
** EPITECH PROJECT, 2023
** B-PSU-200-REN-2-1-minishell1-tom.lefoix
** File description:
** function_env.c
*/

#include "mysh.h"
#include "error_mysh.h"

void print_env_list(UNU char const **arg, var_s *var)
{
    for (var_node *node = var->env_var->head; node != NULL; node = node->next)
        my_printf("%s=%s\n", node->name, node->var);
}

void delete_env_var(const char *name, var_list *list)
{
    var_node *node = list->head;

    for (; node != NULL && my_strcmp(node->name, name) != 0;
    node = node->next);
    if (node == NULL)
        return;
    if (list->head == node)
        list->head = node->next;
    if (list->tail == node)
        list->tail = node->prev;
    if (node->prev != NULL)
        node->prev->next = node->next;
    if (node->next != NULL)
        node->next->prev = node->prev;
    list->size -= 1;
    free_node(&node);
}

void set_env(char const **arg, var_s *var)
{
    var_node *node;
    if (my_arrsize(arg) == 1) {
        print_env_list(arg, var);
        return;
    }
    if (my_arrsize(arg) > 3) {
        my_printf("%z", SE_MANY_ARG, (STATUS = 1));
        return;
    }
    if (!my_str_isalpha_env(arg[1], "setenv: ")) {
        STATUS = 1;
        return;
    }

    if ((node = find_node(arg[1], ENV_VAR)) != NULL) {
        free(node->var);
        node->var = my_strdup(arg[2]);
    } else
        add_var(arg, ENV_VAR);
}

void unset_env(char const **arg, var_s *var)
{
    if (my_arrsize(arg) == 1) {
        write(2,"unsetenv: Too few arguments.\n", 29);
        STATUS = 1;
        return;
    }
    for (size_t i = 1; arg[i]; i++) {
        delete_with_globbing(arg[i], ENV_VAR);
    }
}
