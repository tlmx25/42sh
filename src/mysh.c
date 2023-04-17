/*
** EPITECH PROJECT, 2023
** B-PSU-200-REN-2-1-minishell1-tom.lefoix
** File description:
** mysh.c
*/

#include "mysh.h"

static const command_l command_list[] = {
        {"env",          print_env_list},
        {"unsetenv",     unset_env},
        {"setenv",       set_env},
        {"exit",         exit_function},
        {"cd",           cd_built_in},
        {"/usr/bin/env", print_env_list},
        {"set",          set_local_var},
        {"unset",        unset_local_var},
        {"unalias",        unset_alias},
        {"alias",        add_alias},
};

int is_built_in(const char *command)
{
    for (size_t i = 0; i < ARRAY_LENGTH(command_list); i++) {
        if (my_str_in_str(command, command_list[i].command))
            return 1;
    }
    return 0;
}

void get_command(var_s *var, char **input)
{
    if (input == NULL)
        return;
    for (size_t i = 0; i < ARRAY_LENGTH(command_list); i++) {
        if (my_strcmp(command_list[i].command, input[0]) == 0) {
            command_list[i].fct(AC input, var);
            return;
        }
    }
    exec_sys_function(var, input);
    free_tab(input);
}

void bash_loop(var_s *var)
{
    char *input = NULL;
    size_t len = 0;

    while (1) {
        if (isatty(STDIN_FILENO))
            write(1,"$> ", 3);
        if (getline(&input, &len, stdin) == EOF)
            exit_function(NULL, var);
        input[my_strlen(input) - 1] = '\0';
        if (my_get_first_char(input, " \t") != '\0')
            separate_command_comma(var, input);
        free(input);
        input = NULL;
    }
}

int mysh(UNU int ac, UNU char **av, char **env)
{
    var_s *variable;
    signal(SIGINT, SIG_IGN);

    variable = init_sh((char const **)env);
    if (variable == NULL)
        return 84;
    bash_loop(variable);
    return 0;
}
