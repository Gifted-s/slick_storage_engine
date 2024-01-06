// C program for Red-Black Tree insertion
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef WISCKEY_MEMTABLE_RECORD_H
#define WISCKEY_MEMTABLE_RECORD_H

// A Red-Black tree node structure
struct RBTNode
{
    char *key;
    size_t key_len;
    int64_t value_loc;
    char color;
    struct RBTNode *left, *right, *parent;
};

// Left Rotation
void leftRotate(struct RBTNode **root, struct RBTNode *x);

// Right Rotation (Similar to LeftRotate)
void rightRotate(struct RBTNode **root, struct RBTNode *y);

// Utility function to fixup the Red-Black tree after standard BST insertion
void insertFixUp(struct RBTNode **root, struct RBTNode *z);

// Utility function to insert newly node in RedBlack tree
void insert(struct RBTNode **root, char *key, size_t key_len, int64_t value_loc);

// A utility function to traverse Red-Black tree in inorder fashion
void inorder(struct RBTNode *root, struct RBTNode* sorted_list);

// Utility function to find a key in the RBT
struct RBTNode* getKey(struct RBTNode *root, char *key,  size_t key_len);

// return a sorted list of the nodes in the tree
struct RBTNode* get_nodes_sorted(struct RBTNode *root, uint64_t size);

#endif