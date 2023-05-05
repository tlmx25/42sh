/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** autocompletion
*/

#include <dirent.h>
#include "mysh.h"

static int get_world(char **input, var_s *var)
{
    var_node *node = ALIAS->head;
    int len = my_strlen(*input);

    if (len == 0)
        return 0;
    for (; node != NULL; node = node->next) {
        if (my_strncmp(node->name, *input, len) == 0) {
            free(*input);
            *input = my_strdup(node->name);
            return 1;
        }
    }
    return 0;
}

void open_dir(char **command)
{
    DIR *dir = opendir("/bin");
    struct dirent *in_dir;
    int len = my_strlen(*command);

    if (dir == NULL)
        return;
    in_dir = readdir(dir);
    for (; in_dir != NULL; in_dir = readdir(dir)) {
        if (my_strncmp(*command, in_dir->d_name, len) == 0) {
            free(*command);
            *command = my_strdup(in_dir->d_name);
        }
    }
    closedir(dir);
}

void handle_autocompletion(int c, char **input, var_s *var, const int *cursor)
{
    char **command = my_str_to_word_array(*input, " \t");
    int size_array = my_arrsize(AC command);

    if (c != '\t') {
        free_tab(command);
        *input = my_str_cat_char(*input, (char)c, *cursor);
        return;
    }
    if (var == NULL)
        return;
    if (get_world(input, var))
        return;
    if (size_array != 1 && command != NULL)
        return;
    open_dir(input);
    free_tab(command);
}
