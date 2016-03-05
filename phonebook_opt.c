#include <stdlib.h>
#include <string.h>
#include "phonebook_opt.h"

//entity for each name length
static entry root[MAX_LAST_NAME_SIZE];
static entry *pEntry = NULL;

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastname[], entry *pHead)
{
    int nameIndex = strlen(lastname) - 1;
    int capitalIndex = lastname[0] - 'a';
    pHead = root[nameIndex].pCapital[capitalIndex];

    while (pHead != NULL) {
        if (strcasecmp(lastname, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }

    return NULL;
}

entry *append(char lastName[], entry *e)
{
    if (e->nameLength <= 0 || e->nameLength > MAX_LAST_NAME_SIZE) {
        return e;
    }

    int nameIndex = e->nameLength-1;
    int capitalIndex = lastName[0] - 'a';

    pEntry = root[nameIndex].pCapital[capitalIndex]->pLast;
    strcpy(pEntry->lastName, lastName);
    pEntry->pNext = (entry *) malloc(sizeof(entry));
    pEntry->pNext->pNext = NULL;
    root[nameIndex].pCapital[capitalIndex]->pLast = pEntry->pNext;
    return e;
}

int initBook(void)
{
    int i = 0, j = 0;
    for (i = 0; i < MAX_LAST_NAME_SIZE; ++i) {
        root[i].pNext = NULL;
        root[i].pLast = &root[i];

        for (j = 0; j < ALPHABET_NUMBER; ++j) {
            root[i].pCapital[j] = (entry *) malloc(sizeof(entry));
            root[i].pCapital[j]->pNext = NULL;
            root[i].pCapital[j]->pLast = root[i].pCapital[j];
        }
    }

    return 0;
}

int closeBook(void)
{
    int i = 0, j = 0;
    for (i = 0; i < MAX_LAST_NAME_SIZE; ++i) {
        root[i].pNext = NULL;
        root[i].pLast = &root[i];

        for (j = 0; j < ALPHABET_NUMBER; ++j) {
            free(root[i].pCapital[j]);
        }
    }

    return 0;
}
