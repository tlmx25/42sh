/*
** EPITECH PROJECT, 2023
** B-PSU-200-REN-2-1-minishell1-tom.lefoix
** File description:
** array_to_linkedlist.c
*/

#include "mysh.h"

var_node *init_env_var_node(char const **info)
{
    var_node *node = malloc(sizeof(var_node));
    int start = (is_built_in(SC info[0])) ? 1 : 0;

    if (node == NULL)
        return NULL;
    node->name = my_strdup(info[start]);
    node->var = my_array_to_str_separator(&info[start + 1], " ");
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void free_node(var_node **node)
{
    if ((*node)->name != NULL)
        free((*node)->name);
    if ((*node)->var != NULL)
        free((*node)->var);
    if ((*node) != NULL)
        free(*node);
}

void add_var(char const **info, var_list *list)
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

var_list *array_to_linkedlist(const char **env)
{
    var_list *list = malloc(sizeof(var_list));
    char **line;

    if (list == NULL)
        return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->status = 0;
    if (env == NULL)
        return list;
    for (int i = 0; env[i]; i++) {
        line = my_str_to_word_array(env[i], "=");
        if (line == NULL)
            continue;
        add_var((char const **) (line), list);
        free_tab(line);
    }
    return list;
}

char **linkedlist_to_array(var_list *list)
{
    char **env = malloc(sizeof(char *) * (list->size + 1));
    var_node *node = list->head;
    char *tmp;

    if (env == NULL)
        return NULL;
    env[list->size] = NULL;
    for (size_t i = 0; i < list->size; i++) {
        tmp = my_strcat(node->name, "=");
        env[i] = my_strcat(tmp, node->var);
        free(tmp);
        node = node->next;
    }
    return env;
}
