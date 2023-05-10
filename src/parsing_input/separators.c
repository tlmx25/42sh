/*
** EPITECH PROJECT, 2022
** B-PSU-200-REN-2-1-42sh-arthur.doriel
** File description:
** separators.c
*/

#include "mysh.h"

int check_if_separators(char *input)
{
    for (int i = 0; i < my_strlen(input); i++) {
        if ((input[i] == '&' && (i + 1 < my_strlen(input)) &&
        input[i + 1] == '&') || (input[i] == '|' && (i + 1 < my_strlen(input))
        && input[i + 1] == '|'))
            return 1;
    }
    return 0;
}

static int check_command(char **input, var_s *variable)
{
    get_command(variable, input);
    if (variable->env_var->status == 0)
        return 1;
    return 0;
}

static int check_which_separator(char **input, char *cmd)
{
    int i = 0;

    for (; input[i] != NULL; i++) {
        if (my_strcmp(input[i], cmd) == 0)
            break;
    }
    if (i > 0 && my_strcmp(input[i - 1], "&&") == 0)
        return 1;
    if (i > 0 && my_strcmp(input[i - 1], "||") == 0)
        return 2;
    return 0;
}

static int check_loop(int check, char **cmd, var_s *var, char **tab_with_sep)
{
    if (check_which_separator(tab_with_sep, cmd[0]) == 1) {
        if (check == 1)
        check = check_command(cmd, var);
        return check;
    }
    if (check_which_separator(tab_with_sep, cmd[0]) == 2) {
        if (check != 1)
            check = check_command(cmd, var);
    }
    return check;
}

char **handle_separators(char **input, int i, var_s *var)
{
    char **tab_with_sep = my_str_to_word_array(input[i], " ");
    char **line = tab_cut_separators(input[i]);
    char **cmd = my_str_to_word_array(line[0], " ");
    int check = check_command(cmd, var);
    int j = 1;

    for (; line[j + 1] != NULL; j++) {
        cmd = my_str_to_word_array(line[j], " ");
        check = check_loop(check, cmd, var, tab_with_sep);
    }
    cmd = my_str_to_word_array(line[j], "");
    if ((check_which_separator(tab_with_sep, cmd[0]) == 2 && check == 1) ||
    check == 0)
        return NULL;
    return cmd;
}
