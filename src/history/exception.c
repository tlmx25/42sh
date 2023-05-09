/*
** EPITECH PROJECT, 2023
** projet
** File description:
** exception
*/

#include "mysh.h"

int verif_commands(var_s *data, char *command)
{
    node_t *temp_node = data->history->tail;

    for (;temp_node != NULL;temp_node = temp_node->prev) {
        if (my_strncmp(command, temp_node->command,
        my_strlen(command)) == 0) {
            return 0;
        }
    }
    return 1;
}

int check_name(var_s *data, char **commands, int i)
{
    char *command = my_clean_string(commands[i],"!",1);

    if (verif_commands(data,command) == 1) {
        return 1;
    }
    if (my_str_isnum(command) == 0) {
        return 1;
    }
    return 0;
}

int exception_detection(char *command,var_s *data)
{
    char **temp_commands = my_str_to_word_array(command, ";");
    int i = 0;
    int verif = 0;

    for (;temp_commands[i] != NULL;i++) {
        if (temp_commands[i][0] == '!') {
            verif = check_name(data, temp_commands, i);
        }
        if (verif == 1) {
            return 1;
        }
    }
    free_tab(temp_commands);
    return 0;
}
