/*
** EPITECH PROJECT, 2023
** projet
** File description:
** history
*/

#ifndef HISTORIC_H_
    #define HISTORIC_H_

    typedef struct node {
        int indice;
        char *date;
        char *command;
        struct node *next;
        struct node *prev;
    } node_t;

    typedef struct history {
        node_t *head;
        node_t *tail;
        int lengh;
    } history_t;

#endif /* !HISTORIC_H_ */
