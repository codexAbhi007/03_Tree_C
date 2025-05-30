//Finding height of a binary tree (Recursive and Iterative using queue)

#include <stdio.h>
#include <stdlib.h>

//Tree Node 
struct Node{
    int data;
    struct Node* left;
    struct Node* right;
};

//Queue Node
struct QueueNode{
    struct Node* treeNode;
    struct QueueNode* next;
};

//Global pointers for queue
struct QueueNode* front = NULL;
struct QueueNode* rear = NULL;

//Function prototypes
struct Node* createNode(int);
struct Node* buildTree();
void enqueue(struct Node*);
struct Node* dequeue();
int isEmpty();
int heightRecursive(struct Node*);
int heightIterative(struct Node*);

//main
int main(){
    struct Node* root = buildTree();

    int h1 = heightRecursive(root);
    printf("\nHeight (Recursive): %d\n",h1);

    int h2 = heightIterative(root);
    printf("\nHeight (Iterative): %d\n",h2);

    return 0;
}

//Create tree node
struct Node* createNode(int value){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

//Build binary tree
struct Node* buildTree(){
    int value;
    printf("Enter node value (0 for no node): ");
    scanf("%d",&value);

    if(value == 0) return NULL;

    struct Node* newNode = createNode(value);
    printf("\nEnter Left child of %d:\n",value);
    newNode->left = buildTree();

    printf("\nEnter Right child of %d:\n",value);
    newNode->right = buildTree();

    return newNode;
}

//Enqueue Operation
void enqueue(struct Node* node){
    struct QueueNode* temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    temp->treeNode = node;
    temp->next = NULL;

    if (rear == NULL){
        front = rear = temp;
    }else{
        rear -> next = temp;
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

//Recursive approach to calculate height
int heightRecursive(struct Node* root){
    if (root == NULL) return -1; //base case 
    int leftHeight = heightRecursive(root->left);
    int rightHeight = heightRecursive(root->right);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}


//Iterative based approach to calculate height
int heightIterative(struct Node* root){
    if(root == NULL) return -1;

    enqueue(root);
    int height = -1;

    while(!isEmpty()){
        int levelSize = 0;

        //count how many nodes at current level
        struct QueueNode* temp = front;
        while(temp){
            levelSize++;
            temp = temp->next;
        }

        //Process all nodes at current level
        int i;
        for(i=0;i<levelSize;++i){
            struct Node* current = dequeue();
            if(current->left) enqueue(current->left);
            if(current->right) enqueue(current->right);
        }

        ++height;
    }

    return height;
}