/**
 * Starter Code for Code Along Tree Traversal
 */


#include <stdio.h>
#include <stdlib.h>

#include "NeuTree.h"

/**
 * Creates a new tree.
 * @return A pointer to the newly created tree.
 */
NeuTree* create_tree() {
    NeuTree *t = (NeuTree*)malloc(sizeof(NeuTree));
    if(!t) {
        fprintf(stderr, "Memory allocaiton Error\n");
        return NULL;
    }
    t->root = NULL;
    t->size = 0;
    return t;
}

void _freeNodes(NeuNode *node) {
    if(!node) {
        return;
    }

    _freeNodes(node->left);
    _freNodes(node->right);
    free(node);
}

/**
 * Frees the memory allocated for the tree.
 * @param tree A pointer to the tree to free.
 */
void free_tree(NeuTree* tree) {
    if(!tree) {
        return;
    }
    _freeNodes(tree->root);
    free(tree);
}

/**
 * Adds a new node with the given data to the tree.
 * @param tree A pointer to the tree.
 * @param data The data to add to the tree.
 */
void add(NeuTree* tree, char data) {
    NeuNode *node = (NeuNode*)malloc(sizeof(NeuNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    if(tree->root == NULL) {
        tree->root = node;
    } else {
        NeuNode *cur = tree->root;
        NeuNode *par = NULL;
        while(cur) {
            par = cur;
            if(data < cur->data) {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }
        if(data < par->data) {
            par->left = node;
        } else {
            par->right = node;
        }
    }
}

/**
 * Performs a breadth-first traversal of the tree.
 * @param tree A pointer to the tree.
 * @param visit A function pointer to apply to each node's data.
 */
void breadth_first_traversal(NeuTree* tree, void (*visit)(char)) {
    if(!tree) {
        return;
    }
    
    NeuNode *queue[tree->size]; 
    int f = 0;
    int r = 0;

    queue[r++] = tree->root;
    while(f < r) {
        NeuNode *cur = queue[f++];
        visit(cur->data);
        if(cur->left != NULL) {
            queue[r++] =cur->left;
        } else if(cur->right != NULL){
            queue[r++] = cur->right;
        }
    }
}

void _preOrder(NeuNode * node, void (*visit)(char)) {
    if(!node) {
        return;
    }
    visit(node->data);
    _preOrder(node->left, visit);
    _preOrder(node->right, visit);
}

void _inOrder(NeuNode * node, void (*visit)(char)) {
    if(!node) {
        return;
    }
    _inOrder(node->left, visit);
    visit(node->data);
    _inOrder(node->right, visit);
}

void _postOrder(NeuNode * node, void (*visit)(char)) {
    if(!node) {
        return;
    }
    _postOrder(node->left, visit);
    _postOrder(node->right, visit);
    visit(node);
}

/**
 * Performs a depth-first traversal of the tree.
 * @param tree A pointer to the tree.
 * @param type The type of depth-first traversal (PRE_ORDER, IN_ORDER, POST_ORDER).
 * @param visit A function pointer to apply to each node's data.
 */
void depth_first_traversal(NeuTree* tree, enum TraversalType type, void (*visit)(char)) {
    if(!tree) {
        return;
    }
}