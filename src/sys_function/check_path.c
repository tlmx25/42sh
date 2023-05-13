/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** check_path
*/

#include "error_mysh.h"
#include "mysh.h"

char *check_path(char *command, char **path)
{
    char *path_temp = NULL;

    for (size_t i = 0; (my_str_in_str(command, "/") == 0)
    && IS_NULL(path)[i]; i++) {
        if (my_str_in_str(command, "/"))
            break;
        path_temp = my_strcat_free(my_strcat(IS_NULL(path)[i], "/"),
        command, 1, 0);
        if (!access(path_temp, F_OK)) {
            return path_temp;
        }
        free(path_temp);
    }
    my_printf("%z%z", my_clean_string(command, "\\", 1), CMD_NOT_FOUND);
    return NULL;
}
