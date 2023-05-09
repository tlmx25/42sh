/*
** EPITECH PROJECT, 2023
** projet
** File description:
** history_base
*/

#include "mysh.h"
#include "history.h"

void print_nbr(int nbr)
{
    if (nbr < 10)
        my_printf("     ");
    if (nbr > 9)
        my_printf("    ");
    if (nbr > 99)
        my_printf("   ");
    if (nbr > 999)
        my_printf("  ");
    if (nbr > 9999)
        my_printf(" ");
}

void print_history(var_s *var,int nbr)
{
    node_t *temp_node;
    int i = 0;

    if (HISTORY == NULL || HISTORY->tail == NULL)
        return;
    temp_node = HISTORY->tail;
    for (;i != nbr - 1 && temp_node->prev != NULL;i++) {
        temp_node = temp_node->prev;
    }
    for (;temp_node != NULL;temp_node = temp_node->next) {
        print_nbr(temp_node->indice);
        my_printf("%d  ", temp_node->indice);
        my_printf("%s", temp_node->date);
        my_printf("   %s\n", temp_node->command);
    }
}

void history(char const **command,var_s *var)
{
    if (command[1] == NULL) {
        print_history(var, 100);
        return;
        }
    if (command[1][0] == '-' && command[1][1] == 'c'
    && command[1][2] == '\0') {
        clear_history(var);
        return;
    }
    if (my_str_isnum(command[1]) == 1) {
        print_history(var, my_getnbr(command[1]));
        return;
    }
    if (my_str_isnum(command[1]) == 0) {
        my_printf("history: Badly formed number.\n");
    }
}
