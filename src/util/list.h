//
// Created by mat on 6/12/2022.
//

#ifndef PONG_CLONE_LIST_H
#define PONG_CLONE_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
    void *data;
    struct node_t *next;
} NODE;

typedef struct {
    NODE *head;
    NODE *tail;
    int size;
} LIST;

/**
 * Creates and returns an empty list
 *
 * @return pointer to the list in memory
 */

LIST *list_create();

/**
 * Adds the data to the list
 *
 * @param list list that you want to add to
 * @param data data that you want to add
 */

void list_add(LIST *list, void *data);

/**
 * Frees the list from the memory
 *
 * @param list list that you want to free
 */

void list_free(LIST *list);

#endif //PONG_CLONE_LIST_H
