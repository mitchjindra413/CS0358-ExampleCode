
/** 
 * Starter Code for Dijkstra's Shortest Path Algorithm Code Along
**/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "dijkstra.h"

/// Supporting Heap Data Structures

typedef struct {
  int data; // Vertex index
  int dist; // Distance from source
} NeuHeapNode;

typedef struct {
  int size;            // Current size of the heap
  int capacity;        // Maximum capacity of the heap
  NeuHeapNode **array; // Array of heap nodes
} NeuHeap;

/**
 * Creates a new min heap with the given capacity.
 * @param capacity The initial capacity of the heap.
 * @return A pointer to the created min heap.
 */
NeuHeap *__createHeap(int capacity) {
  NeuHeap *minHeap = (NeuHeap *)malloc(sizeof(NeuHeap));
  minHeap->size = 0;
  minHeap->capacity = capacity; // Initial capacity
  minHeap->array =
      (NeuHeapNode **)malloc(minHeap->capacity * sizeof(NeuHeapNode *));
  return minHeap;
}

/**
 * Frees the memory allocated for the min heap.
 * @param minHeap The min heap to be freed.
 */
void __freeHeap(NeuHeap *minHeap) {
  for (int i = 0; i < minHeap->size; i++) {
    free(minHeap->array[i]);
  }
  free(minHeap->array);
  free(minHeap);
}

/**
 * Inserts a new node into the min heap.
 * @param minHeap The min heap to insert into.
 * @param data The vertex index.
 * @param dist The distance from the source.
 * @return A pointer to the newly created node.
 */
NeuHeapNode *__heapInsert(NeuHeap *minHeap, int data, int dist) {
  NeuHeapNode *newNode = (NeuHeapNode *)malloc(sizeof(NeuHeapNode));
  newNode->data = data;
  newNode->dist = dist;
  minHeap->array[minHeap->size] = newNode;
  minHeap->size++;
  return newNode;
}

/**
 * Swaps two nodes in the min heap.
 * @param a Pointer to the first node.
 * @param b Pointer to the second node.
 */
void __heapSwap(NeuHeapNode **a, NeuHeapNode **b) {
  NeuHeapNode *temp = *a;
  *a = *b;
  *b = temp;
}

/**
 * Helper functions for heap operations.
 */
int __heapParent(int i) { return (i - 1) / 2; }
int __heapLeft(int i) { return (2 * i + 1); }
int __heapRight(int i) { return (2 * i + 2); }
bool __heapIsEmpty(NeuHeap *minHeap) { return minHeap->size == 0; }

/**
 * Heapifies a subtree rooted at index i.
 * @param minHeap The min heap to heapify.
 * @param i The index of the root of the subtree.
 */
void __heapify(NeuHeap *minHeap, int i) {
  int smallest = i;
  int left = __heapLeft(i);
  int right = __heapRight(i);

  // Check if left child is smaller than root
  if (left < minHeap->size &&
      minHeap->array[left]->dist < minHeap->array[smallest]->dist) {
    smallest = left;
  }

  // Check if right child is smaller than smallest so far
  if (right < minHeap->size &&
      minHeap->array[right]->dist < minHeap->array[smallest]->dist) {
    smallest = right;
  }

  // If smallest is not root
  if (smallest != i) {
    // Swap the nodes
    __heapSwap(&minHeap->array[i], &minHeap->array[smallest]);
    // Recursively heapify the affected sub-tree
    __heapify(minHeap, smallest);
  }
}

/**
 * Decreases the key (distance) of a node in the min heap.
 * @param minHeap The min heap to update.
 * @param node The node to update.
 * @param newDist The new distance value.
 */
void __heapDecreaseKey(NeuHeap *minHeap, NeuHeapNode *node, int newDist) {
  node->dist = newDist;
  int i = node->data;
  while (i != 0 &&
         minHeap->array[__heapParent(i)]->dist > minHeap->array[i]->dist) {
    __heapSwap(&minHeap->array[i], &minHeap->array[__heapParent(i)]);
    i = __heapParent(i);
  }
}

/**
 * Extracts the minimum node from the min heap.
 * @param minHeap The min heap to extract from.
 * @return The extracted node.
 */
NeuHeapNode *__heapExtractMin(NeuHeap *minHeap) {
  if (minHeap->size == 0) {
    return NULL;
  }
  NeuHeapNode *root = minHeap->array[0];
  if (minHeap->size > 1) {
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    __heapify(minHeap, 0);
  } else {
    minHeap->size--;
  }
  return root;
}

///////   Dijkstra's Algorithm Implementation   //////////
/**
 * Implements Dijkstra's algorithm to find the shortest path from a source
 * vertex to all other vertices.
 * @param graph The adjacency list representation of the graph.
 * @param src The source vertex.
 * @param dist Output array to store the shortest distance from source to each
 * vertex.
 * @param prev Output array to store the previous node in the optimal path.
 */
void dijkstra(AdjListGraph *graph, int src, int *dist, int *prev) {
  // Initialize distance array and previous array
  
  // Create a min heap to store vertices and their distances
  

  // Insert all vertices into the min heap
  // Track the nodes, so we can have direct access to 
  // update the distance instead of having to search for the node

  // Main loop for Dijkstra's algorithm

    // If the extracted vertex is at infinity, all remaining vertices are
    // unreachable

    // For each adjacent vertex v, update dist[v] if there's a shorter path
    // through u

}

/**
 * Prints the shortest path from source to a given vertex.
 * @param src The source vertex.
 * @param dest The destination vertex.
 * @param prev Array containing the previous node information.
 * @param V The maximum number of vertices in the graph.
 */
void printPath(int dest, int *prev, int V) {
  // Create a temporary array to store the path
  int path[V]; 
  int pathLength = 0;

  // First, collect the path in reverse order
  for (int v = dest; v != -1; v = prev[v]) {
    path[pathLength++] = v;
  }

  // Then print the path in correct order (source to destination)
  for (int i = pathLength - 1; i >= 0; i--) {
    printf("%d", path[i]);
    if (i != 0) {
      printf(" -> ");
    }
  }
}

/**
 * Prints the distance array showing shortest distances from source to all
 * vertices.
 * @param dist Array containing shortest distances.
 * @param prev Array containing previous nodes in the optimal path.
 * @param V The number of vertices.
 */
void printSolution(int *dist, int *prev, int V) {
  printf("Shortest Path from Source to Destination:\n");
  for (int i = 0; i < V; i++) {
    if (dist[i] != INT_MAX) {
      printf("Shortest path to vertex %d is %d with path: ", i, dist[i]);
      printPath(i, prev, V);
      printf("\n");
    } else {
      printf("Vertex %d is unreachable from source\n", i);
    }
  }
  printf("\n");
}