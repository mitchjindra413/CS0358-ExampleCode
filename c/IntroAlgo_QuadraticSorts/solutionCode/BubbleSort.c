/**
 * Solution for Code Along Bubble Sort
 *
 * @author Albert Lionelle
 * @date 2025-04-18
 */

#include <stdio.h>
#include <stdlib.h>

#include "SortUtils.h"

// global to track swaps
long int _bs_opCount = 0;

// function to swap two elements in an array
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
  _bs_opCount++;
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
  for (int i = 0; i < size; i++) {
    _bs_opCount++;
    int swapped = 0; // flag to check if any swaps were made
    for (int j = 0; j < size - i - 1; j++) {
      _bs_opCount++;
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
        swapped = 1;
      }
    }
    if (!swapped) {
      break;
    }
  }
}

int main(int argc, char *argv[]) {
  srand(time(NULL)); // seed the random number generator
  int size = 10;
  if (argc > 1) {
    size = atoi(argv[1]); // get the size from command line argument
  }
  int arr[size];
  // initializeRandomArray(arr, size); // build a random array
  initializeReverseSortedArray(arr, size);

  printf("Original array: \n");
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  int timeTaken = timeFunction(bubbleSort, arr, size);

  printf("Sorted array: \n");
  printArray(arr, size);
  printf("\n");

  printf("Number of swaps: %ld\n", _bs_opCount);
  printTimeTaken(timeTaken); // print the time taken to sort the array

  return 0;
}