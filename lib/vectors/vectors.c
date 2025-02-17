#include "./vectors.h"

ListLink * _createLink(void * value) {
    ListLink * out = malloc(sizeof(ListLink));
    out->next = NULL;
    out->prev = NULL;
    out->value = value;
    return out;
}

ListTemplate * _createList() {
    ListTemplate * out = malloc(sizeof(ListTemplate));
    out->head = NULL;
    out->tail = NULL;
    out->size = 0;
    return out;
}

void _chainTogether(ListLink * a, ListLink * b) {
    a->next = b;
    b->prev = a;
}

void _deleteLink(ListLink * link) {
    free(link->value);
    free(link);
}

void _deleteList(ListTemplate * list) {
    ListLink * current = list->head;
    for (int i = 0; i < list->size; i++) {
        ListLink * temp = current->next;
        _deleteLink(current);
        current = temp;
    }

    free(list);
}

int _getLen(ListTemplate * list) {
    return list->size;
}

ListLink * _getLink(ListTemplate * list, int index) {
    if ((index >= list->size) || index < 0) {
        printf("ERROR: Could not get link at %d, index out of range\n", index);
        return NULL;
    }

    if (index > (list->size / 2)) {
        ListLink * place = list->tail;
        for (int i = 0; i < list->size - index - 1; i++) {
            place = place->prev;
        }
        return place;
    }

    ListLink * place = list->head;
    for (int i = 0; i < index; i++) {
        place = place->next;
    }
    return place;
}

void * _getVal(ListTemplate * list, int index) {
    return _getLink(list, index)->value;
}

void * _pop(ListTemplate * list) {
    if (list->size == 0) {
        return NULL;
    }

    ListLink * link = list->head;
    list->head = link->next;
    list->size--;
    list->head->prev = NULL;
    
    void * value = link->value;
    free(link);

    return value;
}

void _insert(ListTemplate * list, void * value, int index) {
    if ((index > list->size) || (index < 0)) {
        printf("ERROR: Cannot insert at %d, index out of range\n", index);
        return;
    }

    ListLink * newLink = _createLink(value);
    

    if (list->size == 0) {
        list->head = newLink;
        list->tail = newLink;
        list->size++;
        return;
    }

    if (index == 0) {
        _chainTogether(newLink, list->head);
        list->head = newLink->next;
        list->size++;
        return;
    }

    if (index == list->size) {
        _chainTogether(list->tail, newLink);
        list->tail = newLink;
        list->size++;
        return;
    }

    ListLink * before = _getLink(list, index);
    ListLink * after = before->next;
    _chainTogether(before, newLink);
    _chainTogether(newLink, after);
    list->size++;
    return;
}

void _append(ListTemplate * list, void * value) {
    _insert(list, value, list->size);
}

void _push(ListTemplate * list, void * value) {
    _insert(list, value, 0);
}

void * _popAt(ListTemplate * list, int index) {
    if ((index < 0) || (index >= list->size)) {
        printf("ERROR: Could not pop index %d, index out of range\n", index);
    }

    if (index == 0) {
        return _pop(list);
    }

    if (index == list->size - 1) {
        ListLink * link = list->tail;
        void * value = link->value;
        list->tail = link->prev;
        free(link);
        return value;
    }

    ListLink * link = _getLink(list, index);
    ListLink * before = link->prev;
    ListLink * after = link->next;
    _chainTogether(before, after);

    void * value = link->value;
    free(link);
    return value;
}

void _deleteAt(ListTemplate * list, int index) {
    void * value = _popAt(list, index);
    free(value);
}