#ifndef _LIST_H_
#define _LIST_H_
#include <stddef.h>
typedef struct Node{
    void *data;
    struct Node *next;
}Node;
typedef struct wwList{
    Node *head;
    int numElems;
    size_t elemSize;
    int isMalloced;
}wwList;

wwList* wwList_CreateEmpty(size_t elemSize, int isMalloced);
void wwList_Append(wwList *list, void *data);
void wwList_Remove(wwList *list, void *data);
void wwList_Delete(wwList *list);
#endif /* _LIST_H_ */