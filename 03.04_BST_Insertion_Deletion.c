//Insertion and deletion Operation in BST (Binary Search Tree)

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
struct Node* deleteNode(struct Node* root,int value);
struct Node* findMin(struct Node* root);
void inorder(struct Node* root);

int main(){
    struct Node* root = NULL;
    int n, value;

    printf("Enter number of nodes: ");
    scanf("%d",&n);

    int i;
    for(i = 0;i< n;++i){
        printf("Enter: ");
        scanf("%d",&value);
        root = insert(root,value);
    }

    printf("Inorder Traversal after insertion: ");
    inorder(root);
    printf("\n");

    printf("Enter value to be deleted: ");
    scanf("%d",&value);
    root = deleteNode(root,value);

    printf("Inorder Traversal after deletion: ");
    inorder(root);
    printf("\n");

    return 0;
}

//Function definitions

//Create Node
struct Node* createNode(int value){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//Insertion function
struct Node* insert(struct Node* root,int value){
    if(root == NULL)
        return createNode(value); //If no node present
    
    if(value < root->data)
        root->left = insert(root->left, value);
    else if(value > root->data)
        root->right = insert(root->right,value);
    else 
        printf("Duplicate value found %d ignored\n",value);
    
    return root;
}

//Function to find node with smallest value in a subtree
struct Node* findMin(struct Node* root){
    while(root->left != NULL)
        root = root->left;
    return root;
}

//Funtion to Delete a node from BST

struct Node* deleteNode(struct Node* root, int value){
    if(root == NULL){
        printf("Element not found!\n");
        return NULL;
    }

    if(value < root->data)
        root->left = deleteNode(root->left, value); //Search in left subtree
    else if(value > root->data)
        root->right = deleteNode(root->right, value); //Search in right subtree
    else{
        //case 1: Node with 0 children (leaf node)
        if(root->left == NULL && root->right == NULL){
            free(root);
            return NULL;
        }
        //case 2: Node with 1 child and its right child
        else if(root->left == NULL){
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        //case 3: Node with 1 child and its left child
        else if(root->right == NULL){
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        //case 4: Node with two children
        else{
            //First find inorder successor ( smallest node in right subtree )
            struct Node* minRight = findMin(root->right);
            root->data = minRight->data; //Replace data with inorder successor
            //delete inorder successor
            root->right = deleteNode(root->right,minRight->data);
        }
    }

    return root;
}

//Inorder traversal (left -> root-> right)
void inorder(struct Node* root){
    if(root == NULL) return;
    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}
