/*
** EPITECH PROJECT, 2023
** projet
** File description:
** free_history
*/

#include "mysh.h"
#include <stdlib.h>
#include "my.h"

void free_history(var_s *var)
{
    save_history(var, var->dup_stdout);
    clear_history(var);
    free(HISTORY);
    return;
}
