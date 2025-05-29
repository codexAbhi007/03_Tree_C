//Implementation and Traversal of BST (Binary Search Tree)

#include <stdio.h>
#include <stdlib.h>

//Node structure
struct Node{
    int data;
    struct Node* left;
    struct Node* right;

};

//Function prototypes
struct Node* createNode(int value);
struct Node* insert(struct Node* root,int value);
void inorder(struct Node* root);

//Main

int main(){
    struct Node* root = NULL;
    int n,value;
    printf("Enter number of nodes: ");
    scanf("%d",&n);

    
    int i;
    for(i = 0;i<n;++i){
        printf("Enter: ");
        scanf("%d",&value);
        root = insert(root,value);
    }

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");
    return 0;

}

//Create a new node
struct Node* createNode(int value){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//Insert function
struct Node* insert(struct Node* root,int value){
    if(root == NULL){
        return createNode(value);
    }

    if(value < root->data){
        root->left = insert(root->left,value);
    }else if(value > root->data){
        root->right = insert(root->right,value);
    }else{
        printf("Duplicate value %d ignored\n",value);

    }
    return root;
}

//Inorder Traversal
void inorder(struct Node* root){
    if(root == NULL) return;
    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}