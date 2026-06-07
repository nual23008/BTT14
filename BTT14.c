#include <stdio.h>
#include <stdlib.h>
#include  <stdbool.h>
#include <string.h>
#include <windows.h>

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
    return n;
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
                Insert_Recursive(&(*current_node)->left, data);
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
    Insert_Recursive(&(t->root), data);
}

int Count_Height(Node* current_node, int count) {
    if(current_node->left == NULL && current_node->right == NULL) {
        return count;
    }
    else if(current_node->left != NULL && current_node->right == NULL) {
        Count_Height(current_node->left, count + 1);
    }
    else if(current_node->left == NULL && current_node->right != NULL) {
        Count_Height(current_node->right, count + 1);
    }
    else if(current_node->left != NULL && current_node->right != NULL) {
        Count_Height(current_node->left, count + 1);
    }
}

bool Is_Balance(Tree* t) {
    int count_left = Count_Height(t->root->left, 0);
    int count_right = Count_Height(t->root->right, 0);

    return ((count_left - count_right) > 1) ? 1 : 0;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    Tree t;
    t.root = NULL;
    int a[] = {32, 51, 27, 83, 96, 11, 45, 75, 66};
    for(int i = 0; i < 9; i++){
        Insert(&t, a[i]);
    }

    int check = Is_Balance(&t);
    printf("%d", check);
    return 0;
}