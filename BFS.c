#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_QUEUE_SIZE 100

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};
struct Queue {
    int front, rear, size;
    struct Node* array[MAX_QUEUE_SIZE];
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
    queue->front = queue->size = 0;
    queue->rear = MAX_QUEUE_SIZE - 1;
    return queue;
}
bool isEmpty(struct Queue* queue) {
    return queue->size == 0;
}
bool isFull(struct Queue* queue) {
    return queue->size == MAX_QUEUE_SIZE;
}

void enqueue(struct Queue* queue, struct Node* item) {
    if (isFull(queue)) {
        return;
    }
    queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
    printf("%d enqueued to queue\n", item->data);
}

struct Node* dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        return NULL;
    }
    struct Node* item = queue->array[queue->front];
    queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
    queue->size = queue->size - 1;
    return item;
}

void bfs(struct Node* root) {
    if (root == NULL) {
        return;
    }
    struct Queue* queue = createQueue();
    enqueue(queue, root);
    while (!isEmpty(queue)) {
        struct Node* curr = dequeue(queue);
        printf("%d \n", curr->data);
        if (curr->left != NULL) {
            enqueue(queue, curr->left);
        }
        if (curr->right != NULL) {
            enqueue(queue, curr->right);
        }
    }
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

    bfs(root);
    return 0;
}