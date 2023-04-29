/*
** EPITECH PROJECT, 2022
** B-PSU-200-REN-2-1-42sh-arthur.doriel
** File description:
** separators.c
*/

#include "mysh.h"

int check_if_separators(char *input)
{
    for (int i = 0; input[i] != '\n'; i++) {
        if ((input[i] == '&' && input[i + 1] == '&') ||
        (input[i] == '|' && input[i + 1] == '|'))
            return 1;
    }
    return 0;
}

static int check_command(char **input, var_s *variable, int i, int fd[2])
{
    int error = 0;

    exec_command_pipe(input, fd, variable, i);
    for (int i = 0; variable->pid_list[i] != -2; i++) {
        waitpid(variable->pid_list[i], &error, 0);
        if (WEXITSTATUS(error) != 0)
            variable->env_var->status = WEXITSTATUS(error);
    }
    printf("status = %d\n", variable->env_var->status);
    if (variable->env_var->status == 0)
        return 1;
    free(variable->pid_list);
    return 0;
    // si marche
}

void handle_separators(char **input, int i, var_s *var, int fd[2])
{
    printf("execute separators\n");
    char **line = my_str_to_word_array(input[i], " ");
    int check = check_command(line, var, i, fd);

    for (int i = 1; line[i] != NULL; i++) {
        if (my_strcmp(line[i], "&&") != 0 && my_strcmp(line[i], "||") != 0) {
            // si symbole avant = &&
            if (my_strcmp(line[i - 1], "&&") == 0) {
                // si cmd d'avant marche -> check = si cmd actu marche ou pas
                if (check == 1)
                    check = check_command(line, var, i, fd);
                break;
            }
            // si symbole avant = ||
            if (my_strcmp(line[i - 1], "||") == 0) {
                // si cmd d'avant ne marche pas -> check = exec cmd actu
                if (check != 1)
                    check = check_command(line, var, i, fd);
                break;
            }
        }
    }
}
