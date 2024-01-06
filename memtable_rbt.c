// C program for Red-Black Tree insertion
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "includes/memtable_rbt.h"
// Left Rotation
void leftRotate(struct RBTNode **root, struct RBTNode *x)
{
    if (!x || !x->right)
        return;
    // y stored pointer of right child of x
    struct RBTNode *y = x->right;

    // store y's left subtree's pointer as x's right child
    x->right = y->left;

    // update parent pointer of x's right
    if (x->right != NULL)
        x->right->parent = x;

    // update y's parent pointer
    y->parent = x->parent;

    // if x's parent is null make y as root of tree
    if (x->parent == NULL)
        (*root) = y;

    // store y at the place of x
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    // make x as left child of y
    y->left = x;

    // update parent pointer of x
    x->parent = y;
}

// Right Rotation (Similar to LeftRotate)
void rightRotate(struct RBTNode **root, struct RBTNode *y)
{
    if (!y || !y->left)
        return;
    struct RBTNode *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if (x->parent == NULL)
        (*root) = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

// Utility function to fixup the Red-Black tree after standard BST insertion
void insertFixUp(struct RBTNode **root, struct RBTNode *z)
{
    // iterate until z is not the root and z's parent color is red
    while (z != *root && z != (*root)->left && z != (*root)->right && z->parent->color == 'R')
    {
        struct RBTNode *y;

        // Find uncle and store uncle in y
        if (z->parent && z->parent->parent && z->parent == z->parent->parent->left)
            y = z->parent->parent->right;
        else
            y = z->parent->parent->left;

        // If uncle is RED, do following
        // (i)  Change color of parent and uncle as BLACK
        // (ii) Change color of grandparent as RED
        // (iii) Move z to grandparent
        if (!y)
            z = z->parent->parent;
        else if (y->color == 'R')
        {
            y->color = 'B';
            z->parent->color = 'B';
            z->parent->parent->color = 'R';
            z = z->parent->parent;
        }

        // Uncle is BLACK, there are four cases (LL, LR, RL and RR)
        else
        {
            // Left-Left (LL) case, do following
            // (i)  Swap color of parent and grandparent
            // (ii) Right Rotate Grandparent
            if (z->parent == z->parent->parent->left &&
                z == z->parent->left)
            {
                char ch = z->parent->color;
                z->parent->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                rightRotate(root, z->parent->parent);
            }

            // Left-Right (LR) case, do following
            // (i)  Swap color of current RBTNode  and grandparent
            // (ii) Left Rotate Parent
            // (iii) Right Rotate Grand Parent
            if (z->parent && z->parent->parent && z->parent == z->parent->parent->left &&
                z == z->parent->right)
            {
                char ch = z->color;
                z->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                leftRotate(root, z->parent);
                rightRotate(root, z->parent->parent);
            }

            // Right-Right (RR) case, do following
            // (i)  Swap color of parent and grandparent
            // (ii) Left Rotate Grandparent
            if (z->parent && z->parent->parent &&
                z->parent == z->parent->parent->right &&
                z == z->parent->right)
            {
                char ch = z->parent->color;
                z->parent->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                leftRotate(root, z->parent->parent);
            }

            // Right-Left (RL) case, do following
            // (i)  Swap color of current RBTNode  and grandparent
            // (ii) Right Rotate Parent
            // (iii) Left Rotate Grand Parent
            if (z->parent && z->parent->parent && z->parent == z->parent->parent->right &&
                z == z->parent->left)
            {
                char ch = z->color;
                z->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                rightRotate(root, z->parent);
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = 'B'; // keep root always black
}
int s;
// Utility function to insert newly RBTNode in RedBlack tree
void insert(struct RBTNode **root, char *key, size_t key_len, int64_t value_loc)
{
    // Allocate memory for new RBTNode
    struct RBTNode *z = (struct RBTNode *)malloc(sizeof(struct RBTNode));
    z->key = malloc(sizeof(char) * key_len);
    z->key = key;
    z->value_loc = value_loc;
    z->key_len = key_len;
    z->left = z->right = z->parent = NULL;

    // if root is null make z as root
    if (*root == NULL)
    {
        z->color = 'B';
        (*root) = z;
    }
    else
    {
        struct RBTNode *y = NULL;
        struct RBTNode *x = (*root);

        // Follow standard BST insert steps to first insert the RBTNode
        while (x != NULL)
        {
            y = x;
            // handle duplicate keys later
            if (strncmp(z->key, x->key, key_len) < 0)
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;
        if (strncmp(z->key, y->key, key_len) > 0)
            y->right = z;
        else
            y->left = z;
        z->color = 'R';

        // call insertFixUp to fix reb-black tree's property if it
        // is voilated due to insertion.
        insertFixUp(root, z);
    }
}

struct RBTNode *getKey(struct RBTNode *root, char *key, size_t key_len)
{
    if (root == NULL)
    {
        return NULL;
    }

    int cmp = strncmp(key, root->key, key_len);

    if (cmp == 0)
    {
        return root;
    }
    else if (cmp < 0)
    {
        return getKey(root->left, key, key_len);
    }
    else
    {
        return getKey(root->right, key, key_len);
    }
}
int insertion_point = 0;
// A utility function to traverse Red-Black tree in inorder fashion
void inorder(struct RBTNode *root, struct RBTNode *sorted_list)
{

    if (root == NULL)
        return;

    inorder(root->left, sorted_list);
    sorted_list[insertion_point].key = malloc(root->key_len);
    memcpy(sorted_list[insertion_point].key, root->key, root->key_len);
    sorted_list[insertion_point].value_loc = root->value_loc;
    sorted_list[insertion_point].key_len = root->key_len;
    insertion_point++;
    // printf("POS %d \n", insertion_point);
    //  printf("key: %s, value_offset: %lld  index \n", root->key, root->value_loc);
    inorder(root->right, sorted_list);
}

struct RBTNode *get_nodes_sorted(struct RBTNode *root, uint64_t size)
{
    struct RBTNode *nodes = (struct RBTNode *)malloc(sizeof(struct RBTNode) * size);
    inorder(root, nodes);
    return nodes;
}

void free_tree(struct RBTNode *root){
if (root == NULL) {
        return;
    }
    
    // Free nodes in post-order: left-right-root
    free_tree(root->left);
    free_tree(root->right);
    
    // Free the current node
    free(root);
  
}

#include <time.h>

#define NB_ELEMS 4

/* Drier program to test above function*/
// int main()
// {

//     struct MultiType
//     {
//         char *key;
//         size_t key_len;
//         int64_t value_loc;
//     };

// #define SIZE 6

//     struct MultiType array[SIZE];

//     // Assign values to the elements of the array
//     array[0].key = "sunkanmi";
//     array[0].key_len = strlen("sunkanmi");
//     array[0].value_loc = 15;

//     array[1].key = "sankanmi23";
//     array[1].key_len = strlen("sunkanmi23");
//     array[1].value_loc = 14;

//     array[2].key = "sunkanmi43";
//     array[2].key_len = strlen("sunkanmi43");
//     array[2].value_loc = 17;

//     array[5].key = "aaaaaaaaa";
//     array[5].key_len = strlen("aaaaaaaa");
//     array[5].value_loc = 17;

//     array[3].key = "zbunkanmi32";
//     array[3].key_len = strlen("zbunkanmi32");
//     array[3].value_loc = 43;

//     array[4].key = "zunkanmi32";
//     array[4].key_len = strlen("zunkanmi32");
//     array[4].value_loc = 43;

//     srandom(time(NULL));
//     struct RBTNode *root = NULL;

//     // start clock
//     clock_t t0 = clock();

//     for (int i = 0; i < SIZE; i++)
//     {
//         insert(&root, array[i].key, array[i].key_len, array[i].value_loc);
//         printf("\n");
//     }

//     // end clock
//     clock_t t1 = clock();
//     printf("inorder Traversal Is :\n");
//     //inorder(root);
//     printf("\n");
//     // calculate time taken
//     float time_taken = (float)(t1 - t0) / CLOCKS_PER_SEC * 1000;
//     printf("insertion took %fms -> %fus/elem\n",
//            time_taken,
//            time_taken / NB_ELEMS * 1000);

//     get_nodes_sorted(root, 6);

//     // struct RBTNode *node = getKey(root, "zunkanmi32", strlen("zunkanmi32"));

//     // printf("===================SEARCHED KEY RESULT========================= \n");
//     // if (node == NULL)
//     // {
//     //     printf("======================NOT FOUND============");
//     // }
//     // else
//     // {
//     //     printf("Key: %s, Value: %lld \n", node->key, node->value_loc);
//     // }
//     return 0;
// }