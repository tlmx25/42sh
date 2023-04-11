/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** get_redirection.c
*/

#include <fcntl.h>
#include "mysh.h"

static char *create_redirection(var_s *variable, char *input)
{
    int fd;
    char **input_redirect = my_str_to_word_array(input, ">");
    char **clean_input = my_str_to_word_array(input_redirect[1], " \t");
    char *new_input;

    if (input_redirect == NULL)
        return NULL;
    if (my_str_in_str(input, ">>"))
        fd = open(clean_input[0], FLAG_APPEND, 0666);
    else
        fd = open(clean_input[0], FLAG_ERASE, 0666);
    if (fd == -1) {
        free_tab(input_redirect);
        return NULL;
    }
    variable->fd_redirection_out = fd;
    new_input = my_strdup(input_redirect[0]);
    free_tab(input_redirect);
    free_tab(clean_input);
    return new_input;
}

static void managing_pipe(var_s *variable, char **pipe_input, int size)
{
    int error;

    variable->pid_list = my_calloc(sizeof(int) * (size + 1));
    if (variable->pid_list == NULL) {
        free_tab(pipe_input);
        return;
    }
    variable->pid_list[size] = -2;
    parsing_pipe(variable, pipe_input);
    for (int i = 0; variable->pid_list[i] != -2; i++) {
        waitpid(variable->pid_list[i], &error, 0);
        if (WEXITSTATUS(error) != 0)
            variable->list->status = WEXITSTATUS(error);
    }
    free(variable->pid_list);
}

static void choice_execution_function(char *input, var_s *variable)
{
    char **pipe_input = my_str_to_word_array(input, "|");
    int size = my_arrsize(AC pipe_input);

    if (pipe_input == NULL)
        return;
    if (pipe_input[0] != NULL) {
        managing_pipe(variable, pipe_input, size);
    } else
        get_command(variable, my_str_to_word_array(input, " \t"));
    free_tab(pipe_input);
}

static void manage_end_of_command(var_s *variable)
{
    if (variable->fd_redirection_out != STDOUT_FILENO) {
        close(variable->fd_redirection_out);
        variable->fd_redirection_out = STDOUT_FILENO;
    }
    if (variable->fd_redirection_in != STDIN_FILENO) {
        close(variable->fd_redirection_in);
        variable->fd_redirection_in = STDIN_FILENO;
    }
    dup2(variable->dup_stdin, STDIN_FILENO);
    dup2(variable->dup_stdout, STDOUT_FILENO);
}

void verify_if_redirection(var_s *variable, char *input)
{
    if (input != NULL && my_str_in_str(input, "<"))
        input = get_left_redirection(variable, input);
    if (input != NULL && my_str_in_str(input, ">"))
        input = create_redirection(variable, input);
    if (input == NULL)
        return;
    if (variable->fd_redirection_out != STDOUT_FILENO)
        dup2(variable->fd_redirection_out, STDOUT_FILENO);
    if (variable->fd_redirection_out != STDIN_FILENO)
        dup2(variable->fd_redirection_in, STDIN_FILENO);
    choice_execution_function(my_clean_string(input, "'\"", 1), variable);
    manage_end_of_command(variable);
}
