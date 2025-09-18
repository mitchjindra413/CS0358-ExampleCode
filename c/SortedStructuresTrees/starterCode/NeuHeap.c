/**
* Starter code for Code Along Heap
*
**/

#include "NeuHeap.h"

/**
 * Creates a new heap with the given capacity.
 * @param capacity The maximum number of elements the heap can hold.
 * @return A pointer to the newly created heap.
 */
NeuHeap* create_heap(int capacity) {
    NeuHeap *heap = (NeuHeap*)malloc(sizeof(NeuHeap));
    if(!heap) {
      return NULL;
    }
    int *data = (int*)malloc(capacity * sizeof(int));
    if(!data) {
      free(heap);
      return NULL;
    }
    heap->capacity = capacity;
    heap->data = data;
    heap->size = 0;
    return heap;
}

/**
 * Frees the memory allocated for the heap.
 * @param heap A pointer to the heap to free.
 */
void free_heap(NeuHeap* heap) {
    if(!heap) {
      return;
    }

    free(heap->data);
    free(heap);
}

void _swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void _doubleCapacity(NeuHeap *heap) {
  int newCapacity = heap->capacity * SCALE_FACTOR;
  int *newData = (int*)realloc(heap->data, newCapacity * sizeof(int));
  
  heap->data = newData;
  heap->capacity = newCapacity;
}

/**
 * Adds a new element to the heap.
 * @param heap A pointer to the heap.
 * @param value The value to add to the heap.
 */
void enqueue(NeuHeap* heap, int value) {
    if(heap->size == heap->capacity) {
      _doubleCapacity(heap);
    }

    heap->data[heap->size] = value;
    int index = heap->size;
    heap->size++;

    while(index > 0) {
      int parentIdx = (index - 1) / 2;
      if(heap->data[index] > heap->data[parentIdx]) {
        _swap(heap->data[index], heap->data[parentIdx]);
        index = parentIdx;
      } else {
        break;
      }
    }
}

/**
 * Removes and returns the highest-priority element from the heap.
 * @param heap A pointer to the heap.
 * @return The value of the highest-priority element.
 */
int dequeue(NeuHeap* heap) {
    int rootVal = heap->data[0];
    heap->size--;
    heap->data[0] = heap->data[heap->size];

    int idx = 0;
    while(idx < 0) {
      int left = 2 * idx + 1;
      int right = 2 * idx +2;
      int largest = idx;
      if(left < heap->size && heap->data[left] > heap->data[largest]) {
        largest = left;
      }
      if(right < heap->size && heap->data[right] > heap->data[largest]) {
        largest = right;
      }
      if(largest != idx) {
        _swap(&heap->data[largest], &heap->data[idx]);
      } else {
        break;
      }
    }
    return rootVal;
}

/**
 * Prints the elements of the heap.
 * @param heap A pointer to the heap.
 */
void print_heap(NeuHeap* heap) {
    // TODO: Implement
}

/**
 * Prints the heap in a visual format.
 * @param heap A pointer to the heap.
 */
 void print_heap_visually(NeuHeap *heap) {
    if (heap == NULL || heap->size == 0) {
      printf("Heap is empty\n");
      return;
    }
    // Print the heap in a visual format
  
    int max_level = 0;
    int temp_size = heap->size;
    while (temp_size > 0) {
      temp_size = temp_size / 2;
      max_level++;
    }
  
    for (int i = 0; i < max_level; i++) {
      int start_index = (1 << i) - 1;     // First index at this level
      int end_index = (1 << (i + 1)) - 1; // One past the last index at this level
  
      // Print leading spaces for centering
      int spaces = (1 << (max_level - i - 1)) - 1;
      for (int s = 0; s < spaces; s++) {
        printf("  ");
      }
  
      // Print nodes at this level
      for (int j = start_index; j < end_index && j < heap->size; j++) {
        printf("%2d", heap->data[j]);
  
        // Print spaces between nodes at this level
        if (j < end_index - 1 && j + 1 < heap->size) {
          int between_spaces = (1 << (max_level - i)) - 1;
          for (int s = 0; s < between_spaces; s++) {
            printf("  ");
          }
        }
      }
      printf("\n");
    }
    printf("\n");
  }