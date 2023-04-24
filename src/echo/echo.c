/*
** EPITECH PROJECT, 2023
** B-PSU-200-REN-2-1-42sh-lea.allain
** File description:
** echo.c
*/

#include "mysh.h"

static const spe_char_t spe_char_list[] = {
        {'\\',    backslash_double},
        {'a',     backslash_a},
        {'b',     backslash_b},
        {'c',     backslash_c},
        {'e',     backslash_e},
        {'f',     backslash_f},
        {'n',     backslash_n},
        {'r',     backslash_r},
        {'t',     backslash_t},
        {'v',     backslash_v},
};

void check_spe_char(char *command, int i)
{
    for (size_t check = 0; check < ARRAY_LENGTH(spe_char_list); check++) {
        if (spe_char_list[check].spe_char == command[i + 1])
            spe_char_list[check].fct();
    }
}

void print_echo(char *command)
{
    for (int i = 5; command[i]; i++) {
        if (command[i] == '\\') {
            check_spe_char(command, i);
            i += 2;
        }
        if (!command[i + 1])
            my_printf("%c\n", command[i]);
        else
            my_printf("%c", command[i]);
    }
}

void my_echo_command(char const **info, var_s *var)
{
    char *command = my_array_to_str_separator(info, " ");
    command[my_strlen(command)] = '\0';

    if (!info[1]) {
        my_printf("\n");
        return;
    }
    print_echo(command);
}
