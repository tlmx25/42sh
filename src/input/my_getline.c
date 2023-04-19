/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** my_getline
*/

#include <termios.h>
#include "mysh.h"
char *my_str_cat_char(char *str, char c, int cursor);
char *my_str_del_char(char *str, int cursor);

static struct termios set_term(void)
{
    struct termios old_termios;
    struct termios new_termios;

    tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO | ECHONL);
    new_termios.c_iflag &= ~(IXON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
    return old_termios;
}

static void handle_arrow_keys(UNU char** input, int* len, int* cursor)
{
    char key;
    if (getchar() != '[')
        return;
    key = (char)getchar();
    if (key == 'D' && *cursor > 0) {
        my_printf("\033[D");
        (*cursor)--;
    }
    if (key == 'C' && *cursor < *len) {
        my_printf("\033[C");
        (*cursor)++;
    }
}

void set_char(int *len, int *cursor, char **input, int c)
{
    for (size_t i = 0; (int)i != (*len - *cursor); i++)
        my_printf("\033[C");
    for (size_t i = 0; (int)i < *len && *len != 0; i++)
        my_printf("\b \b");
    my_printf("%s", *input);
    *len = my_strlen(*input);
    if (c != 127)
        (*cursor)++;
    else if (*cursor > 0)
        (*cursor)--;
    for (size_t i = 0; (int)i != *len - *cursor; i++)
        my_printf("\033[D");
}

static int get_intput(char **input)
{
    int len = my_strlen(*input);
    int c = 0;
    int cursor = len;

    while (1) {
        c = getchar();
        if (c == 4 || c == 13 || c == EOF)
            return -1;
        if (c == 27) {
            handle_arrow_keys(input, &len, &cursor);
            continue;
        }
        if ((c < 32 || c > 127) && c != '\n')
            continue;
        *input = my_str_cat_char(*input, (char)c, cursor);
        set_char(&len, &cursor,  input, c);
        if (c == '\n')
            break;
    }
    return len;
}

int my_getline(char **input)
{
    struct termios old_termios = set_term();
    int value;

    if (*input == NULL)
        *input = my_strdup("");
    if (*input == NULL) {
        return -1;
    }
    value = get_intput(input);
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
    return value;
}
