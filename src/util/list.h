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
 * Gets an item from the list
 *
 * @param list list that you want to get the item from
 * @param index index of the item
 * @return pointer to the item
 */

void *list_get(LIST *list, int index);

/**
 * Gets the index of the node
 *
 * @param list list that you want to get the index from
 * @param node node that you want to get the index from
 * @return index of the node
 */

int list_index(LIST *list, NODE *node);

/**
 * Gets the size of the list
 *
 * @param list list that you want to get the size of
 * @return size of the list
 */

int list_size(LIST *list);

/**
 * Frees the list from the memory
 *
 * @param list list that you want to free
 */

void list_free(LIST *list);

#endif //PONG_CLONE_LIST_H
