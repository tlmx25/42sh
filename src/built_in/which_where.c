/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** which_where
*/

#include "error_mysh.h"
#include "mysh.h"

static char *get_valid_pass_which(char const *command, var_list *list)
{
    char **path = NULL;
    char *path_temp = NULL;
    char *path_with_back = NULL;

    path = my_str_to_word_array(IS_NULL_N(find_node("PATH", list)), ":");
    for (size_t i = 0; path != NULL && path[i]; i++) {
        path_with_back = my_strcat(IS_NULL(path)[i], "/");
        path_temp = my_strcat(path_with_back, command);
        if (!access(path_temp, F_OK)) {
            free(path_with_back);
            free_tab(path);
            return path_temp;
        }
        free(path_with_back);
        free(path_temp);
    }
    free_tab(path);
    return NULL;
}

static void get_valid_pass_where(char const *command, var_list *list)
{
    char **path = NULL;
    char *path_temp;
    char *path_with_back = NULL;

    path = my_str_to_word_array(IS_NULL_N(find_node("PATH", list)), ":");
    for (size_t i = 0; path[i]; i++) {
        path_with_back = my_strcat(IS_NULL(path)[i], "/");
        path_temp = my_strcat(path_with_back, command);
        if (!access(path_temp, F_OK)) {
            my_printf("%s\n", path_temp);
        }
        free(path_with_back);
        free(path_temp);
    }
    free_tab(path);
}

void my_which_command(char const **info, var_s *var)
{
    char *tmp;
    int status = 0;

    for (size_t i = 1; info[i]; i++) {
        if (is_built_in(info[i])) {
            my_printf("%s%s", info[i], SH_BUILT_CMD);
            status = 1;
        }
        tmp = get_valid_pass_which(info[i], ENV_VAR);
        if (tmp != NULL)
            my_printf("%s\n", tmp);
        if (!status && tmp == NULL) {
            my_printf("%z%z", info[i], CMD_NOT_FOUND);
            STATUS = 1;
        }
        free(tmp);
        status = 0;
    }
}

void my_where_command(char const **info, var_s *var)
{
    for (size_t i = 1; info[i]; i++) {
        if (is_built_in(info[i]))
            my_printf("%s%s", info[i], SH_IS_BUILT_CMD);
        get_valid_pass_where(info[i], ENV_VAR);
    }
}
