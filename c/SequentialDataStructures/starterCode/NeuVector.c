/**
 * Starter Code for Code Along - vector
 **/

#include <stdio.h>
#include <errno.h>


#include "NeuVector.h"

/**
 * Creates a new vector with the specified initial capacity.
 * 
 * @param initial_capacity The initial capacity of the vector.
 * @return A pointer to the newly created vector, or NULL if memory allocation fails.
 */
NeuVector* create_vector(size_t initial_capacity) {
    // TODO: Implement this function
    NeuVector* vector = (NeuVector*)malloc(sizeof(NeuVector));
    if(vector == NULL) {
        return NULL;
    }
    vector->data == (int*)malloc(initial_capacity * sizeof(int));
    if(vector->data == NULL) {
        free(vector);
        return NULL;
    }
    vector->size = 0;
    vector->capacity = initial_capacity;
    return vector;
}
/**
 * Resizes vector
 * @param vector
 * @param new_capacity
 */
void _neu_vector_resize(NeuVector* vector, int new_capacity) {
    if(new_capacity > vector->capacity) {
        int *new_data = (int*)realloc(vector->data, new_capacity * sizeof(int));
        if(new_data != NULL) {
            vector->data = new_data;
            vector->capacity = new_capacity;
        }
    }  else {
        fprintf(stderr, "Memory allocation failed\n");
    }
}

/**
 * Frees the memory allocated for the vector.
 * 
 * @param vector A pointer to the vector to be freed.
 */
void free_vector(NeuVector* vector) {
    // TODO: Implement this function
    if(vector != NULL) {
        free(vector->data);
        free(vector);
    }
}

/**
 * Appends an element to the end of the vector.
 * 
 * @param vector A pointer to the vector.
 * @param value The value to append.
 */
void append_vector_element(NeuVector* vector, int value) {
    // TODO: Implement this function
    insert_vector_element(vector, vector->size, value);
}

/**
 * Finds the first occurrence of a value in the vector.
 * 
 * @param vector A pointer to the vector.
 * @param value The value to find.
 * @return The index of the first occurrence of the value, or -1 if the value is not found.
 */
int contains_element(NeuVector* vector, int value) {
    // TODO: Implement this function
    if(vector == NULL) {
        fprintf(stderr, "No vector");
        return NULL;
    }
    for(size_t i = 0; i < vector->size; i++) {
        if(vector->data[i] == value) {
            return i;
        }
    }
    return -1;
}

/**
 * Gets the current capacity of the vector.
 * 
 * @param vector A pointer to the vector.
 * @return The capacity of the vector.
 */
int get_vector_capacity(NeuVector* vector) {
    // TODO: Implement this function
    if(vector == NULL) {
        fprintf(stderr, "No vector\n");
        return NULL;
    }
    return vector->capacity;
}

/**
 * Gets the element at the specified index in the vector.
 * 
 * @param vector A pointer to the vector.
 * @param index The index of the element to retrieve.
 * @return The value of the element at the specified index.
 */
int get_vector_element(NeuVector* vector, size_t index) {
    // TODO: Implement this function
    if(vector == NULL) {
        fprintf(stderr, "No vector\n");
        return NULL;
    }
    if(index >= vector->size) {
        fprintf(stderr, "Index out of bounds\n");
        return NULL;
    }
    for(size_t i = 0; i < vector->size; i++) {
        if(i == index) {
            return vector->data[i];
        }
    }
    return -1;
}

/**
 * Gets the current size of the vector.
 * 
 * @param vector A pointer to the vector.
 * @return The number of elements in the vector.
 */
int get_vector_size(NeuVector* vector) {
    // TODO: Implement this function
    if(vector == NULL) {
        fprintf(stderr, "No vector\n");
        return NULL;
    }
    return vector->size;
}

/**
 * Inserts an element at the specified index in the vector.
 * 
 * @param vector A pointer to the vector.
 * @param index The index at which to insert the element.
 * @param value The value to insert.
 */
