#include <stdlib.h>
#include <string.h>
#include "phonebook_opt.h"

static entry *pRoot = NULL;
static entry *pContainer = NULL;
static entry *pTracker = NULL;

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastname[], entry *pHead)
{
    int length = strlen(lastname);

    //binary tree search
    while (pHead != NULL && length != pHead->nameLength) {
        if (length < pHead->nameLength) {
            pHead = pHead->pLeftNode;
        } else {
            pHead = pHead->pRightNode;
        }
    }

    while (pHead != NULL) {
        if (strcasecmp(lastname, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }

    return NULL;
}

entry *append(char lastName[], entry *e)
{
    if (pRoot == NULL) {
        pRoot = e;
        pRoot->pLeftNode = pRoot->pRightNode = NULL;
        pRoot->pLast = pRoot;
        pContainer = (entry *) malloc(sizeof(entry));
    }

    pTracker = pRoot;

    //build a binary tree according to name length
    while (e->nameLength != pTracker->nameLength) {
        if (e->nameLength < pTracker->nameLength) {
            if (pTracker->pLeftNode == NULL) {
                pTracker->pLeftNode = (entry *) malloc(sizeof(entry));
                pTracker = pTracker->pLeftNode;
                pTracker->pLeftNode = pTracker->pRightNode = NULL;
                pTracker->pNext = NULL;
                pTracker->pLast = pTracker;
                pTracker->nameLength = e->nameLength;
                break;
            }

            pTracker = pTracker->pLeftNode;
        } else {
            if (pTracker->pRightNode == NULL) {
                pTracker->pRightNode = (entry *) malloc(sizeof(entry));
                pTracker = pTracker->pRightNode;
                pTracker->pLeftNode = pTracker->pRightNode = NULL;
                pTracker->pNext = NULL;
                pTracker->pLast = pTracker;
                pTracker->nameLength = e->nameLength;
                break;
            }

            pTracker = pTracker->pRightNode;
        }
    }

    strcpy(pTracker->pLast->lastName, lastName);
    pTracker->pLast->pNext = (entry *) malloc(sizeof(entry));
    pTracker->pLast = pTracker->pLast->pNext;
    pTracker->pLast->pLeftNode = pTracker->pLast->pRightNode = NULL;
    pTracker->pLast->pNext = NULL;

    return pContainer;
}
