/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** open_write_file.c
*/

#include <unistd.h>
#include <fcntl.h>
#include "mysh.h"

void open_write_list(var_list *list, char const *filepath, int fd_stdout)
{
    int fd = open(filepath, FLAG_ERASE, FLAG_PERM);

    if (fd == -1)
        return;
    dup2(fd, STDOUT_FILENO);
    for (var_node *node = list->head; node != NULL; node = node->next) {
        my_printf("%s=%s\n", node->name, node->var);
    }
    dup2(fd_stdout, STDOUT_FILENO);
}
