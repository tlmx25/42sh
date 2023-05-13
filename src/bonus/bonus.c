/*
** EPITECH PROJECT, 2023
** projet
** File description:
** bonus
*/

#include "mysh.h"
#include "file_sh.h"
#include <time.h>
#include <stdlib.h>

void origin_seb(void)
{
    char **content_file = open_read_content_file(
            get_nb_line_file(".origin_seb"), ".origin_seb");

    if (content_file == NULL) {
        free_tab(content_file);
        return;
    }
    for (int i = 0;content_file[i] != NULL;i++) {
        my_printf("%s\n",content_file[i]);
    }
    free_tab(content_file);
}

void jungle(void)
{
    char **content_file = open_read_content_file(
            get_nb_line_file(".jungle"), ".jungle");

    if (content_file == NULL) {
        free_tab(content_file);
        return;
    }
    for (int i = 0;content_file[i] != NULL;i++) {
        my_printf("%s\n",content_file[i]);
    }
    free_tab(content_file);
}

void simple_seb(void)
{
    char **content_file = open_read_content_file(
            get_nb_line_file(".simple_seb"), ".simple_seb");

    if (content_file == NULL) {
        free_tab(content_file);
        return;
    }
    for (int i = 0;content_file[i] != NULL;i++) {
        my_printf("%s\n",content_file[i]);
    }
    free_tab(content_file);
}

void bonus_jungle(UNU char const **info, UNU var_s *var)
{
    int r;

    srand(time(NULL));
    r = rand() % 3;
    if (r == 0)
        simple_seb();
    if (r == 1)
        origin_seb();
    if (r == 2)
        jungle();
    return;
}
