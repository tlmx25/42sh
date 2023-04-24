/*
** EPITECH PROJECT, 2023
** B-PSU-200-REN-2-1-42sh-lea.allain
** File description:
** echo.c
*/

#include "mysh.h"

void my_echo_command(char const **info, var_s *var)
{
    if (!info[1]) {
        my_printf("\n");
        return;
    }
    for (int i = 1; info[i]; i++) {
        if (!info[i + 1])
            my_printf("%s\n", info[i]);
        else
            my_printf("%s ", info[i]);
    }
}
