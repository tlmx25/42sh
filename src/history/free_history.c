/*
** EPITECH PROJECT, 2023
** projet
** File description:
** free_history
*/

#include "mysh.h"

void free_history(var_s *var)
{
    clear_history(var);
    free(HISTORY);
}
