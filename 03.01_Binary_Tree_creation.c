//Creating Binary Tree

#include <stdio.h>
#include <stdlib.h>

//Node structure
struct Node{
    int data;
    struct Node* left;
    struct Node* right;
};

//Function Prototypes
struct Node* createNode(int value);
struct Node* buildTree();

//Main
int main(){
    struct Node* root = buildTree();

    printf("Tree created successfully");

    return 0;
}

//Function definitions

struct Node* createNode(int value){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* buildTree(){
    int value;
    printf("Enter value (0 for no node): ");
    scanf("%d",&value);

    //base condition
    if(value == 0) return NULL;

    struct Node* new = createNode(value);

    printf("Enter left child of %d\n",value);
    new->left = buildTree(); //Recursive call

    printf("Enter right child of %d\n",value);
    new->right = buildTree(); //Recursive call

    return new;
}