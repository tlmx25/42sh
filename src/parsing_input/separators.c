/*
** EPITECH PROJECT, 2022
** B-PSU-200-REN-2-1-42sh-arthur.doriel
** File description:
** separators.c
*/

#include "mysh.h"

int check_if_separators(char *input)
{
    for (int i = 0; input[i] != '\n'; i++) {
        if ((input[i] == '&' && input[i + 1] == '&') ||
        (input[i] == '|' && input[i + 1] == '|'))
            return 1;
    }
    return 0;
}

void handle_separators(char *input)
{
    printf("execute separators\n");
}
