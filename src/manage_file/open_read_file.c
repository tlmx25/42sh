/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** open_read_file.c
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int get_nb_line_file(char const *filepath)
{
    FILE *fd = fopen(filepath, "r");
    char *line = NULL;
    size_t len = 0;
    int count = 0;

    if (fd == NULL) {
        return -1;
    }
    while (getline(&line, &len, fd) != -1) {
        free(line);
        line = NULL;
        count += 1;
    }
    fclose(fd);

    return count;
}

static char **free_content_file_if_error(char **content_file,
size_t nb_line_actual)
{
    for (size_t i = 0; i < nb_line_actual; i++)
        free(content_file[i]);

    return NULL;
}

char **open_read_content_file(int nb_line, char const *filepath)
{
    char **content_file = malloc(sizeof(char *) * (nb_line + 1));
    size_t len = 0;
    int check_return = 0;
    size_t i = 0;
    FILE *file = fopen(filepath, "r");

    if (file == NULL)
        return NULL;
    for (; i < (size_t)nb_line && check_return != -1; i++) {
        content_file[i] = NULL;
        check_return = getline(&content_file[i], &len, file);
        if (check_return == -1)
            continue;
        content_file[i][check_return - 1] = '\0';
    }
    if (i != (size_t)nb_line)
        return free_content_file_if_error(content_file, i);
    content_file[nb_line] = NULL;
    fclose(file);
    return (content_file);
}
