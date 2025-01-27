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

static int check_command(char **input, var_s *var)
{
    char **copy = copystringarray(input);
    get_command(var, copy);
    if (STATUS == 0)
        return 1;
    return 0;
}

static int check_which_separator(char **input, char *cmd, char *arg)
{
    int i = 0;

    for (; input[i] != NULL; i++) {
        if (my_strcmp(input[i], cmd) == 0 && arg == NULL)
            break;
        if (my_strcmp(input[i], cmd) == 0 && my_strcmp(input[i + 1], arg) == 0)
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
    if (check_which_separator(tab_with_sep, cmd[0], cmd[1]) == 1) {
        if (check == 1)
            check = check_command(cmd, var);
        return check;
    }
    if (check_which_separator(tab_with_sep, cmd[0], cmd[1]) == 2) {
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

    STATUS = 0;
    for (; line[j + 1] != NULL; j++) {
        cmd = my_str_to_word_array(line[j], " ");
        check = check_loop(check, cmd, var, tab_with_sep);
        STATUS = 0;
    }
    cmd = my_str_to_word_array(line[j], " ");
    if ((check_which_separator(tab_with_sep, cmd[0], cmd[1]) == 2 &&
    check == 1) || (check_which_separator(tab_with_sep, cmd[0], cmd[1]) == 1
    && check == 0)) {
        free(cmd);
        cmd = NULL;
    } free_tab(tab_with_sep);free_tab(line);
    return cmd;
}
