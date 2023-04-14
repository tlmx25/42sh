/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** get_local_variable.c
*/

#include "file_sh.h"
#include "mysh.h"


var_list *init_list_variable(char const *filepath)
{
    char **content_file = open_read_content_file(
    get_nb_line_file(filepath), filepath);
    var_list *list;

    list = array_to_linkedlist((char const **)content_file);
    return list;
}
