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

int compare_commands(var_s *data, char **commands, int i, char *command)
{
    node_t *temp_node = data->history->tail;

    for (;temp_node != NULL;temp_node = temp_node->prev) {
        if (my_strncmp(command, temp_node->command,
        my_strlen(command)) == 0) {
            commands[i] = my_strdup(temp_node->command);
            return 0;
        }
    }
    return 1;
}

void check_nbr_or_char(var_s *data, char **commands, int i)
{
    char *command = my_clean_string(commands[i],"!",1);

    if (my_str_isnum(command) == 1) {
        commands[i] = take_old_history(my_getnbr(command),data);
        free(command);
        return;
    }
    if (compare_commands(data,commands, i, command) == 0) {
        free(command);
        return;
    }
}

char *manage_command(char *command, var_s *data)
{
    char **temp_commands = my_str_to_word_array(command, ";");
    int i = 0;

    char *return_command = NULL;

    for (;temp_commands[i] != NULL;i++) {
        if (temp_commands[i][0] == '!') {
            check_nbr_or_char(data, temp_commands, i);
        }
    }
    if (temp_commands[1] == NULL) {
        return_command = my_strdup(temp_commands[0]);
        free_tab(temp_commands);
        return return_command;
    }
    command = my_array_to_str_separator(AC temp_commands,";");
    free_tab(temp_commands);
    return command;
}
