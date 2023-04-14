/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** left_redirection.c
*/

#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "mysh.h"
#include "error_mysh.h"

static void double_left_redirect(char **cut_left_redirect, int fd[2])
{
    size_t len = 0;
    int len_line;
    char *line = NULL;
    char *name = get_name(cut_left_redirect[1]);

    if (name == NULL || cut_left_redirect == NULL)
        return;
    name = my_strcat(name, "\n");
    write(1, "? ", 2);
    while ((len_line = (int)getline(&line, &len, stdin)) != -1) {
        if (my_strcmp(name, line) == 0) {
            free(line);
            break;
        }
        write(fd[1], line, len_line);
        free(line);
        line = NULL;
        write(1, "? ", 2);
    }
    free(name);
}

static int simple_left_redirection(char **cut_left_redirect, var_s *variable)
{
    char *name = get_name(cut_left_redirect[1]);
    char *tmp;
    char *tmp2;
    if (access(name, R_OK) == -1) {
        my_printf("%z%z", name, NO_SUCH_FILE);
        variable->env_var->status = 1;
        return 84;
    }
    tmp = my_strcat("cat ", name);
    tmp2 = my_strcat(tmp, " |");
    free(tmp);
    tmp = cut_left_redirect[0];
    cut_left_redirect[0] = my_strcat(tmp2, cut_left_redirect[0]);
    free(tmp);
    free(tmp2);
    free(name);
    return 0;
}

char *get_left_redirection(var_s *variable, char *input)
{
    char **cut_left_redirect = my_str_to_word_array(input, "<");
    int fd_pipe[2];
    char *str;

    if (cut_left_redirect == NULL)
        return NULL;
    if (pipe(fd_pipe) == -1)
        return NULL;
    if (my_str_in_str(input, "<<")) {
        double_left_redirect(cut_left_redirect, fd_pipe);
        variable->fd_redirection_in = dup(fd_pipe[0]);
    } else
        simple_left_redirection(cut_left_redirect, variable);
    erase_name(cut_left_redirect);
    str = my_array_to_str(AC cut_left_redirect);
    free_tab(cut_left_redirect);
    close(fd_pipe[1]);
    close(fd_pipe[0]);
    return str;
}
