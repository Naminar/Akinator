
#ifndef TREE_

#define TREE_

#include <stdlib.h>
#include <cstdio>
#include <assert.h>
#include <string.h>
#include "config.h"

#define CELL_FMT "%s"

typedef struct Node{

    char* cell;

    Node* mother;

    Node* left_son;
    Node* right_son;

} Node;

//===============================================

Node* tree_construct    (void);
void tree_destruct      (Node* m_node);
Node* add_node          (int val, Node* m_node);
void get_screen_info    (Node* tree, size_t indent = 0);
void print_in           (Node* tree);
void print_post         (Node* tree);

//===============================================

#endif // TREE_
