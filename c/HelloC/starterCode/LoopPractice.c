/**
 * Solution code for Loop Practice Code Along
 * 
 * This program demonstrates the use of loops in C.
 * 
 * @author Albert Lionelle
 * @date 2025-04-03
 */

#include <stdio.h>
#include <stdlib.h>



void forLoopPractice(int x) {
    for(int i = 0; i < x; i++) {
        printf("Step: %d\n", i);
    }
}

int main() {
    int x = 10;
    forLoopPractice(x);
    return 0;
}
