//Finding minimum and maximum element in a BST (Binary Search Tree) using iterative and recursive approach

#include <stdio.h>
#include <stdlib.h>

//Node Structure
struct Node{
    int data;
    struct Node* left;
    struct Node* right;
};

//Function prototypes
struct Node* createNode(int value);
struct Node* insert(struct Node* root,int value);
int findMinRecur(struct Node* root);
int findMaxRecur(struct Node* root);
int findMinIter(struct Node* root);
int findMaxIter(struct Node* root);

//main
int main(){
    struct Node* root = NULL;
    int n,val;

    printf("Enter number of nodes: ");
    scanf("%d",&n);

    int i;
    for(i=0;i<n;++i){
        printf("Enter: ");
        scanf("%d",&val);
        root = insert(root,val);
    }

    printf("\nRecursive Approach->\n");
    printf("Min: %d Max: %d\n",findMinRecur(root),findMaxRecur(root));

    printf("\nIterative Approach->\n");
    printf("Min: %d Max: %d\n",findMinIter(root),findMaxIter(root));

    return 0;
}

//create node function
struct Node* createNode(int value){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//Insert function
struct Node* insert(struct Node* root,int value){
    if(root == NULL) return createNode(value);

    if(value < root->data)
        root->left = insert(root->left,value);
    else if(value > root->data)
        root->right = insert(root->right,value);

    return root;
}

//h = height of the tree
//Recursive: min , Time: O(h), Space: O(h) 
int findMinRecur(struct Node* root){
    if(root->left == NULL) return root->data;
    return findMinRecur(root->left);
}

//Recursive: max, Time: O(h), Space: O(h)
int findMaxRecur(struct Node* root){
    if(root->right == NULL) return root->data;
    return findMaxRecur(root->right);
}

//Iterative: min, Time: O(h), Space: O(1)
int findMinIter(struct Node* root){
    while(root->left != NULL) root = root->left;
    return root->data;
}

//Iterative: max, Time: O(h), Space: O(1)
int findMaxIter(struct Node* root){
    while(root->right != NULL) root = root->right;
    return root->data;
}