/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** open_write_file.c
*/

#include <unistd.h>
#include <stdio.h>
#include "mysh.h"

void open_write_list(var_list *list, char const *filepath) {
    FILE *file = fopen(filepath, "w+");

    if (file == NULL)
        return;
    for (var_node *node = list->head; node != NULL; node = node->next) {
        fprintf(file, "%s=%s", node->name, node->var);
    }
}