/**
 * Starter Code for ConditionPractice Code Along
 * 
 * This program explores condition statements in C.
 * 
 */

#include <stdio.h>
#include <stdlib.h>


void printComparision(int a, int b) {
    if(a < b) {
        printf("A is less than B");
    } else if(b < a) {
        printf("B is less than A");
    } else {
        printf("A is equal to B");
    }
}


int main() {
    int a = 10;
    int b = 20;
    printComparision(a, b);
    return 0;
}
