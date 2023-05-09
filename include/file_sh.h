/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** file_sh.h
*/

#ifndef FILE_SH_H_
    #define FILE_SH_H_
    #define LOCAL_VAR_FILE ".local_var"
    #define ALIAS_FILE ".alias"
    #define DICO_FILE ".dico"
    #define HIS_FILE ".history"
int get_nb_line_file(char const *filepath);
char **open_read_content_file(int nb_line, char const *filepath);
#endif /*FILE_SH_H_*/
