#include <stdlib.h>
#include <string.h>
#include "phonebook_opt.h"

extern int nameLength;
static char *pAlpha[ALPHABET_NUMBER] = {NULL};

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastname[], entry *pHead)
{
    int length = strlen(lastname);
    pHead = (entry *)(pAlpha[lastname[0] - 'a']);

    while (pHead != NULL) {
        if (length >= pHead->shortestName &&
                length <= pHead->longestName &&
                strncmp(lastname, pHead->lastName, length) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    if (e->shortestName == 0) {
        strcpy(e->lastName, lastName);
        e->shortestName = nameLength;
        e->longestName = nameLength;
        pAlpha[lastName[0] - 'a'] = (char *)e;
        return e;
    } else if (e->shortestName >= nameLength) {
        if (strncmp(e->lastName, lastName, nameLength) == 0) {
            e->shortestName = nameLength;
            return e;
        }
    } else if (e->longestName >= nameLength) {
        if (strncmp(e->lastName, lastName, nameLength) == 0) {
            return e;
        }
    } else {
        if (strncmp(e->lastName, lastName, e->longestName) == 0) {
            for (int i = e->longestName; i < nameLength; ++i) {
                e->lastName[i] = lastName[i];
            }

            e->longestName = nameLength;
            e->lastName[nameLength] = '\0';
            return e;
        }
    }

    e->pNext = (entry *) malloc(sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->shortestName = nameLength;
    e->longestName = nameLength;
    e->pNext = NULL;

    if (pAlpha[lastName[0] - 'a'] == NULL) {
        pAlpha[lastName[0] - 'a'] = (char *)e;
    }

    return e;
}
