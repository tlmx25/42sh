/*
** EPITECH PROJECT, 2023
** projet
** File description:
** !base
*/

#include "mysh.h"
#include "history.h"

void execute_command(char *input,var_s *var)
{
    int *tmp;

    if (input == NULL)
        return;
    tmp = var->pid_list;
    separate_command_comma(var,input);
    var->pid_list = tmp;
}

int compare_history(int nbr, var_s *var, char **commands)
{
    node_t *temp_node = NULL;

    if (HISTORY == NULL || HISTORY->head == NULL)
        return 1;
    temp_node = HISTORY->head;
    for (;temp_node->next != NULL;temp_node = temp_node->next) {
        if (temp_node->indice == nbr) {
            free(commands[0]);
            commands[0] = temp_node->command;
            return 0;
        }
    }
    return 1;
}

void take_excla(char **command, var_s *data)
{
    int indice = 0;

    if (command[0][0] == '!' && command[0][1] == '\0') {
        my_printf("!: Command not found.\n");
        return;
    }
    command[0] = my_clean_string(command[0],"!",1);
    if (my_str_isnum(command[0]) == 0) {
        my_printf("%s: Event not found.\n", command[0]), free(command[0]);
        return;
    }
    indice = my_getnbr(command[0]);
    if (compare_history(indice, data, command) == 1) {
        my_printf("%s: Event not found.\n", command[0]), free(command[0]);
        return;
    }
    execute_command(command[0], data);
    free(command[0]);
}
