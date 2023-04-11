/*
** EPITECH PROJECT, 2023
** B-PSU-200-REN-2-1-minishell1-tom.lefoix
** File description:
** test_env.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/myprintf.h"
#include "../include/mysh.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

char const *env[] = {"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin",
"OS=LINUX",
"TEMP=TEMPS",
"LANG=fr_FR.UTF-8",
"PWD=/home/tom",
"HOME=/home/tom",
"SHELL=/bin/bash",
"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin",
"OS=LINUX",
"SHLVL=1",
"TEMP=TEMPS",
"LANG=fr_FR.UTF-8",
"PWD=/home/tom",
"HOME=/home/tom",
"SHELL=/bin/bash",
"LOGNAME=tom",
"USER=tom"
};

Test(array_to_linkedlist, array_to_linkedlist_size, .init = redirect_all_std)
{
    env_list *list = malloc(sizeof(env_list));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list = array_to_linkedlist((char **)env);
    cr_assert_eq(list->size, 17);
    free_env(&list);

}

Test(array_to_linkedlist, array_to_linkedlist_content, .init = redirect_all_std)
{
    env_list *list = malloc(sizeof(env_list));
    int i = 0;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list = array_to_linkedlist((char **)env);
    for (env_v *node = list->head; node != NULL; node = node->next, i++) {
        cr_assert_str_eq(my_strcat(my_strcat(node->name, "="), node->var), env[i]);
    }
    free_env(&list);
}

Test(delete_env_var, delete_env_var, .init = redirect_all_std)
{
    env_list *list = malloc(sizeof(env_list));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list = array_to_linkedlist((char **)env);
    delete_env_var(AC my_str_to_word_array("test=SHLVL", "="), list);
    cr_assert_eq(list->size, 16);
    free_env(&list);
}

Test(delete_env_var, delete_env_head, .init = redirect_all_std)
{
    env_list *list = malloc(sizeof(env_list));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list = array_to_linkedlist((char **)env);
    delete_env_var(AC my_str_to_word_array("test=PATH", "="), list);
    cr_assert_eq(list->size, 16);
    cr_assert_str_eq(list->head->name, "OS");
    free_env(&list);
}

Test(delete_env_var, delete_env_tail, .init = redirect_all_std)
{
    env_list *list = malloc(sizeof(env_list));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list = array_to_linkedlist((char **)env);
    delete_env_var(AC my_str_to_word_array("test=USER", "="), list);
    cr_assert_eq(list->size, 16);
    cr_assert_str_eq(list->tail->name, "LOGNAME");
    free_env(&list);
}

Test(set_env, set_env, .init = redirect_all_std)
{
    env_list *list = malloc(sizeof(env_list));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list = array_to_linkedlist((char **)env);
    set_env(AC my_str_to_word_array("setenv=temp=2", "="), list);
    cr_assert_eq(list->size, 18);
    free_env(&list);
}

Test(set_env, set_env_error, .init = redirect_all_std)
{
    env_list *list = malloc(sizeof(env_list));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list = array_to_linkedlist((char **)env);
    set_env(AC my_str_to_word_array("setenv=2temp test", "="), list);
    cr_assert_eq(list->size, 17);
    cr_assert_stdout_eq_str("setenv: Variable name must begin with a letter.\n");
    free_env(&list);
}

Test(find_node, find_node, .init = redirect_all_std)
{
    env_list *list = malloc(sizeof(env_list));
    env_v *node;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list = array_to_linkedlist((char **)env);
    node = find_node("SHLVL", list);
    cr_assert_str_eq(node->name, "SHLVL");
    cr_assert_str_eq(node->var, "1");
    free_env(&list);
}

Test(find_node, find_node_null, .init = redirect_all_std)
{
    env_list *list = malloc(sizeof(env_list));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    cr_assert_null(find_node("SHLVL", list));
    free_env(&list);
}

Test(exit, exit_syntax_error, .init = redirect_all_std)
{
    env_list *list = malloc(sizeof(env_list));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    cr_assert_null(find_node("SHLVL", list));
    exit_function(AC my_str_to_word_array("exit 1 2", " "), list);
    cr_assert_stderr_eq_str("exit: Expression Syntax.\n");
}

Test(linkedlist_to_array, linkedlist_to_array, .init = redirect_all_std)
{
    env_list *list = malloc(sizeof(env_list));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list = array_to_linkedlist((char **)env);
    char **array = linkedlist_to_array(list);
    cr_assert_eq(my_arrsize(AC array), 17);
    for (int i = 0; i < 17; i++) {
        cr_assert_str_eq(array[i], env[i]);
    }
    free_tab(array);
    free_env(&list);
}

Test(verify_env, verify_env_empty_env, .init = redirect_all_std)
{
    env_list *list = malloc(sizeof(env_list));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    verify_env(list);
    cr_assert_eq(list->size, 3);
    cr_assert_str_eq(list->head->name, "PWD");
    cr_assert_str_eq(list->head->next->name, "SHLVL");
    cr_assert_str_eq(list->head->next->next->name, "PATH");
}

Test(verify_env, verify_env_modif_shlvl, .init = redirect_all_std)
{
    env_list *list = malloc(sizeof(env_list));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list = array_to_linkedlist((char **)env);
    verify_env(list);
    cr_assert_str_eq(find_node("SHLVL", list)->var, "2");
    free_env(&list);
}

Test(verify_env, verify_env_modif_shlvl2, .init = redirect_all_std)
{
    env_list *list = malloc(sizeof(env_list));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list = array_to_linkedlist((char **)env);
    find_node("SHLVL", list)->var = my_strdup("9");
    verify_env(list);
    cr_assert_str_eq(find_node("SHLVL", list)->var, "10");
    free_env(&list);
}

Test(verify_env, verify_env_modif_shlvl3, .init = redirect_all_std)
{
    env_list *list = malloc(sizeof(env_list));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list = array_to_linkedlist((char **)env);
    find_node("SHLVL", list)->var = my_strdup("11");
    verify_env(list);
    cr_assert_str_eq(find_node("SHLVL", list)->var, "12");
    free_env(&list);
}