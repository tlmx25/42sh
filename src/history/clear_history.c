/*
** EPITECH PROJECT, 2023
** projet
** File description:
** clear_history
*/

#include "mysh.h"
#include "history.h"

void clear_history(var_s *var)
{
    node_t *temp_node = HISTORY->head;

    if (temp_node == NULL)
        return;
    for (;temp_node->next != NULL;temp_node = temp_node->next) {
        free(temp_node->command);
        free(temp_node->date);
        if (temp_node->prev != NULL)
            free(temp_node->prev);
    }
    free(temp_node->command);
    free(temp_node->date);
    free(temp_node);
    HISTORY->head = NULL;
    HISTORY->tail = NULL;
    return;
}
