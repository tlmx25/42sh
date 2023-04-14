/*
** EPITECH PROJECT, 2023
** B-PSU-200-REN-2-1-minishell1-tom.lefoix
** File description:
** free_list.c
*/

#include "mysh.h"

void free_list(var_list *list)
{
    var_node *next;

    if (list == NULL)
        return;
    for (var_node *node = list->head; node != NULL; node = next) {
        next = node->next;
        free_node(&node);
    }
    free(list);
}
