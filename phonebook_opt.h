#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#include <stdint.h>

#define MAX_LAST_NAME_SIZE 16
#define ALPHABET_NUMBER 26
#define ENCODING_LENGTH 12 //64bit / 5bit(26 characters)

/* TODO: After modifying the original version, uncomment the following
 * line to set OPT properly */
#define OPT 1
typedef struct __ENCODING_BOOK_ENTRY {
    uint64_t code;
    struct __ENCODING_BOOK_ENTRY *pNext;
} encodingEntry;

typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
    //int shortestName;
    //int longestName;
    struct __PHONE_BOOK_ENTRY *pNext;
    encodingEntry *pEncoding;
} entry;

entry *findName(char lastname[], entry *pHead);
entry *append(char lastName[], entry *e);

#endif
