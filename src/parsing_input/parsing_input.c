/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** parsing_input.c
*/

#include "mysh.h"
#include "error_mysh.h"

static int have_name(char const *str, char const *skip_char,
char const *stop_char, int start)
{
    int i = start;

    if (str[i] == '>' || str[i] == '<')
        i++;
    for (; str[i]; i ++) {
        if (is_separator(skip_char, str[i]))
            continue;
        if (is_separator(stop_char, str[i]))
            return 0;
        return 1;
    }
    return 0;
}

static int verify_ambiguous_redirect(char const *input)
{
    int nb_redirect = 0;

    for (int i = 0; input[i + 1]; i++) {
        if (input[i] == ';')
            nb_redirect = 0;
        if (input[i] == '>' && input[i + 1] != '>')
            nb_redirect++;
        if ((input[i] == '|' && nb_redirect) || nb_redirect > 1) {
            my_printf("%z", AMB_RDRECT);
            return 1;
        }
    }

    return 0;
}

static int verify_name_redirect(char const *input)
{
    int nb_redirect = 0;

    for (int i = 0; input[i]; i++) {
        if (input[i] == '|' || input[i] == ' ')
            continue;
        if (input[i] == '>' || input[i] == '<')
            nb_redirect++;
        else
            nb_redirect = 0;
        if (nb_redirect > 2 || ((IS_RDRECT(input[i])) &&
        !have_name(&input[i], " \t", ";<>|", 1))) {
            my_printf("%z", MISS_NAME_RDRECT);
            return 1;
        }
    }

    return 0;
}

static int verify_invalid_null_cmd(char const *input)
{
    int pipe_activate = 0;
    if (!have_name(input, " \t", ";<>|", 0))
        pipe_activate++;
    if (my_get_first_char(input, " \t") == '|') {
        my_printf("%z", INV_NULL_CMD);
        return 1;
    }
    for (int i = 0; input[i]; i++) {
        if (is_separator(" \t", input[i]))
            continue;
        if (input[i] == '|')
            pipe_activate += (input[i + 1] == '|') ? 0 : 1;
        else
            pipe_activate = 0;
        if (pipe_activate != 0 && !have_name(&input[i], " \t", ";<>|", 1)
        && my_strncmp(&input[i], "||", 2) != 0) {
            return my_printf("%z", INV_NULL_CMD);
        }
    }
    return 0;
}

void separate_command_comma(var_s *var, char *input)
{
    char **array_comma;

    if (verify_name_redirect(input) || verify_invalid_null_cmd(input) ||
    verify_ambiguous_redirect(input)) {
        STATUS = 1;
        return;
    }
    array_comma = my_str_to_word_array(input, ";");
    if (array_comma == NULL)
        return;
    for (int i = 0; array_comma[i]; i++) {
        STATUS = 0;
        verify_if_redirection(var, array_comma[i]);
    }
    free(array_comma);
}
