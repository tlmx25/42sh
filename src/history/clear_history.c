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
    node_t *next = NULL;
    if (temp_node == NULL)
        return;
    for (;temp_node->next != NULL;temp_node = next) {
        next = temp_node->next;
        free(temp_node->command);
        free(temp_node->date);
        free(temp_node);
    }
    free(temp_node->command);
    free(temp_node->date);
    free(temp_node);
    HISTORY->head = NULL;
    HISTORY->tail = NULL;
    return;
}
