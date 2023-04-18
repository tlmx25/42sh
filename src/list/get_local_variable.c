/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** get_local_variable.c
*/

#include "file_sh.h"
#include "error_mysh.h"
#include "mysh.h"


var_list *init_list_variable(char const *filepath)
{
    char **content_file = open_read_content_file(
    get_nb_line_file(filepath), filepath);
    var_list *list;

    list = array_to_linkedlist((char const **)content_file);
    free_tab(content_file);
    return list;
}

static int check_simple_variable(char **command, var_s *var)
{
    var_node *node;

    for (size_t i = 0; command[i]; i++) {
        if (command[i][0] != '$' || command[i][1] == '\0')
            continue;
        node = find_node(&command[i][1], LOCAL_VAR);
        if (node == NULL)
            node = find_node(&command[i][1], ENV_VAR);
        if (node == NULL) {
            my_printf("%z%z", &command[i][1], UDF_VAR);
            return 1;
        }
        free(command[i]);
        command[i] = my_strdup(node->var);
    }
    return 0;
}

int check_variable(char **all_command, var_s *var)
{
    char **command;
    int status = 0;

    for (size_t i = 0; all_command[i] && !status; i++) {
        command = my_str_to_word_array(all_command[i], " \t");
        status = check_simple_variable(command, var);
        free(all_command[i]);
        all_command[i] = my_array_to_str_separator(AC command, " ");
        free_tab(command);
    }
    STATUS = status;
    return status;
}
