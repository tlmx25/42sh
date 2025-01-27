/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** free_var.c
*/

#include "mysh.h"

void free_var(var_s *var)
{
    free_list(ENV_VAR);
    free_list(LOCAL_VAR);
    free_list(ALIAS);
    free_list(DICO);
    free_history(var);
    close(var->dup_stdin);
    close(var->dup_stdout);
    free(var->prompt);
    free(var);
}
