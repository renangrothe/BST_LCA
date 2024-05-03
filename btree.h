#ifndef BTREE_H
#define BTREE_H

struct node;

node* buildtree (int key);

void deletetree (node* root);

int insertleaf (node* root, int key);

int removesubtree (node* root);

node* searchelement (node* root, int key);

node* findlowercommonancestor (node* root, int keyA, int keyB);


#endif