/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** check_local_var
*/

#include "mysh.h"

static const var_node default_variable[] = {
        {"term", "term=42sh-256color", NULL, NULL},
        {"ignoreof", "ignoreof=off", NULL, NULL},
        {"?", "?=0", NULL, NULL},
};

static void set_cwd_variable(var_s *var)
{
    char **tmp = NULL;
    char *pwd = getcwd(NULL, 0);
    char *str_tmp = NULL;

    str_tmp = my_strcat("set cwd=", pwd);
    tmp = my_str_to_word_array(str_tmp, " ");
    set_local_var(AC tmp, var);
    free(str_tmp);
    free(pwd);
    free_tab(tmp);
}

void check_local_var(var_s *var)
{
    char **tmp;
    var_node *node;

    for (size_t i = 0; i < ARRAY_LENGTH(default_variable); i++) {
        node = find_node(default_variable[i].name, LOCAL_VAR);
        if (node != NULL) {
            delete_env_var(default_variable[i].name, LOCAL_VAR);
        }
        tmp = my_str_to_word_array(default_variable[i].var, "=");
        if (tmp == NULL)
            continue;
        add_var(AC tmp, LOCAL_VAR);
        free_tab(tmp);
    }
    set_cwd_variable(var);
}
