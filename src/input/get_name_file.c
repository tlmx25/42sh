/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** get_name_file
*/

#include <dirent.h>
#include "mysh.h"

static char *open_dir_path(char *name, char const *path)
{
    DIR *dir = opendir(path);
    struct dirent *in_dir;
    int len = my_strlen(name);

    if (dir == NULL)
        return name;
    in_dir = readdir(dir);
    for (; in_dir != NULL; in_dir = readdir(dir)) {
        if (my_strncmp(name, in_dir->d_name, len) == 0) {
            free(name);
            name = my_strdup(in_dir->d_name);
            break;
        }
    }
    closedir(dir);
    return (in_dir->d_type != DT_REG) ? name : my_strcat_free(name, "/", 1, 0);
}

static void get_path(char **input, char **command, var_s *var, int size)
{
    char **path = my_str_to_word_array(command[size - 1], "/");
    int size_path = my_arrsize(AC path);

    if (path == NULL)
        return;
}
