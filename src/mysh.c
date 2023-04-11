/*
** EPITECH PROJECT, 2023
** B-PSU-200-REN-2-1-minishell1-tom.lefoix
** File description:
** mysh.c
*/

#include "mysh.h"

static const command_l command_list[] = {
        {"env", print_env_list},
        {"unsetenv", unset_env},
        {"setenv", set_env},
        {"exit", exit_function},
        {"cd", cd_built_in},
        {"/usr/bin/env", print_env_list}
};

int is_built_in(char *command)
{
    for (size_t i = 0; i < ARRAY_LENGTH(command_list); i++) {
        if (my_str_in_str(command, command_list[i].command))
            return 1;
    }
    return 0;
}

void get_command(var_s *variable, char **input)
{
    if (input == NULL)
        return;
    if (my_strcmp( input[0], command_list[3].command) == 0) {
        close(variable->dup_stdin);
        close(variable->dup_stdout);
        exit_function(AC input, variable->list);
    }
    for (size_t i = 0; i < ARRAY_LENGTH(command_list); i++) {
        if (my_strcmp(command_list[i].command, input[0]) == 0) {
            command_list[i].fct(AC input, variable->list);
            return;
        }
    }
    exec_sys_function(variable, input);
    free_tab(input);
}

void bash_loop(var_s *variable)
{
    char *input = NULL;
    size_t len = 0;

    while (1) {
        if (isatty(STDIN_FILENO))
            write(1,"$> ", 3);
        if (getline(&input, &len, stdin) == EOF)
            exit_function(NULL, variable->list);
        input[my_strlen(input) - 1] = '\0';
        if (my_get_first_char(input, " \t") != '\0')
            separate_command_comma(variable, input);
        free(input);
        input = NULL;
    }
}

int mysh(UNU int ac, UNU char **av, char **env)
{
    var_s variable;
    variable.list = array_to_linkedlist(env);
    signal(SIGINT, SIG_IGN);
    if (variable.list == NULL) {
        return 1;
    }
    verify_env(variable.list);
    if (variable.list->head == NULL) {
        exit(84);
    }
    variable.fd_redirection_out = 1;
    variable.fd_redirection_in = 0;
    variable.dup_stdout = dup(STDOUT_FILENO);
    variable.dup_stdin = dup(STDIN_FILENO);
    variable.pid_list = NULL;
    bash_loop(&variable);
    return 0;
}
