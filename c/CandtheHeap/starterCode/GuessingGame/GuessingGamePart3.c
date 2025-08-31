/**
 * Starter code for the Guessing Game Part 3 code along
 * 
 * This code is mostly the same for Guessing Game Part 2
 */

#include <stdbool.h> // for boolean type
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for string manipulation
#include <time.h>   // for random number generation

#include "GuessingGame.h"

int getRandomNumber(int min, int max) {
  // Generate a random number between min and max
    return (rand() % (max - min + 1)) + min;
}

int getInput() {
    char buffer[20];
    int input = 0;
    scanf("%s", buffer);
    input = atoi(buffer);
    return input;
}

GameState *initializeGameState(int maxAttempts, int playerType, int min, int max) {
    GameState *gameState = (GameState*)malloc(sizeof(GameState));
    gameState->guesses = (int*)malloc(sizeof(int) * maxAttempts);
    gameState->attempts = 0;
    gameState->maxAttempts = maxAttempts;
    gameState->max = max;
    gameState->min = min;
    gameState->playerType = playerType;
    return gameState;
}

void freeGameState(GameState *gameState){ 
    free(gameState->guesses);
    free(gameState);
}

// a game that only gives X number of choices
// track the number of attempts
// i want to track the guesses
bool runGame(int randomNumber, GameState *gameState) {
    int guess = 0;
    int computerMin = gameState->min;
    int computerMax = gameState->max;

    while(gameState->attempts < gameState->maxAttempts) {
        if(gameState->playerType == HUMAN) {
            printf("Enter your guess (%d-%d): ", gameState->min, gameState->max);
            guess = getInput();
            feedback(randomNumber - guess);
        } else {
            guess = computerMin + (computerMax - computerMin) / 2;
        }
        gameState->guesses[gameState->attempts] = guess;
        gameState->attempts++;
        if(guess == randomNumber) {
            return true;
        }
        if(gameState->playerType == COMPUTER) {
            if(guess > randomNumber) {
                computerMax = guess - 1;
            } else {
                computerMin = guess + 1;
            }
        }
    }

    return false;
}

void feedback(int state) {
    if(state < 0) {
        printf("Too High! Try again.\n");
    } else if(state > 0) {
        printf("Too low! Try again.\n");
    } 
}

void giveFeedback(int randomNumber, bool found, GameState *gameState) {
    if (found) {
        printf("Congratulations! %s guessed the number %d in %d attempts.\n", gameState->playerType == HUMAN ? "You" : "The computer",
            randomNumber, gameState->attempts);
    } else {
        printf("Game Over! The number was %d.\n", randomNumber);
    }
    printf("%s guesses were: ", gameState->playerType == HUMAN ? "Your" : "The computer's");
    for (int i = 0; i < gameState->attempts; i++) {
        printf("%d ", gameState->guesses[i]);
    }
    printf("\n\n");
}

void start() {
    printf("Welcome to the Guessing Game!\n");
    char choice[20];

    while (strcasecmp(choice, "exit") != 0) {
        printf("Play: Human\n");
        printf("Play: Computer\n");
        printf("Exit\n");
        printf("Enter your choice (human | computer | exit): ");
        scanf("%s", choice);

        if (strcasecmp(choice, "human") == 0 || strcasecmp(choice, "computer") == 0) {
            int randomNumber = getRandomNumber(1, 100);
            int playerType = strcasecmp(choice, "human") == 0 ? HUMAN : COMPUTER;
            GameState *gameState = initializeGameState(DEFAULT_MAX_ATTEMPTS, playerType, DEFAULT_MIN, DEFAULT_MAX);
            printf("Starting the game...\n");
            bool found = runGame(randomNumber, gameState);
            giveFeedback(randomNumber, found, gameState);
            freeGameState(gameState);
        } else if (strcasecmp(choice, "exit") == 0) {
            printf("Exiting the game...\n");
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
}