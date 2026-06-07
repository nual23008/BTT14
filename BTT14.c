#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

int Get_Height(Node* current_node) {
    if(current_node == NULL) return 0;

    int left_height = Get_Height(current_node->left);
    int right_height = Get_Height(current_node->right);

    return 1 + ((left_height > right_height) ? left_height : right_height);
}

int Caculate_Balance_Factor(Tree* t) {
    int count_left = Get_Height(t->root->left);
    int count_right = Get_Height(t->root->right);

    return (count_left - count_right);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    Tree t;
    t.root = NULL;
    int a[] = {32, 51, 27, 83, 96, 11, 45, 75, 66};
    for(int i = 0; i < 9; i++){
        Insert(&t, a[i]);
    }

    int check = Caculate_Balance_Factor(&t);
    printf("%d", check);
    return 0;
}