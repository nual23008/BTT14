#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
}Node;

Node* Create_Node(int data) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = data;
    n->left = NULL;
    n->right = NULL;
}

typedef struct {
    Node* root;
}Tree;

void Insert_Recursive(Node** current_node, int data) {
    if((*current_node) == NULL) {
        (*current_node) = Create_Node(data);
        return;
    }
    else {
        if(data < (*current_node)->data) {
            if((*current_node)->left == NULL) {
                (*current_node)->left = Create_Node(data);
                return;
            }
            else {
                Insert_Recursive(&(*current_node)->data, data);
            }
        }
        
        else {
            if((*current_node)->right == NULL) {
                (*current_node)->right = Create_Node(data);
                return;
            }
            else {
                Insert_Recursive(&(*current_node)->right, data);
            }
        }
    }
}

void Insert(Tree* t, int data) {
    if(t->root == NULL) return;
    Insert_Recursive(&(t->root), data);
}

