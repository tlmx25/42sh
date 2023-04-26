/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** set_prompt
*/

#include "mysh.h"
char *get_host_name(var_s *var);
char *get_user_name(var_s *var);
char *set_grass_text(var_s *var);
char *reset_att(var_s *var);
char *set_italic_text(var_s *var);
char *set_underline_text(var_s *var);
char *set_blinks_text(var_s *var);
char *get_directory_name(var_s *var);
char *get_directory_name_without_home(UNU var_s *var);

static const prompt_t list_flags[] = {
        {'m', get_host_name},
        {'n', get_user_name},
        {'B', set_grass_text},
        {'b', reset_att},
        {'I', set_italic_text},
        {'i', reset_att},
        {'U', set_underline_text},
        {'u', reset_att},
        {'S', set_blinks_text},
        {'s', reset_att},
        {'/', get_directory_name},
        {'~', get_directory_name_without_home},
};

int is_flag_prompt(char c)
{
    for (size_t i = 0; i < ARRAY_LENGTH(list_flags); i++) {
        if (list_flags[i].flag == c)
            return (int)(i + 1);
    }
    return 0;
}

static char *parse_prompt(var_s *var, var_node *node)
{
    int flag = 0;
    char *tmp = NULL;
    char *str_flag = NULL;

    for (size_t i = 0; node->var[i]; i++) {
        flag = is_flag_prompt(node->var[i + 1]);
        if (node->var[i] == '%' && flag != 0) {
            str_flag = (char *) list_flags[flag - 1].fct(var);
            tmp = my_strcat_free(tmp, str_flag, 1, 1);
            i++;
            continue;
        }
        tmp = my_str_cat_char(tmp, node->var[i], 7890987);
    }
    return tmp;
}

void set_prompt(var_s *var)
{
    var_node *node = find_node("prompt", LOCAL_VAR);

    if (node == NULL || !my_strcmp(node->var, "$> ") || node->var == NULL) {
        var->prompt = CHOICE_PROMPT;
        return;
    }
    free(var->prompt);
    var->prompt = parse_prompt(var, node);
}
