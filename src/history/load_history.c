/*
** EPITECH PROJECT, 2023
** projet
** File description:
** load_history
*/

#include "mysh.h"
#include "file_sh.h"

int verif_read(char **commands)
{
    return 0;
}

void add_history(node_t *node, char **commands,var_s *data)
{
    node->command = my_strdup(commands[1]);
    node->date = my_strdup(commands[0]);
    node->indice = data->history->lengh;
    if (data->history->head == NULL) {
        node->next = NULL;
        node->prev = NULL;
        data->history->head = node;
        data->history->tail = node;
        return;
    }
    node->next = NULL;
    node->prev = data->history->tail;
    data->history->tail->next = node;
    data->history->tail = node;
    return;
}

int read_history(char *command,var_s *var)
{
    node_t *cell = NULL;
    char **commands = my_str_to_word_array(command, "=");

    if (verif_read(commands) == 1) {
        free_tab(commands);
        return 1;
    }
    cell = malloc(sizeof(node_t));
    add_history(cell, commands, var);
    free_tab(commands);
    return 0;
}

void load_history(var_s *data)
{
    char **content_file = open_read_content_file(
            get_nb_line_file(".history"), ".history");

    if (content_file == NULL)
        return;
    for (int i = 0;content_file[i] != NULL;i++) {
        read_history(content_file[i],data);
        if (data->history->tail != NULL)
            data->history->lengh = data->history->tail->indice + 1;
    }
    free_tab(content_file);
    return;
}
