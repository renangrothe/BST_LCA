#include "btree.h"
#include <stdlib.h>

typedef struct node {

    struct node* left;
    struct node* right;
    int key;

} node;

node* buildtree (int key) {

    node* root = (node *) malloc (sizeof (node));

    if (!root) 
        return 0;

    root->key = key;
    root->right = NULL;
    root->left = NULL;

    return root;
}

void deletetree (node* root) {

    if (!root)
        return;

    removeleaf (root->left);
    removeleaf (root->right);

    free (root);

    return;
}

int insertleaf (node* root, int key) { //look at the new inserted element's father as a sub-tree

    if (!root)  //invalid root address
        return 0;

    if (root->key > key) {
        
        if (!root->left) { //recursion found the insertion spot
            
            root->left = (node *) malloc (sizeof (node));
            
            if (!root->left)
                return 0; //memory allocation failed 

            root->left->key = key;
            root->left->left = NULL;
            root->left->right = NULL;
            return 1;

        }   else  //if there's already a left subtree, try with the left element subtree
                return insertleaf (root->left, key);
    
    } else if (root->key < key) { //insertion found the insertion spot

        if (!root->right) {

            root->right = (node *) malloc (sizeof (node));
        
        if (!root->right)
                return 0; //memory allocation failed 

            root->right->key = key;
            root->right->left = NULL;
            root->right->right = NULL;
            return 1;

        }   else  //if there's already a right subtree, try the insertion with the right element subtree
                return insertleaf (root->right, key);

    }

    return 0; //insertion failed
}

int removesubtree (node* root) {

    if (!root) 
        return NULL;
    
    removesubtree (root->left);
    removesubtree (root->right);

    free(root);

    return 1;
}

node* searchelement (node* root, int key) {

    if (!root || root->key == key) //base case: returns NULL if subtree is empty, or returns the address of the found key.
        return root;

    if (key < root->key)
        return searchelement (root->left, key);

    return searchelement (root->right, key);
}

node* findlowercommonancestor (node* root, int keyA, int keyB) {

    if (!root) //case base: the root is NULL (invalid or end of recursion), or both elements are not in the subtree.
        return NULL;

    if (keyA < root->key && keyB < root->key)
        return findlowercommonancestor (root->left, keyA, keyB);

    if (keyA > root->key && keyB > root->key)
        return findlowercommonancestor (root->right, keyA, keyB);

    return root; 
}