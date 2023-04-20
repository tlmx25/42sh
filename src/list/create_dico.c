/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** create
*/

#include "file_sh.h"
#include "mysh.h"

static var_node *init_dico_node(char const **info)
{
    var_node *node = malloc(sizeof(var_node));
    int start = 0;

    if (node == NULL)
        return NULL;
    node->name = my_strdup(info[start]);
    node->var = my_array_to_str_separator(&info[start + 1], " ");
    node->next = NULL;
    node->prev = NULL;
    return node;
}

static void add_var_dico(char const **info, var_list *list)
{
    list->size += 1;
    if (list->head == NULL) {
        list->head = init_dico_node(info);
        list->tail = list->head;
        return;
    }
    list->tail->next = init_dico_node(info);
    list->tail->next->prev = list->tail;
    list->tail = list->tail->next;
}

static var_list *array_to_linkedlist_dico(const char **env)
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
        add_var_dico((char const **) (line), list);
        free_tab(line);
    }
    return list;
}

var_list *init_dico(char const *filepath)
{
    char **content_file = open_read_content_file(
            get_nb_line_file(filepath), filepath);
    var_list *list;

    list = array_to_linkedlist_dico((char const **)content_file);
    free_tab(content_file);
    return list;
}
