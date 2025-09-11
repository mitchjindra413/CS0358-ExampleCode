/**
 * Starter code for Code Along: Singly Linked List
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "NeuSinglyLinkedList.h"

/**
 * Function to create a new node
 *
 * @param value The value to store in the node.
 * @return A pointer to the newly created node, or NULL if memory allocation
 * fails.
 */
Node *__sll_create_node(int value) {
  Node *node = (Node*)malloc(sizeof(Node));
  if(node == NULL) {
    fprintf(stderr, "Memory Allocation Error\n");
    return NULL;
  }
  node->data = value;
  return node;
}

/**
 * Function to free a node
 *
 * @param node A pointer to the node to be freed.
 */
void __sll_free_node(Node *node) {
  if(node != NULL) {
    free(node);
  }
}

/**
 * Creates a new singly linked list.
 *
 * @return A pointer to the newly created list, or NULL if memory allocation
 * fails.
 */
NeuSLL *sll_create() {
  NeuSLL *sll = (NeuSLL*)malloc(sizeof(NeuSLL));
  if(sll == NULL) {
    fprintf(stderr, "Memory Allocation Error\n");
    return NULL;
  }
  sll->size = 0;
  sll->head = NULL;
  return sll;
}

/**
 * Frees the memory allocated for the singly linked list.
 *
 * @param list A pointer to the list to be freed.
 */
void sll_free(NeuSLL *list) {
  if(list == NULL) {
    return;
  }

  
  free(list);
}

/**
 * Gets the node at the specified index in the singly linked list.
 *
 * @param list A pointer to the list.
 * @param index The index of the node to retrieve.
 * @return A pointer to the node at the specified index, or NULL if the index is
 * out of bounds.
 */
Node *__sll_get_node(NeuSLL *list, size_t index) {
  if(list == NULL || list->size <= index || index < 0) {
    return NULL;
  }

  Node *curNode = list->head;
  for(size_t i = 0; i < index; i++) {
    curNode = curNode->next;
  }
  return curNode;
}

/**
 * Gets the element at the specified index in the singly linked list.
 *
 * @param list A pointer to the list.
 * @param index The index of the element to retrieve.
 * @return The value of the element at the specified index, or -1 if the index
 * is out of bounds.
 */
int get_sll_element(NeuSLL *list, size_t index) {
  if(list == NULL || list->size <= index || index < 0) {
    return -1;
  }

  return __sll_get_node(list, index)->data;
}

/**
 * Inserts an element at the specified index in the singly linked list.
 *
 * @param list A pointer to the list.
 * @param index The index at which to insert the element.
 * @param value The value to insert.
 */
void insert_sll_element(NeuSLL *list, size_t index, int value) {
  if(list == NULL || list->size <= index || index < 0) {
    return;
  }
  Node *newNode = __sll_create_node(value);
  if(newNode == NULL) {
    return;
  }

  if(index == 0) {
    newNode->next = list->head;
    list->head = newNode;
  } else {
    Node *prev = __sll_get_node(list, index - 1);
    if(prev != NULL) {
      newNode->next = prev->next;
      prev->next = newNode;
    } else {
      __sll_free_node(newNode);
      return;
    }
  }
  list->size++;
}

/**
 * Checks if the singly linked list is empty.
 *
 * @param list A pointer to the list.
 * @return true if the list is empty, false otherwise.
 */
bool is_sll_empty(NeuSLL *list) {
  
  return list->size == 0;
}

/**
 * Removes the element at the specified index in the singly linked list.
 *
 * @param list A pointer to the list.
 * @param index The index of the element to remove.
 * @return The value of the removed element, or -1 if the index is out of bounds.
 */
int remove_sll_element(NeuSLL *list, size_t index) {
  if(list == NULL || index >= list->size || index < 0) {
    return -1;
  }

  Node *removeNode = NULL;
  if(index == 0) {
    removeNode = list->head;
    list->head = list->head->next;
  } else {
    Node *prev = __sll_get_node(list, index - 1);
    if(prev != NULL) {
      removeNode = prev->next;
      prev->next = removeNode->next;
    }
  }

  if(removeNode != NULL) {
    int value = removeNode->data;
    __sll_free_node(removeNode);
    list->size--;
    return value;
  }
  return -1;
}

/**
 * Gets the size of the singly linked list.
 *
 * @param list A pointer to the list.
 * @return The number of elements in the list.
 */
size_t get_sll_size(NeuSLL *list) {
  return list->size;
}

/**
 * Pops the last element from the singly linked list.
 *
 * @param list A pointer to the list.
 * @return The value of the popped element, or -1 if the list is empty.
 */
int sll_pop(NeuSLL *list) {
  return remove_sll_element(list, list->size - 1);
}

/**
 * Pushes an element to the front of the singly linked list.
 *
 * @param list A pointer to the list.
 * @param value The value to push.
 */
void sll_push(NeuSLL *list, int value) {
  insert_sll_element(list, 0, value);
}

/**
 * Sets the element at the specified index in the singly linked list.
 *
 * @param list A pointer to the list.
 * @param index The index of the element to set.
 * @param value The value to set at the specified index.
 */
void set_sll_element(NeuSLL *list, size_t index, int value) {
  if(list == NULL || index >= list->size || index < 0) {
    return;
  }
  __sll_get_node(list, index)->data = value;
}

/**
 * Prints the elements of the singly linked list to the standard output.
 *
 * @param list A pointer to the list.
 */
void print_sll(NeuSLL *list) {
  if (list == NULL || list->head == NULL) {
    printf("[]\n");
    return;
  }

  printf("[");
  Node *current = list->head;
  while (current != NULL) {
    printf("%d", current->data);
    if (current->next != NULL) {
      printf(", ");
    }
    current = current->next;
  }
  printf("]\n");
}

/**
 * Converts the singly linked list to a string representation.
 *
 * @param list A pointer to the list.
 * @return A string representation of the list, or NULL if memory allocation
 * fails.
 */
const char *sll_to_string(NeuSLL *list) {
  if (list == NULL || list->head == NULL) {
    return strdup("[]");
  }

  size_t buffer_size = 64; // Initial buffer size
  char *buffer = (char *)malloc(buffer_size * sizeof(char));
  if (buffer == NULL) {
    return NULL; // Memory allocation failed
  }

  strcpy(buffer, "["); // Start the string with an opening bracket

  Node *current = list->head;
  while (current != NULL) {
    char temp[16]; // Temporary buffer to hold the string representation of the
                   // current node's data
    sprintf(temp, "%d", current->data); // Convert the integer to a string
    strcat(buffer,
           temp); // Append the string representation of the current node's data

    if (current->next != NULL) {
      strcat(buffer,
             ", "); // Append a comma and space if there are more elements
    }

    // Check if the buffer needs to be resized
    if (strlen(buffer) + 16 >= buffer_size) {
      buffer_size *= 2;
      buffer = (char *)realloc(buffer, buffer_size * sizeof(char));
      if (buffer == NULL) {
        return NULL; // Memory allocation failed
      }
    }

    current = current->next;
  }

  strcat(buffer, "]"); // Close the string with a closing bracket
  return buffer;
}