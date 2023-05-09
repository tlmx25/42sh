/*
** EPITECH PROJECT, 2023
** projet
** File description:
** save_history
*/

#include <unistd.h>
#include <fcntl.h>
#include "mysh.h"
#include "history.h"

void save_history(var_s *data, int fd_stdout)
{
    int fd = open(".history", FLAG_ERASE, FLAG_PERM);

    if (fd == -1)
        return;
    dup2(fd, STDOUT_FILENO);
    for (node_t *temp_node = data->history->head; temp_node != NULL
    ; temp_node = temp_node->next) {
        my_printf("%s=%s\n", temp_node->date,temp_node->command);
    }
    dup2(fd_stdout, STDOUT_FILENO);
}
