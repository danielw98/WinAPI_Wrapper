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
wwList* wwList_CreateEmpty(size_t elemSize, int isMalloced)
{
    wwList *list = (wwList*) malloc(sizeof(wwList));
    list->head = NULL;
    list->numElems = 0;
    list->elemSize = elemSize;
    list->isMalloced = isMalloced;
    //fprintf(fp, "creating empty list\n");
    return list;
}
void wwList_Append(wwList *list, void *data)
{
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    Node *node = list->head;
    if(list->head == NULL)
    {
        list->head = newNode;
        fprintf(fp, "first button %p\n", newNode->data);
        return;
    }
    while(node->next != NULL)
        node = node->next;
    node->next = newNode;
    fprintf(fp, "appending button %p\n", node->data);
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
    Node *node = list->head;
    while(node != NULL)
    {
        Node *nextNode = node->next;
        if(list->isMalloced == TRUE)
            free(node->data);
        free(node);
        node = nextNode;
        list->numElems--;
    }
    free(list);
}