/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** alias.c
*/

#include "file_sh.h"
#include "mysh.h"

void add_alias(char const **info, var_s *var)
{
    var_node *node;

    if (my_arrsize(info) == 1) {
        print_list_variable(ALIAS, '\t');
        return;
    }
    if ((node = find_node(info[1], ALIAS)) != NULL) {
        free(node->var);
        node->var = my_array_to_str_separator(&info[2], " ");
    } else
        add_var(AC info, ALIAS);
    open_write_list(ALIAS, ALIAS_FILE, var->dup_stdout);
}

void unset_alias(char const **info, var_s *var)
{
    if (my_arrsize(info) == 1) {
        write(2, "unalias: Too few arguments.\n", 29);
        STATUS = 1;
        return;
    }
    for (size_t i = 1; info[i]; i++)
        delete_env_var(info[i], LOCAL_VAR);
    open_write_list(LOCAL_VAR, LOCAL_VAR_FILE, var->dup_stdout);
}

char *check_alias(char *command, var_s *var)
{
    var_node *node;
    char **tmp = my_str_to_word_array(command, " \t");

    if (tmp == NULL)
        return command;
    if (!(node = find_node(tmp[0], ALIAS))) {
        free_tab(tmp);
        return command;
    }
    tmp[0] = my_strdup(node->var);
    free(command);
    command = my_array_to_str_separator( AC tmp, " ");
    free_tab(tmp);
    return check_alias(command, var);

}
