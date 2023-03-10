#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
#define bool int

typedef struct node 
{
    int source;
    int destiny;
    int weight;
    struct node *next;
} node;

node *create_node(int source, int destiny, int weight)
{
    node *new = (node *)malloc(sizeof(node));
    new->source = source;
    new->destiny = destiny;
    new->weight = weight;
    new->next = NULL;
    return new;
}

void insert_node(node **first_node, int source, int destiny, int weight)
{
    if ((*first_node) == NULL)
    {
        (*first_node) = create_node(source, destiny, weight);
        return;
    }
    node *current_node = *(first_node);

    while (current_node->next != NULL)
    {
        current_node = current_node->next;
    }
    current_node->next = create_node(source, destiny, weight);
}

bool delete_node(node **first_node, int destiny)
{
    node *current = *(first_node), *previous;
    previous = current;

    if (current == NULL)
    {
        return false;
    }

    while (current->destiny != destiny)
    {
        previous = current;
        current = current->next;
        if (current == NULL)
        {
            return false;
        }
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

bool is_destiny_on_node_list(node *list, int destiny)
{
    node *current = list;
    while (current != NULL)
    {
        if (current->destiny == destiny)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

void push(node **head, node *new_head)
{
    if (*head == NULL)
    {
        *head = new_head;
    }
    else
    {
        new_head->next = *head;
        *head = new_head;
    }
}

node *pop(node **head)
{
    if (*head != NULL)
    {
        node *old_head = *head;
        *head = (*head)->next;
        old_head->next = NULL;
        return old_head;
    }
    return NULL;
}

int get_total_cost(node **head)
{
    int total = 0;
    while (*head != NULL)
    {
        node *old_head = pop(head);
        total += old_head->weight;
        free(old_head);
    }
    return total;
}