/**
 * Starter File for code along Array Practice. 
 * This file will demonstrate basic array operations.
 * This will include functions for initializing, printing, and manipulating arrays.
 * 
 */

#include <stdio.h>
#include <stdlib.h>


int main() {
    int numbers[5] = {1,2,3,4,5};
    for(int i = 0; i < 5; i++) {
        printf("%d",numbers[i]);
    }
    return 0;
}