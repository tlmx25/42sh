/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** set_prompt_att
*/


#include "mysh.h"

char *set_grass_text(UNU var_s *var)
{
    char *text = my_strdup("\e[1m");
    return text;
}

char *set_underline_text(UNU var_s *var)
{
    char *text = my_strdup("\e[4m");
    return text;
}

char *set_italic_text(UNU var_s *var)
{
    char *text = my_strdup("\e[3m");
    return text;
}

char *set_blinks_text(UNU var_s *var)
{
    char *text = my_strdup("\e[6m");
    return text;
}

char *reset_att(UNU var_s *var)
{
    char *code = my_strdup("\e[0m");
    return code;
}
