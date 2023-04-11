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

char *verify_path(char const *arg, env_list *list)
{
    env_v *old_path;
    if (arg[0] == '-') {
        old_path = find_node("OLDPWD", list);
        if (old_path != NULL)
            return old_path->var;
        else
            return "";
    }
    return (char *)arg;
}

void cd_home_argument(char const **arg, env_list *list)
{
    env_v *home_var = find_node("HOME", list);
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

void cd_built_in(char const **arg, env_list *list)
{
    char *old_path = my_strcat("setenv=OLDPWD=", getcwd(NULL, 0));
    int nb_arg = my_arrsize(arg);
    if (nb_arg > 2) {
        my_printf("%z", CD_MANY_ARG);
        list->status = 1;
        return;
    }
    if (nb_arg == 1 || !my_strcmp(arg[1], "~")) {
        cd_home_argument(arg, list);
    } else {
        if (chdir(verify_path(arg[1], list)) == -1) {
            list->status = 1;
            my_printf("%z%z%z%z",((arg[1][0] == '-') ? "" : arg[1]),
            ": ", strerror(errno), ".\n");
            return;
        }
    }
    set_env(AC my_str_to_word_array(old_path,"="), list);
    find_node("PWD", list)->var = getcwd(NULL, 0);
}
