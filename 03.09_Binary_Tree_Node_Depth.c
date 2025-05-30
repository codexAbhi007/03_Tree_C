//Finding depth of a node in Binary Tree

#include <stdio.h>
#include <stdlib.h>

//Tree Node Structure
struct Node{
    int data;
    struct Node* left;
    struct Node* right;
};

//Queue Node structure (for iterative approach)
struct QueueNode{
    struct Node* treeNode;
    int level; // to store depth level
    struct QueueNode* next;
};

struct QueueNode* front = NULL;
struct QueueNode* rear = NULL;

//Function prototypes
struct Node* createNode(int);
struct Node* buildTree();
int findDepthRecursive(struct Node*,int);
int findDepthIterative(struct Node*, int);
void enqueue(struct Node*, int);
struct QueueNode* dequeue();
int isEmpty();

//Main
int main(){
    struct Node* root = buildTree();

    int target;
    printf("\nEnter value to find depth: ");
    scanf("%d",&target);

    int depthRec = findDepthRecursive(root,target);
    printf("\nRecursive Depth: %d\n",depthRec);

    int depthIter = findDepthIterative(root, target);
    printf("Iterative depth: %d\n",depthIter);

    return 0;
}

//Create tree node
struct Node* createNode(int value){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
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

//Recursive approach to find depth
int findDepthRecursive(struct Node* root, int x){
    if(root == NULL) return -1;

    if(root->data == x)
        return 0;
    
    int leftDepth = findDepthRecursive(root->left, x);
    if(leftDepth >= 0)
        return leftDepth + 1;

    int rightDepth = findDepthRecursive(root->right,x);
    if(rightDepth >= 0)
        return rightDepth + 1;

    return -1; //If node not found
}

//Queue operations for iterative approach
void enqueue(struct Node* node,int level){
    struct QueueNode* temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    temp->treeNode = node;
    temp->level = level;
    temp->next = NULL;

    if(rear == NULL){
        front = rear = temp;
    }else{
        rear->next = temp;
        rear = temp;
    }
}

struct QueueNode* dequeue(){
    if(front == NULL) return NULL;
    struct QueueNode* temp = front;
    front = front->next;
    if(front == NULL) rear = NULL;
    return temp;
}

int isEmpty(){
    return front == NULL;
}

//Iterative approach
int findDepthIterative(struct Node* root,int x){
    if(root == NULL) return -1;

    enqueue(root,0);

    while(!isEmpty()){
        struct QueueNode* temp = dequeue();
        struct Node* curr = temp->treeNode;
        int currLevel = temp->level;
        free(temp);

        if(curr->data == x) return currLevel;

        if(curr->left) enqueue(curr->left, currLevel + 1);
        if(curr->right) enqueue(curr->right, currLevel + 1);
    }

    return -1; // If node not found
}