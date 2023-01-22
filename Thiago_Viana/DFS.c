#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void dfs(struct Node* root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->data);
    dfs(root->left);
    dfs(root->right);
}

int main() {
    /*
            1
          /   \
         2     3
        / \
       4   5  
    */
    struct Node* root = newNode(1);
    
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    
    printf("Busca em profundidade: ");
    dfs(root);
    printf("\n");
    
    return 0;
}