/*
** EPITECH PROJECT, 2023
** B-PSU-200-REN-2-1-minishell1-tom.lefoix
** File description:
** array_to_linkedlist.c
*/

#include "mysh.h"

env_v *init_env_var_node(char const **info)
{
    env_v *node = malloc(sizeof(env_v));
    int get_lvl = (my_strcmp(info[0], "setenv") == 0) ? 2 : 1;

    if (node == NULL)
        return NULL;
    node->name = my_strdup((my_strcmp(info[0], "setenv") == 0)
            ? info[1] : info[0]);
    if (my_arrsize(info) >= get_lvl + 1) {
        for (int i = get_lvl + 1; info[i]; i++)
            info[get_lvl] = my_strcat((char *)info[get_lvl],
        my_strcat("=", (char *)info[i]));
    }
    node->var = my_strdup((my_strcmp(info[0], "setenv") == 0)
            ? info[2] : info[1]);
    node->prev = NULL;
    node->next = NULL;
    return node;
}

void free_node(env_v **node)
{
    if ((*node)->name != NULL)
        free((*node)->name);
    if ((*node)->var != NULL)
        free((*node)->var);
    if ((*node) != NULL)
        free(*node);
}

void add_env_var(char const **info, env_list *list)
{
    list->size += 1;
    if (list->head == NULL) {
        list->head = init_env_var_node(info);
        list->tail = list->head;
        return;
    }
    list->tail->next = init_env_var_node(info);
    list->tail->next->prev = list->tail;
    list->tail = list->tail->next;
}

env_list *array_to_linkedlist(char **env)
{
    env_list *list = malloc(sizeof(env_list));
    char **line;

    if (list == NULL)
        return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->status = 0;
    for (int i = 0; env[i]; i++) {
        line = my_str_to_word_array(env[i], "=");
        if (line == NULL)
            return NULL;
        add_env_var((char const **)(line), list);
        free_tab(line);
    }
    return list;
}

char **linkedlist_to_array(env_list *list)
{
    char **env = malloc(sizeof(char *) * (list->size + 1));
    env_v *node = list->head;

    if (env == NULL)
        return NULL;
    env[list->size] = NULL;
    for (size_t i = 0; i < list->size; i++) {
        env[i] = my_strcat(my_strcat(node->name, "="), node->var);
        node = node->next;
    }
    return env;
}
