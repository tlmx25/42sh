/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** parsing_pipe.c
*/

#include "mysh.h"

void manage_child_part(char **input, var_s *var, int fd[2], int i)
{
    char **command = my_str_to_word_array(input[ABS(i)], " \t");

    if (command != NULL) {
        if (input[i + 1])
            dup2(fd[1], STDOUT_FILENO);
        get_command(var, command);
    }
    exit(var->env_var->status);
}

void manager_parent_part(int fd[2], var_s *variable, int pid, int last_pipe)
{
    int dup_0;

    variable->pid_list = add_pid(variable->pid_list, pid);
    dup2(fd[0], STDIN_FILENO);
    close(fd[1]);
    if (!last_pipe) {
        dup_0 = dup(fd[0]);
        pipe(fd);
        dup2(fd[1], dup_0);
        close(dup_0);
    }
}

void manager_last_part_built_in(var_s *variable, char *input, int fd[2])
{
    char **command = my_str_to_word_array(input, " \t");

    if (command == NULL)
        return;
    get_command(variable, command);
    dup2(fd[0], STDIN_FILENO);
    close(fd[1]);
}

int exec_command_pipe(char **input, int fd[2], var_s *var, int i)
{
    int pid;

    input[i] = check_alias(input[i], var);
    if (input[i + 1] == NULL && is_built_in(input[i])) {
        manager_last_part_built_in(var, input[i], fd);
        return 1;
    }
    pid = fork();
    if (pid == -1)
        return 1;
    if (pid == 0)
        manage_child_part(input, var, fd, i);
    else
        manager_parent_part(fd, var, pid, (input[i + 1]) ? 0 : 1);
    return 0;
}

void parsing_pipe(var_s *variable, char **input)
{
    int fd[2];

    if (check_variable(input, variable))
        return;
    if (pipe(fd) == -1)
        return;
    for (int i = 0; input[i]; i++) {
        printf("input = %s\n", input[i]);
        if (check_if_separators(input[i])) {
            handle_separators(input, i, variable);
            break;
            // si dernière cmd marche, la mettre en haut de l'input pour
            // pipe dessus
        }
        // input envoyé à cette fonction = transformé pour aller dans pipe
        if (exec_command_pipe(input, fd, variable, i))
            break;
    }
    close(fd[0]);
}
