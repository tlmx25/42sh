/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** set_status_variable
*/

#include "mysh.h"

void set_status_variable(var_s *var)
{
    var_node *status = find_node("?", LOCAL_VAR);
    char *str_status = my_putnbrm(STATUS);
    char **info = NULL;
    char *tmp = NULL;

    if (str_status == NULL)
        return;
    if (status != NULL) {
        free(status->var);
        status->var = str_status;
    } else {
        tmp = my_strcat("?=", str_status);
        info = my_str_to_word_array(tmp, "=");
        add_var(AC info, LOCAL_VAR);
        free(tmp);
        free_tab(info);
        free(str_status);
    }
}
