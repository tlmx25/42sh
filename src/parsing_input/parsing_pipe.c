/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** parsing_pipe.c
*/

#include "mysh.h"

char **input_after(char **input, char **cmd, int i)
{
    input = my_delline(input, i);
    char *command = NULL;

    command = my_array_to_str_separator(AC cmd, " ");
    if (input[0] == NULL || input == NULL) {
        input = malloc(sizeof(char *) * 2);
        input[0] = my_strdup(command);
        input[1] = NULL;
    } else {
        input = my_appendline_index(input, command, i);
    }
    return input;
}

void exec_loop(var_s *variable, char **input, int fd[2])
{
    char **cmd = NULL;
    int check = 0;

    for (int i = 0; input[i]; i++) {
        if (check == 1)
            i--;
        if (check_if_separators(input[i])) {
            cmd = handle_separators(input, i, variable);
            check = 1;
        }
        if (cmd == NULL && check == 1)
            continue;
        if (cmd != NULL)
            input = input_after(input, cmd, i);
        if (exec_command_pipe(input, fd, variable, i))
            break;
        cmd = NULL;
        check = 0;
    }
    free_tab(cmd);
}

void parsing_pipe(var_s *variable, char **input)
{
    int fd[2];

    if (check_variable(input, variable))
        return;
    if (pipe(fd) == -1)
        return;
    exec_loop(variable, input, fd);
    close(fd[0]);
}
