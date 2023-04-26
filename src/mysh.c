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
        {"which",        my_which_command},
        {"where",        my_where_command},
        {"echo",         my_echo_command},
};

int is_built_in(const char *command)
{
    for (size_t i = 0; i < ARRAY_LENGTH(command_list); i++) {
        if (my_str_in_str(command, command_list[i].command)) {
            return 1;
        }
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
            free_tab(input);
            return;
        }
    }
    exec_sys_function(var, input);
    free_tab(input);
}

void bash_loop(var_s *var)
{
    char *input = NULL;
    char *pre_cmd = NULL;

    while (1) {
        manage_input(&input, var);
        pre_cmd = my_strdup(IS_NN(find_node("precmd", ALIAS)));
        if (my_get_first_char(input, " \t") != '\0')
            separate_command_comma(var, input);
        if (pre_cmd != NULL)
            separate_command_comma(var, pre_cmd);
        free(input);
        free(pre_cmd);
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
    variable->mode = (ac != 1) ? CLASSIC : EDITING;
    bash_loop(variable);
    return 0;
}
