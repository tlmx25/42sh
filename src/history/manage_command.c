/*
** EPITECH PROJECT, 2023
** projet
** File description:
** manage_command
*/

#include "mysh.h"

char *take_old_history(int nbr, var_s *data)
{
    node_t *temp_node = data->history->head;

    for (;temp_node != NULL;temp_node = temp_node->next) {
        if (temp_node->indice == nbr) {
            return my_strdup(temp_node->command);
        }
    }
    return NULL;
}

char *manage_command(char *command, var_s *data)
{
    char **temp_commands = my_str_to_word_array(command, ";");
    int i = 0;

    for (;temp_commands[i] != NULL;i++) {
        if (temp_commands[i][0] == '!')
            temp_commands[i] = take_old_history(my_getnbr(temp_commands[i])
            ,data);
    }
    command = my_array_to_str_separator(temp_commands," ");
    free_tab(temp_commands);
    return command;
}
