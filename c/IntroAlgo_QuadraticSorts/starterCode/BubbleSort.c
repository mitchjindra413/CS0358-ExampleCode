/**
 * Solution for Code Along Bubble Sort
 *
 * @author Albert Lionelle
 * @date 2025-04-18
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#include "SortUtils.h"

// global to track swaps
long int _bs_swapCount = 0;

// function to swap two elements in an array
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
  _bs_swapCount++;
}

/** Pseudo Code
 *
 *
 ```
 Algorithm BubbleSort(A)
    Input: List A of 𝑛 elements
    Output: Mutates sorted array (A) in ascending order

    for i = 0 to n-1:
        swapped = false
        for j = 0 to n-i-2:
            if A[j] > A[j+1]:
                swap(A[j], A[j+1])
                swapped = true
        if not swapped:
            break
 ```
*
**/

// function to perform bubble sort on an array
void bubbleSort(int *arr, int size) {
  for(int i = 0; i < size; i++) {
    bool swapped = false;
    for(int j = 0; j < size - 1; j++) {
      if(arr[j] > arr[j+1]) {
        swap(&arr[j], &arr[j+1]);
        swapped = true;
      }
    }
    if(!swapped) {
      break;
    }
  }
}

void selectionSort(int *arr, int size) {
  for(int i = 0; i < size - 1; i++) {
    int min = i;
    for(int j = i + 1; j < size; j++) {
      if(arr[j] < arr[min]) {
        min = j;
      }
    }
    if(min != i) {
      swap(&arr[min], &arr[i]);
    }
  }
}

void insertionSort(int *arr, int size) {
  for(int i = 1; i < size; i++) {
    int key = arr[i];
    int j = i;
    while(j > 0 && arr[j - 1] > key) {
      arr[j] = arr[j-1];
      j = j - 1;
    }
    arr[j] = key;
  }
}

int main(int argc, char *argv[]) {
  srand(time(NULL)); // seed the random number generator
  int size = 10;
  if (argc > 1 ) {
    size = atoi(argv[1]); // get the size from command line argument
  } 
  int arr[size];
  initializeRandomArray(arr, size); // build a random array

  printf("Original array: \n");
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  int timeTaken = timeFunction(bubbleSort, arr, size);

  printf("Sorted array: \n");
  printArray(arr, size);
  printf("\n");

  printf("Number of swaps: %ld\n", _bs_swapCount);
  printTimeTaken(timeTaken); // print the time taken to sort the array

  // Selection Sort
  initializeRandomArray(arr, size); // build a random array

  printf("Original array: \n");
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  timeTaken = timeFunction(selectionSort, arr, size);

  printf("Sorted array: \n");
  printArray(arr, size);
  printf("\n");

  printf("Number of swaps: %ld\n", _bs_swapCount);
  printTimeTaken(timeTaken); // print the time taken to sort the array

  // Insertion Sort
  initializeRandomArray(arr, size); // build a random array

  printf("Original array: \n");
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  timeTaken = timeFunction(insertionSort, arr, size);

  printf("Sorted array: \n");
  printArray(arr, size);
  printf("\n");

  printf("Number of swaps: %ld\n", _bs_swapCount);
  printTimeTaken(timeTaken); // print the time taken to sort the array

  return 0;
}