//Implementation of AVL Tree (Insertion - LL,RR,LR,RL rotations)
#include <stdio.h>
#include <stdlib.h>

//Node structure
struct Node{
    int data;
    struct Node* left;
    struct Node* right;
    int height;
};

//Function prototypes
struct Node* createNode(int data);
int max(int a,int b);
int height(struct Node* node);
int getBalance(struct Node* node);
struct Node* rightRotate(struct Node* y);
struct Node* leftRotate(struct Node* x);
struct Node* insert(struct Node* node,int data);
void inOrder(struct Node* root);

//main
int main(){
    struct Node* root = NULL;
    int n,data;

    printf("Enter no of nodes in AVL tree: ");
    scanf("%d",&n);

    int i;
    for(i = 0; i<n;++i){
        printf("Enter: ");
        scanf("%d",&data);
        root = insert(root,data);
    }

    printf("InOrder Traversal: ");
    inOrder(root);
    return 0;
}

//Create new node
struct Node* createNode(int data){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 0;
    return node;
 }

//Get height function
int height(struct Node* node){
    if(node == NULL) return -1;
    return node->height;
}

//Max of two integers function
int max(int a,int b){
    return(a > b) ? a: b;
}

//Get balance factor
int getBalance(struct Node* node){
    if(node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

//Right rotate function
struct Node* rightRotate(struct Node* y){
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

//Left rotate function
struct Node* leftRotate(struct Node* x){
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

//Insert function
struct Node* insert(struct Node* node, int data){
    if(node == NULL) return createNode(data);

    if(data < node->data)
        node->left = insert(node->left,data);
    else if(data > node->data)
        node->right = insert(node->right,data);
    else 
        return node;  //if duplicate

    node->height = 1 + max(height(node->left), height(node->right));

    int balanceFactor = getBalance(node);

    //Left Left Case
    if(balanceFactor > 1 && data < node->left->data)
        return rightRotate(node);

    //Right Right Case
    if(balanceFactor < -1 && data > node->right->data)
        return leftRotate(node);

    //Left Right Case
    if(balanceFactor > 1 && data > node->left->data){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    //Right Left Case
    if(balanceFactor < -1 && data < node->right->data){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }


    return node;
}

//Inorder traversal
void inOrder(struct Node* root){
    if(root != NULL){
        inOrder(root->left);
        printf("%d ",root->data);
        inOrder(root->right);
    }
}

