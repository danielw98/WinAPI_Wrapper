#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
extern FILE *fp;
wwList* wwList_CreateEmpty(size_t elemSize, int isMalloced, wwListFreeFunc freeFunc)
{
    wwList *list = (wwList*) malloc(sizeof(wwList));
    list->head = NULL;
    list->numElems = 0;
    list->elemSize = elemSize;
    list->isMalloced = isMalloced;
    list->freeFunc = freeFunc;
    return list;
}
void wwList_Append(wwList *list, void *data)
{
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    fprintf(fp, "%s %d list = %p\n", __FILE__, __LINE__, list);
    Node *node = list->head;
    if(list->head == NULL)
    {
        list->head = newNode;
        return;
    }
    while(node->next != NULL)
        node = node->next;
    node->next = newNode;
    list->numElems++;
}
void wwList_Remove(wwList *list, void *data)
{
    Node *node = list->head;
    int removed = FALSE;
    if(node == NULL)
        return;
    while(node->next != NULL)
    {
        if(memcmp(node->next->data, data, list->elemSize) == 0)
        {
            removed = TRUE;
            Node *toDelete = node->next;
            node->next = node->next->next;
            if(list->freeFunc != NULL)
                list->freeFunc(toDelete);
            free(toDelete);
            break;
        }
        node = node->next;
    }
    if(removed == TRUE)
        list->numElems--;
}
void wwList_Delete(wwList *list)
{
    if(list == NULL)
        return;
    Node *node = list->head;
    while(node != NULL)
    {
        Node *nextNode = node->next;
        if(list->isMalloced == TRUE)
        {
            if(list->freeFunc != NULL)
                list->freeFunc(node->data);
            free(node->data);
        }
        free(node);
        node = nextNode;
        list->numElems--;
    }
    free(list);
}