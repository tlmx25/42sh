/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** init_sh.c
*/

#include "file_sh.h"
#include "mysh.h"

static int init_list(var_s *var, char const **env)
{
    if (var == NULL)
        return 84;
    ENV_VAR = array_to_linkedlist(env);
    LOCAL_VAR = init_list_variable(LOCAL_VAR_FILE);
    ALIAS = init_list_variable(ALIAS_FILE);
    if (ENV_VAR == NULL || LOCAL_VAR == NULL || ALIAS == NULL) {
        return 84;
    }
    verify_env(var);
    if (ENV_VAR->head == NULL)
        return 84;
    return 0;
}

var_s *init_sh(char const **env)
{
    var_s *var = malloc(sizeof(var_s));

    if (init_list(var, env) == 84) {
        free(var);
        return NULL;
    }
    var->fd_redirection_out = 1;
    var->fd_redirection_in = 0;
    var->dup_stdout = dup(STDOUT_FILENO);
    var->dup_stdin = dup(STDIN_FILENO);
    var->pid_list = NULL;
    return var;
}
