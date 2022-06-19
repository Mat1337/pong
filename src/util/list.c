//
// Created by mat on 6/12/2022.
//

#include "list.h"

/**
 * Creates and returns an empty list
 *
 * @return pointer to the list in memory
 */

LIST *list_create() {
    // allocate memory for the list
    LIST *list = (LIST *) malloc(sizeof(LIST));

    // set the initial size of the list to 0
    list->size = 0;

    // make sure that the head node is null
    list->head = NULL;

    // return the list
    return list;
}

/**
 * Adds the data to the list
 *
 * @param list list that you want to add to
 * @param data data that you want to add
 */

void list_add(LIST *list, void *data) {
    // allocate memory for the new node
    NODE *node = (NODE *) malloc(sizeof(NODE));

    // make sure that the node does not point to anything
    node->next = NULL;

    // make that data pointer point to data
    node->data = data;

    // if there is no head in the list
    if (list->head == NULL) {
        // set the current node as the head of the list
        list->head = node;
    } else {
        // get the head of the list
        NODE *iterator = list->head;

        // find the last element in the list
        while (iterator->next != NULL) {

            // update the current iterator to the next node
            iterator = iterator->next;
        }

        // update the next pointer of the last element to the new node
        iterator->next = node;
    }

    // set the pointer to the tail to the current node
    list->tail = node;

    // increment the size of the list
    list->size++;
}

/**
 * Gets an item from the list
 *
 * @param list list that you want to get the item from
 * @param index index of the item
 * @return pointer to the item
 */

void *list_get(LIST *list, int index) {
    return (list->head + index)->data;
}

/**
 * Gets the index of the node
 *
 * @param list list that you want to get the index from
 * @param node node that you want to get the index from
 * @return index of the node
 */

int list_index(LIST *list, NODE *node) {
    return (int) (&node - &list->head);
}

/**
 * Gets the size of the list
 *
 * @param list list that you want to get the size of
 * @return size of the list
 */

int list_size(LIST *list) {
    return (int) (&list->tail - &list->head) + 1;
}

/**
 * Frees the list from the memory
 *
 * @param list list that you want to free
 */

void list_free(LIST *list) {
    // get the head of the list
    NODE *iterator = list->head;

    // if the iterator is invalid
    if (iterator == NULL) {
        // return out of the method there is nothing to free
        return;
    }

    // loop through the list
    while (iterator != NULL) {
        // cache the next item
        NODE *temp = iterator->next;

        // free the data in the iterator
        free(iterator->data);

        // free the iterator
        free(iterator);

        // reset the iterator pointer
        iterator = temp;
    }

    // free the list pointer
    free(list);
}