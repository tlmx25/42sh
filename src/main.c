/*
** EPITECH PROJECT, 2023
** B-PSU-200-REN-2-1-minishell1-tom.lefoix
** File description:
** mysh.c
*/

#include "mysh.h"

int main(int ac, char **av, char **env)
{
    if (ac != 1 && my_strcmp(av[1], "-i") != 0)
        return 84;
    return mysh(ac, av, env);
}
