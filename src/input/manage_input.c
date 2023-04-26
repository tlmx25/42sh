/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** manage_input
*/

#include "mysh.h"

int clean_line(int len, int cursor)
{
    for (size_t i = 0; (int)i != (len - cursor); i++)
        my_printf("\033[C");
    for (size_t i = 0; (int)i < len && len != 0; i++)
        my_printf("\b \b");
    return -1;
}

void manage_input(char **input, var_s *var)
{
    size_t len = 0;
    int value;
    var_node *node = find_node("ignoreof", LOCAL_VAR);

    if (isatty(STDIN_FILENO)) {
        set_prompt(var);
        my_printf("%s ", var->prompt);
    }
    if (isatty(STDIN_FILENO) && var->mode == EDITING)
        value = my_getline(input, var);
    else
        value = (int)getline(input, &len, stdin);
    if (value == EOF && my_strcmp(IS_NN(node), "on") != 0) {
        free(*input);
        exit_function(NULL, var);
    }
    input[0][value - 1] = '\0';
}
