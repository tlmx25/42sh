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
        {'e',     backslash_e},
        {'f',     backslash_f},
        {'n',     backslash_n},
        {'r',     backslash_r},
        {'t',     backslash_t},
        {'v',     backslash_v},
};

static void check_spe_char(char const *command, int i)
{
    for (size_t check = 0; check < ARRAY_LENGTH(spe_char_list); check++) {
        if (spe_char_list[check].spe_char == command[i + 1])
            spe_char_list[check].fct();
    }
}

static int flag_n(char *command, int i, int flags)
{
    if (flags != 0) {
        if (command[i + 1] == '\0') {
            my_printf("%c", command[i]);
            return 1;
        }
    }
    return 0;
}

static void print_echo(char *command, int flags)
{
    for (int i = 5 + flags; command[i]; i++) {
        if (command[i] == '\\') {
            check_spe_char(command, i);
            i += 2;
        }
        if (flag_n(command, i, flags) == 1)
            break;
        if (!command[i + 1])
            my_printf("%c\n", command[i]);
        else
            my_printf("%c", command[i]);
    }
}

void my_echo_command(char const **info, UNU var_s *var)
{
    char *command = my_array_to_str_separator(info, " ");
    command[my_strlen(command)] = '\0';
    int flags = 0;

    if (!info[1]) {
        my_printf("\n");
        return;
    }
    if (my_strcmp(info[1], "-n") == 0)
        flags = 3;
    print_echo(command, flags);
    free(command);
}
