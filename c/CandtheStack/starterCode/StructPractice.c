/**
 * Starter code for Code Along Struct Practice.
 * In this code along we will explore structs, initializing
 * and using pointers to structs for access in functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
} Person;

void printPerson(Person *p) {
    printf("Name: %s. Age: %d.\n", p->name, p->age);
}

void updateAge(Person *p, int age) {
    p->age = age;
}

void updateName(Person *p, char *name) {
    strcpy(p->name, name);
}


int main() {
    Person p;
    strcpy(p.name, "Test");
    p.age = 10;
    printPerson(&p);

    updateAge(&p, 20);
    updateName(&p, "Update");
    printPerson(&p);

    Person p2 = {"Bob", 25};
    printPerson(&p2);

    return 0;
}