void insert_vector_element(NeuVector* vector, size_t index, int value) {
    // TODO: Implement this function
    if(index > vector->size) {
        fprintf(stderr, "Index out of bounds.\n");
        return;
    }
    if(vector->size == vector->capacity) {
        _neu_vector_resize(vector, vector->capacity * SCALE_FACTOR);
    }
    for(size_t i = vector->size; i > index; i--) {
        vector->data[i] = vector->data[i-1];
    }
    vector->data[index] = value;
    vector->size++;
}

/**
 * Removes and returns the last element of the vector.
 * 
 * @param vector A pointer to the vector.
 * @return The value of the removed element, or -1 if the vector is empty.
 */
int pop_vector_element(NeuVector* vector) {
    // TODO: Implement this function
    return remove_vector_element(vector, vector->size - 1);
}

/**
 * Prints the elements of the vector to the standard output.
 * 
 * @param vector A pointer to the vector.
 */
void print_vector(NeuVector* vector) {
    printf("Vector: [");
    for(int i = 0; i < vector->size; i++) {
        printf("%d", vector->data[i]);
        if (i < vector->size - 1) {
            printf(", "); // only print comma if not the last element
        }
    }
    printf("]\n");

}

/**
 * Removes the element at the specified index in the vector.
 * 
 * @param vector A pointer to the vector.
 * @param index The index of the element to remove.
 * @return 0 if successful, or -1 if the index is out of bounds.
 */
int remove_vector_element(NeuVector* vector, size_t index) {
    // TODO: Implement this function
    if(vector == NULL) {
        fprintf(stderr, "No vector\n");
        return NULL;
    }
    if(index >= vector->size || index < 0) {
        fprintf(stderr, "Index out of bounds\n");
        errno = ERANGE;
        return -1;
    }
    errno = 0;
    int data = vector->data[index];
    for(size_t i = 0; i < vector->size; i++) {
        vector->data[i] = vector->data[i+1];
    }
    vector->size--;
    return data;
}

/**
 * Sets the element at the specified index in the vector.
 * 
 * @param vector A pointer to the vector.
 * @param index The index of the element to set.
 * @param value The value to set at the specified index.
 */
void set_vector_element(NeuVector* vector, size_t index, int value) {
    // TODO: Implement this function
    if(vector == NULL) {
        fprintf(stderr, "No vector\n");
        return;
    }
    if(index < 0 || index >= vector->size) {
        fprintf(stderr, "Index out of bounds\n");
        return;
    }
    vector->data[index] = value;
}


/**
 * Converts the vector to a string representation, to make tests easier. 
 * NOTE: this is mostly untested... use with care.
 * 
 * @param vector A pointer to the vector.
 * @return A string representation of the vector.
 */
const char* vector_to_string(NeuVector* vector) {
    if (vector == NULL || vector->size == 0 || vector->data == NULL) {
        return "[]"; // Return empty string if vector is empty
    }
    size_t buffer_size = 3 + (vector->size - 1) * 4; // Estimate buffer size
    char* buffer = (char*)malloc(buffer_size * sizeof(char));
    if (buffer == NULL) {
        return NULL; // Memory allocation failed
    }
    buffer[0] = '[';
    size_t offset = 1;
    for (size_t i = 0; i < vector->size; ++i) {
        offset += snprintf(buffer + offset, buffer_size - offset, "%d", vector->data[i]);
        if (i < vector->size - 1) {
            offset += snprintf(buffer + offset, buffer_size - offset, ", "); // Add comma and space
        }
        if(offset >= buffer_size) {
            // resize the buffer if needed
            buffer_size *= SCALE_FACTOR;
            buffer = (char*)realloc(buffer, buffer_size * sizeof(char));
            if (buffer == NULL) {
                return NULL; // Memory allocation failed
            }
        }
    }
    buffer[offset] = ']'; // Close the string representation
    buffer[offset + 1] = '\0'; // Null-terminate the string
    return buffer; // Return the string representation of the vector
}