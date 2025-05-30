//Level order traversal of binary tree using queue

#include <stdio.h>
#include <stdlib.h>

//Tree Node structure
struct Node{
    int data;
    struct Node* left;
    struct Node* right;
};

//Queue node structure
struct QueueNode{
    struct Node* treeNode; //pointer to tree node
    struct QueueNode* next;
};

//Global queue poitner
struct QueueNode* front = NULL;
struct QueueNode* rear = NULL;

//Function prototypes
struct Node* createNode(int);
struct Node* buildTree();
void levelOrderTraversal(struct Node*);
void enqueue(struct Node*);
struct Node* dequeue();
int isEmpty();

//main 
int main(){
    struct Node* root = buildTree();
    printf("\nLevel Order Traversal: ");
    levelOrderTraversal(root);
    printf("\n");
    return 0;
}

//Create tree node
struct Node* createNode(int value){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//Build the tree
struct Node* buildTree(){
    int value;
    printf("Enter node value (0 for no node): ");
    scanf("%d",&value);
    if(value == 0) return NULL;

    struct Node* new = createNode(value);
    printf("\nEnter left child of %d:\n",value);
    new->left = buildTree();

    printf("\nEnter right child of %d:\n",value);
    new->right = buildTree();

    return new;
}

//Enqueue operation
void enqueue(struct Node* node){
    struct QueueNode* temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    temp->treeNode = node;
    temp->next = NULL;

    if(rear == NULL){
        front = rear = temp;
    }else{
        rear->next = temp;
        rear = temp;
    }

}

//Dequeue Operation
struct Node* dequeue(){
    if(front == NULL) return NULL;

    struct QueueNode* temp = front;
    struct Node* node = temp->treeNode;
    front = front->next;
    if(front == NULL) rear = NULL;
    free(temp);
    return node;
}

//Check if queue is empty
int isEmpty(){
    return front == NULL;
}

//Level order traversal function
void levelOrderTraversal(struct Node* root){
    if(root == NULL) return;

    enqueue(root);

    while(!isEmpty()){
        struct Node* current = dequeue();
        printf("%d ",current->data);

        if(current->left) enqueue(current->left);
        if(current->right) enqueue(current->right);
    }
}