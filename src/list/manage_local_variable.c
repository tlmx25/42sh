/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** manage_local_variable.c
*/

#include "file_sh.h"
#include "mysh.h"

void print_list_variable(var_list *list, char separator)
{
    if (list == NULL)
        return;
    for (var_node *node = list->head; node != NULL; node = node->next)
        my_printf("%s%c%s\n", node->name, separator, node->var);
}

static void set_multiple_var(char const **info, var_s *var)
{
    var_node *node;
    char **name_value;

    for (size_t i = 1; info[i]; i++) {
        name_value = my_str_to_word_array(info[i], "=");
        if (name_value == NULL)
            continue;
        if (!my_str_isalpha_env(name_value[0], "set: ")) {
            STATUS = 1;
            return;
        }
        if ((node = find_node(name_value[0], LOCAL_VAR)) != NULL) {
            free(node->var);
            node->var = my_strdup(name_value[1]);
        } else
            add_var(AC name_value, LOCAL_VAR);
        open_write_list(LOCAL_VAR, LOCAL_VAR_FILE, var->dup_stdout);
        free_tab(name_value);
    }
}

void set_local_var(const char **info, var_s *var)
{
    if (my_arrsize(info) == 1) {
        print_list_variable(LOCAL_VAR, '\t');
        return;
    }
    set_multiple_var(info, var);
}

void unset_local_var(char const **info, var_s *var)
{
    if (my_arrsize(info) == 1) {
        write(2,"unset: Too few arguments.\n", 26);
        STATUS = 1;
        return;
    }
    for (size_t i = 1; info[i]; i++)
        delete_env_var(info[i], LOCAL_VAR);
    open_write_list(LOCAL_VAR, LOCAL_VAR_FILE, var->dup_stdout);
}
