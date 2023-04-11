/*
** EPITECH PROJECT, 2023
** B-PSU-200-REN-2-1-minishell1-tom.lefoix
** File description:
** verify_env.c
*/

#include "mysh.h"

env_v *find_node(char const *name, env_list *list)
{
    env_v *node = list->head;
    while (node != NULL && my_strcmp(node->name, name) != 0)
        node = node->next;
    return node;
}

void verify_env(env_list *list)
{
    env_v *node;
    if (find_node("PWD", list) == NULL) {
        set_env(AC my_str_to_word_array(my_strcat("setenv=PWD=",
        getcwd(NULL, 0)), "="), list);
    }
    if ((node = find_node("SHLVL", list)) == NULL) {
        set_env(AC my_str_to_word_array("setenv=SHLVL=1", "="), list);
    } else {
        node->var = my_putnbrm(my_getnbr(node->var) + 1);
    }
    if (find_node("PATH", list) == NULL) {
        set_env(AC my_str_to_word_array("setenv=PATH=/bin:/usr/bin:/usr",
        "="), list);
    }
}

int my_str_isalpha_env(char const *str)
{
    if (str == NULL)
        return 0;
    if (!is_alpha(str[0])  && str[0] != '_') {
        my_printf("%z", "setenv: Variable name must begin with a letter.\n");
        return 0;
    }
    for (int i = 0; str[i]; i++) {
        if (str[i] == '_')
            continue;
        if ((str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z') &&
            (str[i] < '0' || str[i] > '9')) {
            my_printf("%z", "setenv: Variable name must contain alphanumeric"
                            " characters.\n");
            return 0;
        }
    }
    return 1;
}

int my_str_isalphanum_env(char const *str)
{
    if (str == NULL)
        return 1;
    for (int i = 0; str[i]; i++) {
        if (is_separator(":-/.", str[i]))
            continue;
        if ((str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z') &&
            (str[i] < '0' || str[i] > '9')) {
            return 0;
        }
    }
    return 1;
}
