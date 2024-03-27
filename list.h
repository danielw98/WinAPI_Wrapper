#ifndef _LIST_H_
#define _LIST_H_
#include <stddef.h>

typedef void (*wwListFreeFunc)(void *data);
typedef struct Node{
    void *data;
    struct Node *next;
}Node;
typedef struct wwList{
    Node *head;
    int numElems;
    int isMalloced;
    size_t elemSize;
    wwListFreeFunc freeFunc;
}wwList;

wwList* wwList_CreateEmpty(size_t elemSize, int isMalloced, wwListFreeFunc freeFunc);
void wwList_Append(wwList *list, void *data);
void wwList_Remove(wwList *list, void *data);
void wwList_Delete(wwList *list);
#endif /* _LIST_H_ */