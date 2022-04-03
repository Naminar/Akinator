
#define  TX_USE_SPEAK

#include "../include/TXLib.h"
#include "../include/akinator.h"
#include "../include/dump.h"
#include "../include/database.h"
#include "../Stack/stack.h"
#include "../include/tree.h"

/*
Node* add_node(DATA value, Node* node)
{
    if (!node)
    {
       node = (Node*) calloc(1, sizeof(Node));

       strcpy(node->cell, value);
       node->left_son   = nullptr;
       node->right_son  = nullptr;
    }
    else if (value > node->cell)
    {
        node->right_son = add_node(value, node->right_son);

        node->right_son->mother = node;

    }
    else if (value <= node->cell)
    {
        node->left_son = add_node(value, node->left_son);

        node->left_son->mother = node;
    }

    return node;

}*/

void get_screen_info(Node* node, size_t indent) //print_pre
{
    if (!node)
		return;

    printf("%*s", indent, "{");

    indent += INDENT_STEP;

    printf(" " CELL_FMT " ", node->cell);

    if (node->left_son || node->right_son)
    {
        printf("\n");

        get_screen_info(node->left_son, indent);

        if (node->right_son)
            printf("\n");

        get_screen_info(node->right_son, indent);

        printf("\n%*s", indent -= INDENT_STEP, "}");
    }
    else
    {
        /*get_screen_info(node->left_son, indent);    commented

        if (node->right_son)
            printf("\n");

        get_screen_info(node->right_son, indent);

        //printf("\n%*s", indent -= 4, "}");*/

        printf("}");
    }
}

void print_in(Node* node)
{
    if (!node)
        return;

    print_in(node->left_son);

    printf(CELL_FMT "  ", node->cell);

    print_in(node->right_son);
}

void print_post(Node* node)
{
    if (!node)
        return;

    print_post(node->left_son);

    print_post(node->right_son);

    printf(CELL_FMT "  ", node->cell);

}

Node* tree_construct(void)
{
    Node* root = (Node*) calloc(1, sizeof(Node));

    assert (root);

    root->mother    =   nullptr;
    root->left_son  =   nullptr;
    root->right_son =   nullptr;
    root->cell      =   nullptr;//(char*) calloc(WORLD_LENGTH, sizeof (char));

    return root;
}

void tree_destruct(Node* node)
{
    if (node)
    {
        tree_destruct(node->left_son);

        tree_destruct(node->right_son);

        free(node->cell);

        free(node);
    }
}
