/*
** EPITECH PROJECT, 2023
** B-PSU-200-REN-2-1-minishell1-tom.lefoix
** File description:
** cd_built_in.c
*/

#include <string.h>
#include <errno.h>
#include "mysh.h"
#include "error_mysh.h"

char *verify_path(char const *arg, var_list *list)
{
    var_node *old_path;
    if (arg[0] == '-') {
        old_path = find_node("OLDPWD", list);
        if (old_path != NULL)
            return old_path->var;
        else
            return "";
    }
    return (char *)arg;
}

void cd_home_argument(char const **arg, var_list *list)
{
    var_node *home_var = find_node("HOME", list);
    if (home_var == NULL && my_arrsize(arg) == 1) {
        my_printf("%z", CD_NO_HOME_DIR);
        list->status = 1;
        return;
    }
    if (home_var == NULL && !my_strcmp(arg[1], "~")) {
        my_printf("%z", CD_NO_HOME_SET);
        list->status = 1;

        return;
    }
    if (chdir(home_var->var) == -1) {
        perror(home_var->var);
        list->status = 1;
    }
}

void cd_built_in(char const **arg, var_s *var)
{
    char *old_path = my_strcat("setenv=OLDPWD=", getcwd(NULL, 0));
    int nb_arg = my_arrsize(arg);
    if (nb_arg > 2) {
        my_printf("%z", CD_MANY_ARG);
        STATUS = 1;
        return;
    }
    if (nb_arg == 1 || !my_strcmp(arg[1], "~")) {
        cd_home_argument(arg, ENV_VAR);
    } else {
        if (chdir(verify_path(arg[1], ENV_VAR)) == -1) {
            STATUS = 1;
            my_printf("%z%z%z%z",((arg[1][0] == '-') ? "" : arg[1]),
            ": ", strerror(errno), ".\n");
            return;
        }
    }
    set_env(AC my_str_to_word_array(old_path,"="), var);
    find_node("PWD", ENV_VAR)->var = getcwd(NULL, 0);
}
