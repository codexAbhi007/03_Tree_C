//Traversing A binary tree (Preorder,Inorder,Postorder)

#include <stdio.h>
#include <stdlib.h>

//Structure
struct Node{
    int data;
    struct Node* left;
    struct Node* right;
};


//Function prototypes
struct Node* createNode(int value);
struct Node* buildTree();
void preorder(struct Node* root);
void inorder(struct Node* root);
void postorder(struct Node* root);

//Main
int main(){
    struct Node* root = buildTree();

    printf("\nPreorder Traversal: ");
    preorder(root);

    printf("\nInorder Traversal: ");
    inorder(root);

    printf("\nPostorder Traversal: ");
    postorder(root);

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
    printf("Enter node value (0 for no node): ");
    scanf("%d",&value);

    if(value == 0) return NULL; //base condition

    struct Node* new = createNode(value);

    printf("Enter left Child of %d:\n",value);
    new->left = buildTree();

    printf("Enter right Child of %d:\n",value);
    new->right = buildTree();

    return new;

}

//Preorder: Root -> left -> right
void preorder(struct Node* root){
    if(root == NULL) return;
    printf("%d ",root->data);
    preorder(root->left);
    preorder(root->right);
}

//Inorder: left -> Root -> Right
void inorder(struct Node* root){
    if(root == NULL) return;
    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}

//Postorder: Left -> Right -> Root
void postorder(struct Node* root){
    if(root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ",root->data);
}