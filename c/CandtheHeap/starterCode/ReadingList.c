/**
 * Starter code for Reading List Code Along. 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//create structs for books and readinglist
//create functions for create reading list and freeing it

typedef struct {
    char author[100];
    char title[256];
} Book;

typedef struct {
    Book *books;
    int size;
    int current;
} ReadingList;

ReadingList *createReadingList(int size) {
    ReadingList *readingList = (ReadingList *)malloc(sizeof(ReadingList));
    readingList->books = (Book *)malloc(sizeof(Book) * size);
    readingList->size = size;
    readingList->current = 0;
    return readingList;
}

void freeReadingList(ReadingList *readingList) {
    free(readingList->books);
    free(readingList);
}

void printReadingList(ReadingList *readingList) {
    for(int i = 0; i < readingList->current; i++) {
        printf("Title: %s, Author: %s\n", readingList->books[i].title, readingList->books[i].author);
    }
}

void copyString(char *dst, const char *src, int size) {
    strncpy(dst, src, size - 1);
    dst[size - 1] = '\0';
}

void addBook(ReadingList *readingList, const char *title, const char *author) {
    int idx = readingList->current;
    Book *single = &readingList->books[idx];
    copyString(single->author, author, sizeof(single->author));
    copyString(single->title, title, sizeof(single->title));

    readingList->current++;
}

void removeBook(ReadingList *readingList, int idx) {
    if(idx < 0 || idx >= readingList->current) {
        printf("Invalid index");
    }
    for(int i = idx; i < readingList->current - 1; i++) {
        readingList->books[i] = readingList->books[i+1];
    }
    readingList->current--;
}

int main() {
    ReadingList *myList = createReadingList(10);

    addBook(myList, "Test Book", "Test");
    addBook(myList, "T Book2", "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAb");

    printReadingList(myList);
    removeBook(myList, 1);
    printReadingList(myList);
    freeReadingList(myList);
    return 0;
}