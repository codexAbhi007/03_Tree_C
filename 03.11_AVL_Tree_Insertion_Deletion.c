//Insertion and Deletion of node in AVL Tree

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
int height(struct Node* node);
int max(int a,int b);
int getBalance(struct Node* node);
struct Node* rightRotate(struct Node* y);
struct Node* leftRotate(struct Node* x);
struct Node* insert(struct Node* node, int data);
struct Node* deleteNode(struct Node* root,int data);
struct Node* minValueNode(struct Node* node);
void preOrder(struct Node* root);

//Main
int main(){
    struct Node* root = NULL;
    int n, data;
    printf("Enter no of nodes: ");
    scanf("%d",&n);
    int i;
    for(i=0;i<n;++i){
        printf("Enter: ");
        scanf("%d",&data);
        root = insert(root,data);
    }

    printf("PreOrder Traversal: ");
    preOrder(root);
    printf("\n");

    printf("Enter node to be deleted: ");
    scanf("%d",&data);
    root = deleteNode(root,data);

    printf("PreOrder Traversal After Deletion: ");
    preOrder(root);
    printf("\n");

    return 0;
}

//Create a new node
struct Node* createNode(int data){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 0;
    return node;
}

//Get height
int height(struct Node* node){
    return node ? node->height : -1;
}

//max function
int max(int a,int b){
    return (a>b) ? a : b;
}

//Calculate balance Factor
int getBalance(struct Node* node){
    return node ? height(node->left) - height(node->right) : 0;
}

//Right rotation
struct Node* rightRotate(struct Node* y){
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    //update heights
    y->height = 1+ max(height(y->left), height(y->right));
    x->height = 1+ max(height(x->left), height(x->right));

    return x;
}

//Left rotation
struct Node* leftRotate(struct Node* x){
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    //update heights
    x->height = 1+ max(height(x->left), height(x->right));
    y->height = 1+ max(height(y->left), height(y->right));

    return y;
}

//Insert node
struct Node* insert(struct Node* node,int data){
    if(node == NULL) return createNode(data);

    if(data < node->data) node->left = insert(node->left,data);
    else if(data > node->data) node->right = insert(node->right, data);
    else return node; //No duplicates

    //Update height of current node
    node->height = 1 + max(height(node->left), height(node->right));

    //check balance factor
    int balance = getBalance(node);

    //LL case
    if(balance > 1 && data < node->left->data) return rightRotate(node);

    //LR case
    if(balance > 1 && data > node->left->data){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    //RL case
    if(balance < -1 && data < node->right->data){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;

}

//Find node with minimum value
struct Node* minValueNode(struct Node* node){
    struct Node* current = node;
    while(current->left != NULL)
        current = current->left;
    return current;
}

//Delete node
struct Node* deleteNode(struct Node* root,int data){
    if(root == NULL) return NULL;

    if(data < root->data)
        root->left = deleteNode(root->left, data);
    else if(data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        //Node with no child
        if(root->left == NULL && root->right == NULL){
            free(root);
            return NULL;
        }
        //node with 1 child (only right)
        else if(root -> left == NULL){
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        //node with 1 child (only left)
        else if(root->right == NULL){
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        //node with 2 children: use inorder successor
        struct Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    //Update height
    root->height = 1 + max(height(root->left), height(root->right));

    //check balance factor
    int balance = getBalance(root);

    //LL
    if(balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
    //LR
    if(balance > 1 && getBalance(root->left) < 0){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    //RR
    if(balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
    //RL
    if(balance < -1 && getBalance(root->right) > 0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;

}

//Preorder traversal
void preOrder(struct Node* root){
    if(root != NULL){
        printf("%d ",root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}