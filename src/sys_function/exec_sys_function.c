/*
** EPITECH PROJECT, 2023
** B-PSU-200-REN-2-1-minishell1-tom.lefoix
** File description:
** exec_sys_function.c
*/

#include <errno.h>
#include "mysh.h"
#include "error_mysh.h"

static const signal_error_t error_signal[] = {
{SIGSEGV, SEGV},
{SIGFPE, FPE_ERR},
{SIGABRT, ABRT},
};

char *get_valid_pass(char *command, var_list *list)
{
    static char **path = NULL;
    char *path_temp;

    if (path == NULL)
        path = my_str_to_word_array(IS_NULL_N(find_node("PATH", list)), ":");
    if (!access(command, F_OK) && !access(command, X_OK))
        return command;
    if (my_get_first_char(command, " \t") == '.') {
        my_printf("%z%z", command, CMD_NOT_FOUND);
        return NULL;
    }
    for (size_t i = 0; IS_NULL(path)[i]; i++) {
        path_temp = my_strcat(my_strcat(IS_NULL(path)[i], "/"), command);
        if (!access(path_temp, F_OK)) {
            return path_temp;
        }
        free(path_temp);
    }
    my_printf("%z%z", my_clean_string(command, "\\", 1), CMD_NOT_FOUND);
    return NULL;
}

void verify_error_sig(int result_exec)
{
    for (int i = 0; i != ARRAY_LENGTH(error_signal); i++) {
        if (WTERMSIG(result_exec) == error_signal[i].signal_num)
            my_printf("%z", error_signal[i].message);
    }
    my_printf("%z", (WCOREDUMP(result_exec)) ? CRDMP : "\n");
}

void manager_fork(var_s *variable, int result_exec)
{
    if (WIFSIGNALED(result_exec))
        verify_error_sig(result_exec);
    variable->env_var->status = WEXITSTATUS(result_exec);
}

void manager_no_exec(char *command)
{
    if (errno != ENOEXEC) {
        my_printf("%z%z%z%z", command, ": ", strerror(errno), ".\n");
    } else {
        my_printf("%z", my_strcat(command, NO_EXC));
        exit(126);
    }
    exit(1);
}

void exec_sys_function(var_s *var, char **input)
{
    pid_t pid = fork();
    int result_exec;
    char *path_command;
    char **env = linkedlist_to_array(ENV_VAR);
    if (pid == 0) {
        signal(SIGINT, SIG_DFL);
        path_command = get_valid_pass(input[0], ENV_VAR);
        if (path_command == NULL || env == NULL)
            exit(1);
        result_exec = execve(path_command, input,env);
        if (result_exec != -1)
            exit(0);
        manager_no_exec(input[0]);
    } else {
        waitpid(pid, &result_exec, 0);
        free_tab(env);
        manager_fork(var, result_exec);
    }
}
