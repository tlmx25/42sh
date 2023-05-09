/*
** EPITECH PROJECT, 2023
** B-PSU-200-REN-2-1-minishell1-tom.lefoix
** File description:
** error_mysh.h
*/
#ifndef ERROR_MYSH_H_
    #define ERROR_MYSH_H_
    #define NO_EXC ": Exec format error. Wrong Architecture.\n"
    #define NO_SUCH_FILE ": No such file or directory.\n"
    #define CRDMP " (core dumped)\n"
    #define SEGV "Segmentation fault"
    #define CMD_NOT_FOUND ": Command not found.\n"
    #define FPE_ERR "Floating exception"
    #define CD_MANY_ARG "cd: Too many arguments.\n"
    #define CD_NO_HOME_DIR "cd: No home directory.\n"
    #define CD_NO_HOME_SET "No $home variable set.\n"
    #define SE_MANY_ARG "setenv: Too many arguments.\n"
    #define ABRT "Aborted"
    #define AMB_RDRECT "Ambiguous output redirect.\n"
    #define MISS_NAME_RDRECT "Missing name for redirect.\n"
    #define INV_NULL_CMD "Invalid null command.\n"
    #define VAR_CTN_AN "Variable name must contain alphanumeric characters.\n"
    #define VAR_STR_LET "Variable name must begin with a letter.\n"
    #define UDF_VAR ": Undefined variable.\n"
    #define CMD_NOT_FOUND ": Command not found.\n"
    #define SH_BUILT_CMD ": shell built-in command.\n"
    #define SH_IS_BUILT_CMD " is a shell built-in\n"
    #define ILL_N_VAR "Illegal variable name.\n"
    #define IS_RDRECT(X) (X == '<' || X == '>') ? 1 : 0

typedef struct signal_error {
    int signal_num;
    char *message;
} signal_error_t;
#endif /*ERROR_MYSH_H_*/
