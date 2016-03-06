#include <stdlib.h>
#include <string.h>
#include "phonebook_opt.h"

extern int nameLength;
static char *pAlpha[ALPHABET_NUMBER] = {NULL};
static encodingEntry *pLast = NULL;
static uint64_t encodingMask = 31; //11111

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastname[], entry *pHead)
{
    int length = strlen(lastname);
    int i = 0;
    pHead = (entry *)(pAlpha[lastname[0] - 'a']);
    char name[MAX_LAST_NAME_SIZE] = {0};
    uint64_t charCode = 0;

    while (pHead != NULL) {
        pLast = pHead->pEncoding; //reserve first encoding entry

        while (pHead->pEncoding != NULL) {
            for (i = 0; i < ENCODING_LENGTH; ++i) {
                charCode = pHead->pEncoding->code >> 5 * i;

                if ((charCode & encodingMask) > 0) {
                    name[i] = (charCode & encodingMask) - 1 + 'a';
                } else {
                    break;
                }
            }

            name[i] = '\0';

            if (strncmp(lastname, name, length) == 0) {
                pHead->pEncoding = pLast;
                return pHead;
            }

            pHead->pEncoding = pHead->pEncoding->pNext;
        }

        pHead->pEncoding = pLast;

        if (strncmp(lastname, pHead->lastName, length) == 0) {
            return pHead;
        }

        pHead = pHead->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    if (pAlpha[0] == NULL) { //pHead
        e->pEncoding = NULL;
        pAlpha[lastName[0] - 'a'] = (char *)e;
    }

    if (nameLength > ENCODING_LENGTH || //encode one char needs 5 bit
            pAlpha[lastName[0] - 'a'] == NULL) { //do not encode first character to get index
        if (e->pEncoding != NULL) {
            e->pNext = (entry *) malloc(sizeof(entry));
            e = e->pNext;
            e->pNext = NULL;
            e->pEncoding = NULL;
        }

        if (pAlpha[lastName[0] - 'a'] == NULL) {
            pAlpha[lastName[0] - 'a'] = (char *)e;
        }

        if (nameLength > ENCODING_LENGTH) {
            strcpy(e->lastName, lastName);
            e->pNext = (entry *) malloc(sizeof(entry));
            e = e->pNext;
            e->pNext = NULL;
            e->pEncoding = NULL;
        }

        return e;
    }

    if (e->pEncoding == NULL) {
        e->pEncoding = (encodingEntry *) malloc(sizeof(encodingEntry));
        pLast = e->pEncoding;
        pLast->code = 0;
        pLast->pNext = NULL;
    } else {
        pLast->pNext = (encodingEntry *) malloc(sizeof(encodingEntry));
        pLast = pLast->pNext;
        pLast->code = 0;
        pLast->pNext = NULL;
    }

    for (int i = nameLength-1; i >= 0; --i) { //encode from last char
        pLast->code <<= 5;
        pLast->code += lastName[i] - 'a' + 1;
    }

    return e;
}
