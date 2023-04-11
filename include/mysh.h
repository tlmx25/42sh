/*
** EPITECH PROJECT, 2023
** B-PSU-200-REN-2-1-minishell1-tom.lefoix
** File description:
** mysh.h
*/

#ifndef MYSH_H
    #define MYSH_H
    #define UNU __attribute__((unused))
    #define AC (char const **)
    #define ABS(X) (X < 0) ? (X * (-1)) : X
    #define IS_NULL_N(X) (X == NULL) ? "/bin:/usr/bin:/usr" : X->var
    #define IS_NULL(X) (X == NULL) ? NULL : X
    #define FLAG_APPEND O_CREAT | O_WRONLY | O_APPEND
    #define FLAG_ERASE O_CREAT | O_WRONLY | O_TRUNC
    #define HAVE_NAME_ARG(X) (X[1] == '>') ? &X[1] : X
    #include <unistd.h>
    #include <string.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include "my.h"
    #include "myprintf.h"

typedef struct env_v {
    char *name;
    char *var;
    struct env_v *next;
    struct env_v *prev;
}env_v;

typedef struct env_list {
    env_v *head;
    env_v *tail;
    size_t size;
    int status;
}env_list;

typedef struct var {
    char **arg;
    env_list *list;
    int fd_redirection_out;
    int fd_redirection_in;
    int dup_stdout;
    int dup_stdin;
    int *pid_list;
}var_s;

typedef struct commands {
    char *command;
    void (*fct)(char const **, env_list *);
}command_l;



int mysh(int ac, char **av, char **env);
void add_env_var(char const **info, env_list *list);
env_list *array_to_linkedlist(char **env);
void free_node(env_v **node);
void delete_env_var(char const **name, env_list *list);
void print_env_list(UNU char const **arg,env_list *list);
void exit_function(char const **arg, env_list *list);
char **linkedlist_to_array(env_list *list);
env_v *find_node(char const *name, env_list *list);
void set_env(char const **arg, env_list *list);
void exec_sys_function(var_s *variable, char **input);
void verify_env(env_list *list);
void free_env(env_list **list);
void unset_env(char const **arg, env_list *list);
int my_str_isalphanum_env(char const *str);
int my_str_isalpha_env(char const *str);
void cd_built_in(char const **arg, env_list *list);
void separate_command_comma(var_s *variable, char *input);
void get_command(var_s *variable, char **input);
void verify_if_redirection(var_s *variable, char *input);
void parsing_pipe(var_s *variable, char **input);
int *add_pid(int *actual_list, int pid);
void erase_name(char **array);
char *get_name(char const *str);
int is_built_in(char *command);
char *get_left_redirection(var_s *variable, char *input);
#endif
