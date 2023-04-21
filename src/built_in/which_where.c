/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** which_where
*/

#include "error_mysh.h"
#include "mysh.h"

static char *get_valid_pass_w(char const *command, var_list *list)
{
    char **path = NULL;
    char *path_temp;

    path = my_str_to_word_array(IS_NULL_N(find_node("PATH", list)), ":");
    for (size_t i = 0; path != NULL && path[i]; i++) {
        path_temp = my_strcat(my_strcat(IS_NULL(path)[i], "/"), command);
        if (!access(path_temp, F_OK)) {
            free_tab(path);
            return path_temp;
        }
        free(path_temp);
    }
    free_tab(path);
    return NULL;
}

void my_which_command(char const **info, var_s *var)
{
    char *tmp;
    int status;

    for (size_t i = 1; info[i]; i++) {
        if (is_built_in(info[i])) {
            my_printf("%s%s", info[i], SH_BUILT_CMD);
            status = 1;
        }
        tmp = get_valid_pass_w(info[i], ENV_VAR);
        if (tmp == NULL && !status) {
            STATUS = 1;
            my_printf("%z%z", info[i], CMD_NOT_FOUND);
        } else
            my_printf("%s%c", tmp, (status) ? '\0' : '\n' );
        free(tmp);
        status = 0;
    }
}
