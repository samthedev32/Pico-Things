#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
    void *userData;
    struct list *next;
} list;

// Add new element to List
void list_add(list **l, void *userData)
{
    list *new = (list *)malloc(sizeof(list));
    list *last = *l;

    new->userData = userData;
    new->next = NULL;

    if (*l == NULL)
    {
        *l = new;
        return;
    }

    while (last->next != NULL)
        last = last->next;
    last->next = new;

    return;
}

// Get Element from List
void *list_get(list *l, int n)
{
    if (l == NULL)
        return NULL;

    list *tmp = l;
    for (int i = 0; i < n; i++)
    {
        if (tmp->next == NULL)
            return NULL;
        tmp = tmp->next;
    }

    return tmp->userData;
}

// Set Element's Data in List
void list_set(list *l, int n, void *userData)
{
    if (l == NULL)
        return;

    list *tmp = l;
    for (int i = 0; i < n; i++)
    {
        if (tmp->next == NULL)
            return;
        tmp = tmp->next;
    }

    tmp->userData = userData;
}

// Iterate List
int list_iterate(list *origin, list **i)
{
    if (*i == NULL)
        *i = origin;
    else
        *i = (*i)->next;

    if (*i == NULL)
        return 0;
    else
        return 1;
}