/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** list_manager.c
*/

#include "mysh.h"

int *add_pid(int *actual_list, int pid)
{
    size_t size = 0;
    int *new_list;
    for (; actual_list[size] != -2; size++);
    new_list = malloc(sizeof(int) * (size + 2));
    if (new_list == NULL)
        return actual_list;
    new_list[size + 1] = -2;
    for (size_t i = 0; i < size; i++) {
        new_list[i] = actual_list[i];
    }
    new_list[size] = pid;
    free(actual_list);
    return new_list;
}
