/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** manage_input
*/

#include "mysh.h"

void manage_input(char **input, var_s *var)
{
    size_t len = 0;
    int value;

    if (isatty(STDIN_FILENO))
        write(1,"$> ", 3);
    if (isatty(STDIN_FILENO) && var->mode == EDITING)
        value = my_getline(input);
    else
        value = (int)getline(input, &len, stdin);
    if (value == EOF) {
        free(*input);
        exit_function(NULL, var);
    }
    input[0][value - 1] = '\0';
}
