/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** prompt_function
*/

#include "mysh.h"

char *get_host_name(UNU var_s *var)
{
    char *name = malloc(sizeof(char) * 1024);

    if (name == NULL)
        return NULL;
    if (gethostname(name, 1024) == -1) {
        free(name);
        return NULL;
    }
    return name;
}

char *get_user_name(UNU var_s *var)
{
    char *name = malloc(sizeof(char) * 1024);

    if (name == NULL)
        return NULL;
    if (getlogin_r(name, 1024) == -1) {
        free(name);
        return NULL;
    }
    return name;
}

char *get_directory_name(UNU var_s *var)
{
    char *name = getcwd(NULL, 0);

    if (name == NULL) {
        free(name);
        return NULL;
    }
    return name;
}

char *get_directory_name_without_home(UNU var_s *var)
{
    char *name = getcwd(NULL, 0);
    char *tmp = NULL;
    var_node *node = find_node("HOME", ENV_VAR);

    if (name == NULL || node == NULL) {
        free(name);
        return NULL;
    }
    if (!my_strncmp(name, node->var, my_strlen(node->var))) {
        tmp = name;
        name = my_strdup(&name[my_strlen(node->var)]);
        free(tmp);
    }
    return name;
}
