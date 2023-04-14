/*
** EPITECH PROJECT, 2023
** B-PSU-200-REN-2-1-minishell1-tom.lefoix
** File description:
** verify_env.c
*/

#include "error_mysh.h"
#include "mysh.h"

var_node *find_node(char const *name, var_list *list)
{
    var_node *node = list->head;
    while (node != NULL && my_strcmp(node->name, name) != 0)
        node = node->next;
    return node;
}

void verify_env(var_s *var)
{
    var_node *node;
    if (find_node("PWD", ENV_VAR) == NULL) {
        set_env(AC my_str_to_word_array(my_strcat("setenv=PWD=",
        getcwd(NULL, 0)), "="), var);
    }
    if ((node = find_node("SHLVL", ENV_VAR)) == NULL) {
        set_env(AC my_str_to_word_array("setenv=SHLVL=1", "="), var);
    } else {
        node->var = my_putnbrm(my_getnbr(node->var) + 1);
    }
    if (find_node("PATH", ENV_VAR) == NULL) {
        set_env(AC my_str_to_word_array("setenv=PATH=/bin:/usr/bin:/usr",
        "="), var);
    }
}

int my_str_isalpha_env(char const *str, char const *command)
{
    if (str == NULL)
        return 0;
    if (!is_alpha(str[0]) && str[0] != '_') {
        my_printf("%z%z", command, VAR_STR_LET);
        return 0;
    }
    for (int i = 0; str[i]; i++) {
        if (str[i] == '_')
            continue;
        if ((str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z') &&
            (str[i] < '0' || str[i] > '9')) {
            my_printf("%z%z", command, VAR_CTN_AN);
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
