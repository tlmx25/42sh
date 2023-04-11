/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** exit_function.c
*/

#include "mysh.h"

void exit_function(char const **arg, env_list *list)
{
    char exit_status = (char)list->status;

    if (arg != NULL && arg[1] != NULL && my_getnbr(arg[1]) != -898998) {
        exit_status = (char)my_getnbr(arg[1]);
        my_printf("test : %i\n", my_getnbr(arg[1]));
    } else if (my_arrsize(arg) != 1 && arg != NULL) {
        write(2, "exit: Expression Syntax.\n", 25);
        return;
    }
    free_env(&list);
    if (arg == NULL)
        free_tab((char **)arg);
    if (isatty(STDIN_FILENO))
        my_printf("exit\n");
    exit(exit_status);
}
