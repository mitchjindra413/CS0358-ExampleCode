/**
 *  Starter code for the NeuHashtable implementation.
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "NeuHashtable.h"

NeuNode **_createNeuNodeTable(int capacity) {
  NeuNode **table = (NeuNode**)malloc(capacity * sizeof(NeuNode));
  if(!table) {
    return NULL;
  }
  for(int i = 0; i < capacity; i++) {
    table[i] = NULL;
  }
  return table;
}

/**
 * Creates a new hashtable with the given capacity.
 * For the capacity, it will find the nearest power of two greater than or equal
 * to the given capacity.
 *
 * @param capacity The initial capacity of the hashtable.
 * @return A pointer to the newly created hashtable.
 */
NeuHashtable *create_hashtable(int capacity) {
  int newCapacity = 1;
  while(newCapacity < capacity) {
    newCapacity *= 2;
  }

  NeuHashtable *hashtable = (NeuHashtable*)malloc(sizeof(NeuHashtable));
  hashtable->capacity = newCapacity;
  hashtable->size = 0;
  hashtable->table = _createNeuNodeTable(newCapacity);
  return hashtable;
}

/**
 * Frees the memory allocated for the hashtable.
 * @param hashtable A pointer to the hashtable to free.
 */
void free_hashtable(NeuHashtable *hashtable) {
  if(hashtable) {
    for(int i = 0; i < hashtable->capacity; i++) {
      NeuNode *cur = hashtable->table[i];
      while(cur) {
        NeuNode *tmp = cur;
        cur = cur->next;
        free(tmp);
      }
    }
    free(hashtable->table);
    free(hashtable);
  }
}

size_t _djb2HashFunction(const char *key) {
  size_t hash = 5381;
  int c;
  while((c = *key++)) {
    hash = ((hash << 5) + hash) + c; //hash * 33 + c
  }

  return hash;
}

size_t _getIndex(const char *key, size_t capacity) {
  return _djb2HashFunction(key) & (capacity - 1); // hash % capacity - works because capacity is power of 2
}

NeuNode *_createNeuNode(const char *itemId, const char *itemName, double itemPrice, int itemQuantity) {
  NeuNode *node = (NeuNode*)malloc(sizeof(NeuNode));
  strcpy(node->data.itemID, itemId);
  strcpy(node->data.itemName, itemName);
  node->data.itemPrice = itemPrice;
  node->data.itemQuantity = itemQuantity;
  node->next = NULL;
  return node;
}

void _doubleCapacity(NeuHashtable *hashtable) {
  int newCapacity = hashtable->capacity * SCALE_FACTOR;
  NeuNode **newTable = _createNeuNodeTable(newCapacity);

  for(int i = 0; i < hashtable->capacity; i++) {
    NeuNode *cur = hashtable->table[i];
    while(cur) {
      size_t hashIndex = _getIndex(cur->data.itemID, newCapacity);
      NeuNode *next = cur->next;
      cur->next = newTable[hashIndex];
      newTable[hashIndex] = cur;
      cur = next;
    }
  }
  free(hashtable->table);
  hashtable->table = newTable;
  hashtable->capacity = newCapacity;
}

/**
 * Adds an item to the hashtable.
 * @param hashtable A pointer to the hashtable.
 * @param itemID The ID of the item.
 * @param itemName The name of the item.
 * @param itemPrice The price of the item.
 * @param itemQuantity The quantity of the item.
 */
void add_item(NeuHashtable *hashtable, const char *itemID, const char *itemName,
              double itemPrice, int itemQuantity) {
  if(get_item(hashtable, itemID)) {
    //all ready exists
    return;
  }
  if(get_load_factor(hashtable) > LOAD_FACTOR) {
    _doubleCapacity(hashtable);
  }
  size_t hashIndex = _getIndex(itemID, hashtable->capacity);
  NeuNode *node = _createNeuNode(itemID, itemName, itemPrice, itemQuantity);
  node->next = hashtable->table[hashIndex];
  hashtable->table[hashIndex] = node;
  hashtable->size++;
}

/**
 * Gets an item from the hashtable by its ID.
 * @param hashtable A pointer to the hashtable.
 * @param itemID The ID of the item to retrieve.
 * @return A pointer to the item if found, or NULL if not found.
 */
Item *get_item(NeuHashtable *hashtable, const char *itemID) {
  size_t hashIndex = _getIndex(itemID, hashtable->capacity);
  NeuNode *cur = hashtable->table[hashIndex];
  while(cur) {
    if(strcmp(cur->data.itemID, itemID) == 0) {
      return &cur->data;
    }
    cur = cur->next;
  }
  return NULL;
}

/**
 * Gets the load factor of the hashtable.
 * @param hashtable A pointer to the hashtable.
 * @return The load factor of the hashtable.
 */
inline double get_load_factor(NeuHashtable* hashtable) {
    return (double) hashtable->size / hashtable->capacity;
}

/**
 * Removes an item from the hashtable by its ID.
 * @param hashtable A pointer to the hashtable.
 * @param itemID The ID of the item to remove.
 */
void remove_item(NeuHashtable *hashtable, const char *itemID) {
  int hashIndex = _getIndex(itemID, hashtable->capacity);
  NeuNode *cur = hashtable->table[hashIndex];
  NeuNode *prev = NULL;
  while(cur) {
    if(strcmp(cur->data.itemID, itemID) == 0) {
      if(prev) {
        prev->next = cur->next;
      } else {
        hashtable->table[hashIndex] = cur->next;
      }
      free(cur);
      hashtable->size--;
      return;
    }
    prev = cur;
    cur = cur->next;
  }
}

/**
 * Prints an item from the hastable.
 * @param item A pointer to the item to print.
 */
void __print_item(Item *item) {
  if (item != NULL) {
    printf("item(ID: %s, Name: %s, Price: %.2f, Quantity: %d)", item->itemID,
           item->itemName, item->itemPrice, item->itemQuantity);
  } else {
    printf("NULL");
  }
}

/**
 * Prints the contents of the hashtable.
 * Format is key:value seperated by commas.
 * Example: {key1:value1, key2:value2}
 * @param hashtable A pointer to the hashtable.
 */
void print_hashtable(NeuHashtable *hashtable) {
  printf("{");
  for (int i = 0; i < hashtable->capacity; i++) {
    NeuNode *current = hashtable->table[i];
    while (current != NULL) {
      printf("%s:", current->data.itemID);
      __print_item(&current->data);
      current = current->next;
      if (current != NULL) {
        printf(", ");
      }
    }
    if (i < hashtable->capacity - 1 && hashtable->table[i] != NULL) {
      printf(", ");
    }
  }
  printf("}\n");
}

/**
 * Prints the array with a count of number of items in 
 * each index of the hashtable. An example layout would be
 * [1, 0, 0, 0, 0, 0, 0, 1]
 * where the first index has 1 item and the last index has 1 item.
 */
void print_table_visual(NeuHashtable *hashtable) {
    printf("[");
    for (int i = 0; i < hashtable->capacity; i++) {
        NeuNode* current = hashtable->table[i];
        int count = 0;
        while (current != NULL) {
            count++;
            current = current->next;
        }
        printf("%d", count);
        if (i < hashtable->capacity - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}