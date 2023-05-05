/*
** EPITECH PROJECT, 2023
** projet
** File description:
** init_history
*/

#include "mysh.h"
#include "history.h"

history_t *init_history(void)
{
    history_t *new_history = malloc(sizeof(history_t));

    new_history->head = NULL;
    new_history->tail = NULL;
    new_history->lengh = 1;
    return new_history;
}
