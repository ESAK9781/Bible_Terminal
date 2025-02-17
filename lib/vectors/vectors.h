#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef struct _Link_Struct {
    struct _Link_Struct * next;
    struct _Link_Struct * prev;
    void * value;
} ListLink;

typedef struct _List_Struct {
    ListLink * head;
    ListLink * tail;
    int size;
} ListTemplate;

/**
 * @brief create a list link whose value is stored at the pointer
 * @param value pointer to the value of the link
 * @return pointer to the new link
 */
ListLink * _createLink(void * value);

/**
 * @brief create a list wrapper
 * @return pointer to the new list wrapper
 */
ListTemplate * _createList();

/**
 * @brief corrects the pointers of two links so the first one comes after the second
 * @param a pointer to the first link
 * @param b pointer to the second link
 */
void _chainTogether(ListLink * a, ListLink * b);

/**
 * @brief free the memory associated with a link
 * @param link pointer to the link to free
 */
void _deleteLink(ListLink * link);

/**
 * @brief free the memory associated with a list and all its links
 * @param list pointer to the list
 */
void _deleteList(ListTemplate * list);

/**
 * @brief get the length of a list
 * @param list pointer to the list
 * @return number of elements in the list
 */
int _getLen(ListTemplate * list);

/**
 * @brief retrieve a link at a certain index
 * @param list pointer to the list
 * @param index the index to retrieve
 * @return pointer to that link
 */
ListLink * _getLink(ListTemplate * list, int index);

/**
 * @brief retrieve the value at a certain index
 * @param list pointer to the list
 * @param index index to retrieve
 * @return pointer to the value of that link
 */
void * _getVal(ListTemplate * list, int index);

/**
 * @brief retrieve and remove the link at the beginning of the list
 * @param list pointer to the list
 * @return pointer to the value
 */
void * _pop(ListTemplate * list);

/**
 * @brief insert an element into the list at a specified index
 * @param list pointer to the list
 * @param value value to insert
 * @param index index to insert at
 */
void _insert(ListTemplate * list, void * value, int index);

/**
 * @brief add an element to the end of the list
 * @param list pointer to the list
 * @param value value to append
 */
void _append(ListTemplate * list, void * value);

/**
 * @brief add an element to the front of the list
 * @param list pointer to the list
 * @param value pointer to the value
 */
void _push(ListTemplate * list, void * value);

/**
 * @brief retrieve and remove an element from the specified index
 * @param list pointer to the list
 * @param index index to retrieve at
 * @return pointer to the value
 */
void * _popAt(ListTemplate * list, int index);

/**
 * @brief delete the node at a specified index
 * @param list pointer to the list
 * @param index index to delete at
 */
void _deleteAt(ListTemplate * list, int index);