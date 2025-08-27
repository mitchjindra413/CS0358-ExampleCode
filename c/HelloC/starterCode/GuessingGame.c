/**
 * Guessing Game Code Along
 * 
 * This code along implements a small guessing game in C.
 * The player has to guess a number between 1 and 100.
 * it provides feedback on whether the guess is too high or too low.
 * The game continues until the player guesses the correct number.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h> // for random number generation

int genRandomNumber(int min, int max) {
    return (rand() % max - min + 1 ) + min;
}

int getUserInput(int min, int max) {
    int input;

    printf("Type a number between %d and %d:", min, max);
    scanf("%d", &input);

    return input;
}

int compare(int input, int rand) {
    if(input < rand) {
        printf("Mystery number is greater than input\n");
        return 0;
    } else if(input > rand) {
        printf("Mystery number is less than input\n");
        return 0;
    } else {
        printf("Mystery number found\n");
        return 1;
    }
}

void guessingGame() {
    int min = 1;
    int max = 100;
    int randNum = genRandomNumber(1, 100);
    int input = 0;
    int attempts = 0;

    while(input != randNum) {
        input = getUserInput(min, max);
        
        attempts++;
        if(compare(input, randNum)) {
            break;
        }
    }

    printf("Game Won: %d Attempts\n", attempts);
}

char getStartUserInput() {
    char c;
    printf("Would you like to play again? (y/n): ");
    scanf(" %c", &c);

    while(tolower(c) != 'y' && tolower(c) != 'n') {
        printf("Invalid input. Please enter y or n: ");
        scanf(" %c", &c);
    }

    return c;
}

void start() {
    int run = 1;
    printf("Guessing Game:\n");
    while(run) {
        guessingGame();

        if(getStartUserInput() == 'n') {
            break;
        }
    }

    printf("Game Ended\n");
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    start();

    return 0;
}