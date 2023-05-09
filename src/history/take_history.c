/*
** EPITECH PROJECT, 2023
** projet
** File description:
** take_history
*/

#include "history.h"
#include "mysh.h"

char *take_time(void)
{
    time_t timestamp = time(NULL);
    struct tm * pTime = localtime(&timestamp);
    char *time = NULL;
    char *buffer = malloc(sizeof(char) * 1000);

    strftime(buffer,1000,"%H:%M", pTime);
    time = my_strdup(buffer);
    free(buffer);
    return time;
}

int void_command(char *buffer)
{
    for (int i = 0;buffer[i] != '\0';i++) {
        if (buffer[i] != ' ')
            return 1;
    }
    return 0;
}

void add_link_list(node_t *node, char *command,var_s *var)
{
    node->command = command;
    node->date = take_time();
    node->indice = HISTORY->lengh;
    if (HISTORY->head == NULL) {
        node->next = NULL;
        node->prev = NULL;
        HISTORY->head = node;
        HISTORY->tail = node;
        return;
    }
    node->next = NULL;
    node->prev = HISTORY->tail;
    HISTORY->tail->next = node;
    HISTORY->tail = node;
    return;
}

void take_history(char *command,var_s *var)
{
    node_t *cell = NULL;

    if (void_command(command) == 0 || exception_detection(command, var) == 1)
        return;
    cell = malloc(sizeof(node_t));
    command = manage_command(command, var);
    add_link_list(cell, command, var);
    HISTORY->lengh += 1;
    return;
}
