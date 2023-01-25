#include "graph.c"
#include <limits.h>

typedef struct tree_node
{
    int value;
    int key;
    int left_cost;
    int right_cost;
    struct tree_node *left;
    struct tree_node *right;
} tree_node;

tree_node *create_tree_node(int value, int key)
{
    tree_node *new_tree_node = (tree_node *)malloc(sizeof(tree_node));
    new_tree_node->value = value;
    new_tree_node->key = key;
    new_tree_node->left_cost = INT_MAX;
    new_tree_node->right_cost = INT_MAX;
    new_tree_node->left = NULL;
    new_tree_node->right = NULL;
    return new_tree_node;
}

void insert_left(tree_node **node, int left_cost, int left_id, int left_key)
{
    (*node)->left_cost = left_cost;
    tree_node *new_tree_node = create_tree_node(left_id, left_key);
    (*node)->left = new_tree_node;
}

void insert_right(tree_node **node, int right_cost, int right_id, int right_key)
{
    (*node)->left_cost = right_cost;
    tree_node *new_tree_node = create_tree_node(right_id, right_key);
    (*node)->left = new_tree_node;
}

tree_node *search_node(tree_node *root, int key, tree_node **parent)
{
    *parent = NULL;
    if (root == NULL)
    {
        return NULL;
    }
    else
    {
        tree_node *current = root;
        while (current != NULL)
        {
            if (current->key == key)
            {
                return current;
            }
            else
            {
                *parent = current;
                if (key > current->key)
                {
                    current = current->right;
                }
                else
                {
                    current = current->left;
                }
            }
        }
    }
    return NULL;
}

void destroy_tree_aux(tree_node *root)
{
    if (root != NULL)
    {
        destroy_tree_aux(root->left);
        destroy_tree_aux(root->right);
        root->left = NULL;
        root->right = NULL;
        free(root);
    }
}

void destroy_tree(tree_node **root, tree_node *root_parent)
{
    destroy_tree_aux(*root);
    tree_node *parent_node;
    search_node(root_parent, (*root)->key, &parent_node);
    if (parent_node != NULL)
    {
        if (parent_node->left == *root)
            parent_node->left = NULL;
        else
            parent_node->right = NULL;
    }
    *root = NULL;
}