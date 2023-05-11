/*
** EPITECH PROJECT, 2023
** projet
** File description:
** save_history
*/

#include <unistd.h>
#include <fcntl.h>
#include "mysh.h"
#include "file_sh.h"
#include "history.h"

void save_history(var_s *var, int fd_stdout)
{
    int fd;

    if (HISTORY == NULL || HISTORY->head == NULL)
        return;
    fd = open(HIS_FILE, FLAG_ERASE, FLAG_PERM);
    if (fd == -1)
        return;
    dup2(fd, STDOUT_FILENO);
    for (node_t *temp_node = HISTORY->head; temp_node != NULL
    ; temp_node = temp_node->next) {
        my_printf("%s=%s\n", temp_node->date,temp_node->command);
    }
    dup2(fd_stdout, STDOUT_FILENO);
    close(fd);
}
