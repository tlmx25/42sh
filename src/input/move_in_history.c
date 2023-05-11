/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** move_in_history
*/

#include "mysh.h"
int clean_line(int len, int cursor);

void move_in_history_up(var_s *var, char **input, int *cursor, int *len)
{
    if ((HISTORY->actual != NULL && HISTORY->actual->prev == NULL) ||
    HISTORY->tail == NULL) {
        return;
    }
    if (HISTORY->actual == NULL)
        HISTORY->actual = HISTORY->tail;
    else
        HISTORY->actual = HISTORY->actual->prev;
    free(*input);
    *input = my_strdup(HISTORY->actual->command);
    clean_line(*len, *cursor);
    *len = my_strlen(*input);
    *cursor = *len;
    my_printf("%s", *input);
}

void move_in_history_down(var_s *var, char **input, int *cursor, int *len)
{
    if (HISTORY->actual == NULL || HISTORY->tail == NULL) {
        return;
    }
    HISTORY->actual = HISTORY->actual->next;
    free(*input);
    *input = my_strdup((HISTORY->actual == NULL) ? "" :
    HISTORY->actual->command);
    clean_line(*len, *cursor);
    *len = my_strlen(*input);
    *cursor = *len;
    my_printf("%s", *input);
}
