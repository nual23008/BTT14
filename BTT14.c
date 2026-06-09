#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <math.h>

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

int Calculate_Balance_Factor(Node* t) {
    int count_left = Get_Height(t->left);
    int count_right = Get_Height(t->right);

    return (count_left - count_right);
}

Node* Right_Rotate(Node* y) {
    Node* x = y->left;
    Node* n = x->right;

    x->right = y;
    y->left = n;

    return x;
}

Node* Left_Rotate(Node* y) {
    Node* x = y->right;
    Node* n = x->left;

    x->left = y;
    y->right = n;

    return x;
}

Node* Balance_Tree(Node** current_node) {
    int balance = Calculate_Balance_Factor(*current_node);

    if(abs(balance) <= 1) {
        return (*current_node);
    }
    else if(balance < -1) {
        int right_balance = Calculate_Balance_Factor((*current_node)->right);

        if(right_balance <= 0) {
            return Left_Rotate((*current_node));
        }
        else {
            (*current_node)->right = Right_Rotate((*current_node)->right);
            return Left_Rotate((*current_node));
            }
    }
    else if(balance > 1) {
        int left_balance = Calculate_Balance_Factor((*current_node)->left);

        if(left_balance > 0) {
            return Right_Rotate((*current_node));
        }
        else {
            (*current_node)->left = Left_Rotate((*current_node)->left);
            return Right_Rotate((*current_node));
        }
    }

    return (*current_node);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    Tree t;
    t.root = NULL;
    int a[] = {32, 51, 27, 83, 96, 11, 45, 75, 66};
    for(int i = 0; i < 9; i++){
        Insert(&t, a[i]);
    }

    int check = Calculate_Balance_Factor(t.root);
    printf("%d", check);
    
    return 0;
}