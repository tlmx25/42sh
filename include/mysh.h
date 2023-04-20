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
    #define SC (char const *)
    #define ABS(X) (X < 0) ? (X * (-1)) : X
    #define IS_NULL_N(X) (X == NULL) ? "/bin:/usr/bin:/usr" : X->var
    #define IS_NULL(X) (X == NULL) ? NULL : X
    #define FLAG_APPEND O_CREAT | O_WRONLY | O_APPEND
    #define FLAG_ERASE O_CREAT | O_WRONLY | O_TRUNC
    #define FLAG_PERM S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH
    #define STATUS var->env_var->status
    #define LOCAL_VAR var->local_var
    #define ENV_VAR var->env_var
    #define ALIAS var->alias
    #define DICO var->dico
    #define HAVE_NAME_ARG(X) (X[1] == '>') ? &X[1] : X
    #include <unistd.h>
    #include <string.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include "my.h"
    #include "myprintf.h"

enum MODE {
    CLASSIC,
    EDITING,
};
typedef struct var_node {
    char *name;
    char *var;
    struct var_node *next;
    struct var_node *prev;
}var_node;

typedef struct var_list {
    var_node *head;
    var_node *tail;
    size_t size;
    int status;
}var_list;

typedef struct var {
    char **arg;
    var_list *env_var;
    var_list *local_var;
    var_list *alias;
    var_list *dico;
    int fd_redirection_out;
    int fd_redirection_in;
    int dup_stdout;
    int dup_stdin;
    int *pid_list;
    int mode;
}var_s;

typedef struct commands {
    char *command;
    void (*fct)(char const **, var_s *);
}command_l;



int mysh(int ac, char **av, char **env);
void add_var(char const **info, var_list *list);
var_list *array_to_linkedlist(const char **env);
void free_node(var_node **node);
void delete_env_var(const char *name, var_list *list);
void print_env_list(UNU char const **arg, var_s *var);
void exit_function(char const **arg, var_s *var);
char **linkedlist_to_array(var_list *list);
var_node *find_node(char const *name, var_list *list);
void set_env(char const **arg, var_s *var);
void exec_sys_function(var_s *variable, char **input);
void verify_env(var_s *var);
void free_list(var_list *list);
void unset_env(char const **arg, var_s *var);
int my_str_isalphanum_env(char const *str);
int my_str_isalpha_env(char const *str, char const *command);
void cd_built_in(char const **arg, var_s *var);
void separate_command_comma(var_s *variable, char *input);
void get_command(var_s *var, char **input);
void verify_if_redirection(var_s *variable, char *input);
void parsing_pipe(var_s *variable, char **input);
int *add_pid(int *actual_list, int pid);
void erase_name(char **array);
char *get_name(char const *str);
int is_built_in(const char *command);
char *get_left_redirection(var_s *variable, char *input);
var_s *init_sh(char const **env);
void open_write_list(var_list *list, char const *filepath, int fd_stdout);
var_list *init_list_variable(char const *filepath);
void free_var(var_s *var);
void print_list_variable(var_list *list, char separator);
void set_local_var(const char **info, var_s *var);
void unset_local_var(char const **info, var_s *var);
void unset_alias(char const **info, var_s *var);
void add_alias(char const **info, var_s *var);
char *check_alias(char *command, var_s *var);
int check_variable(char **all_command, var_s *var);
int my_getline(char **input, var_s *var);
void manage_input(char **input, var_s *var);
var_list *init_dico(char const *filepath);
void handle_autocompletion(int c, char **input, var_s *var, int *cursor);
void clean_list(var_list *list);
void delete_with_globbing(char const *name, var_list *list);
#endif
