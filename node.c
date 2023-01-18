#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
#define bool int

typedef struct node
{
    int value;
    struct node *next;
} node;

node *create_node(int value)
{
    node *new = (node *)malloc(sizeof(node));
    new->value = value;
    new->next = NULL;
}

void insert_node(node **first_node, int value)
{
    if ((*first_node) == NULL)
    {
        (*first_node) = create_node(value);
        return;
    }
    node *current_node = *(first_node);

    while (current_node->next != NULL)
    {
        current_node = current_node->next;
    }
    current_node->next = create_node(value);
}

bool delete_node(node **first_node, int value)
{
    node *current = *(first_node), *previous;
    previous = current;
    while (current->value != value && current != NULL)
    {
        previous = current;
        current = current->next;
    }
    if (current == NULL)
    {
        return false;
    }
    if (previous == current)
    {
        *(first_node) = current->next;
        free(current);
        return true;
    }
    previous->next = current->next;
    free(current);
    return true;
}

int get_node_list_size(node *list)
{
    node *current = list;
    int size = 0;

    while (current != NULL)
    {
        size++;
        current = current->next;
    }

    return size;
}