/**
* Starter code for the code along on Priority Queue
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#include "NeuPriorityQueue.h"


/**
 * Creates a new priority queue with the given capacity.
 * @param capacity The maximum number of elements the queue can hold.
 * @return A pointer to the newly created priority queue.
 */
NeuPriorityQueue* create_priority_queue(int capacity) {
    NeuPriorityQueue *pq = (NeuPriorityQueue*)malloc(sizeof(NeuPriorityQueue));
    if(pq == NULL) {
        return NULL;
    }
    int *data = (int*)malloc(capacity * sizeof(int));
    if(!data) {
        free(pq);
        return NULL;
    }
    pq->capacity = capacity;
    pq->data = data;
    pq->size = 0;

    return pq;
}

/**
 * Frees the memory allocated for the priority queue.
 * @param queue A pointer to the priority queue to free.
 */
void free_priority_queue(NeuPriorityQueue* queue) {
    if(queue) {
        free(queue->data);
        free(queue);
    }
}

/**
 * Clears all elements from the priority queue.
 * @param queue A pointer to the priority queue to clear.
 */
void clear_priority_queue(NeuPriorityQueue* queue) {
    // TODO: Implement
}

/**
 * Removes and returns the highest-priority element from the queue.
 * @param queue A pointer to the priority queue.
 * @return The value of the highest-priority element.
 */
int dequeue(NeuPriorityQueue* queue) {
    if(!has_items(queue)) {
        fprintf(stderr, "Queue is empty\n");
    }
    int highestPrio = queue->data[queue->size - 1];
    queue->size--;
    return highestPrio;
}

void _doubleQueue(NeuPriorityQueue *queue) {
    int newCapacity = queue->capacity * SCALE_FACTOR;
    int *newData = (int*)realloc(queue->data, newCapacity * sizeof(int));
    queue->data = newData;
    queue->capacity = newCapacity;
}

/**
 * Adds a new element to the priority queue.
 * @param queue A pointer to the priority queue.
 * @param value The value to add to the queue.
 */
void enqueue(NeuPriorityQueue* queue, int value) {
    if(queue->size >= queue->capacity) {
        _doubleQueue(queue);
    }
    if(queue->size == 0) {
        queue->data[0] = value;
    } else {
        int i = queue->size - 1;
        while(i >= 0 && queue->data[i] >= value) {
            queue->data[i+ 1] = queue->data[i];
            i--;
        }
        queue->data[i+1] = value;
    }
    queue->size++;
}

/**
 * Checks if the priority queue has any items.
 * @param queue A pointer to the priority queue.
 * @return true if the queue has items, false otherwise.
 */
bool has_items(NeuPriorityQueue* queue) {
    
    return queue->size > 0;
}

/**
 * Returns the highest-priority element without removing it.
 * @param queue A pointer to the priority queue.
 * @return The value of the highest-priority element.
 */
int peek(NeuPriorityQueue* queue) {
    if(!queue) {
        return -1;
    }
    return queue->data[0];
}

/**
 * Prints the elements of the priority queue.
 * @param queue A pointer to the priority queue.
 */
void print_priority_queue(NeuPriorityQueue* queue) {
    if(queue == NULL) {
        return;
    }
    printf("Priority Queue: [")
    for(int i = queue->size - 1; i >= 0; i--) {
        printf("%d ", queue->data[i]);
    }
    printf("]\n");
}