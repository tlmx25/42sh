/*
** EPITECH PROJECT, 2023
** B-PSU-200-REN-2-1-minishell1-tom.lefoix
** File description:
** free_env.c
*/

#include "mysh.h"

void free_env(env_list **list)
{
    env_v *next;
    for (env_v *node = (*list)->head; node != NULL; node = next) {
        next = node->next;
        free_node(&node);
    }
}
