//Implementation of Red Black tree

#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

typedef struct Node{
    int data;
    int color;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
}Node;

//Function prototypes
Node* insert(Node* root,int data);
Node* createNode(int data);
Node* insertRecursive(Node* root,Node* z);
Node* fixInsertion(Node* root,Node* z);
Node* rotateLeft(Node* root,Node* x);
Node* rotateRight(Node* root, Node* x);
void inOrder(Node* root);

//Main
int main(){
    int n,val;
    Node* root = NULL;

    printf("Enter no of nodes: ");
    scanf("%d",&n);

    int i;
    for(i=0;i<n;++i){
        printf("Enter value: ");
        scanf("%d",&val);
        root = insert(root,val);
    }

    printf("Inorder Traversal: ");
    inOrder(root);

    return 0;
}

//Function definitions

Node* insert(Node* root,int data){
    Node* z = createNode(data);

    if(root == NULL){
        z->color = BLACK;
        return z;
    }

    root = insertRecursive(root,z);
    return fixInsertion(root,z);
}

Node* createNode(int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = RED;
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

//Normal BST Insertion using recursion

Node* insertRecursive(Node* root,Node* z){
    if(root == NULL)
        return z;

    if(z->data < root->data){
        root->left = insertRecursive(root->left, z);
        root->left->parent = root;
    }else if(z->data > root->data){
        root->right = insertRecursive(root->right,z);
        root->right->parent  = root;
    }else{
        printf("Duplicate ignored!");
        free(z);
    }
    return root;
}

Node* fixInsertion(Node* root, Node* z){
    //Loop untill red red violation is resolve or we reach the root
    while(z!= root && z->parent->color ==RED){
        Node* parent = z->parent;
        Node* grandparent = parent->parent;

        //Case 1 and 2: Parent is on the left of grandparent
        if(parent == grandparent->left){
            Node* uncle = grandparent->right;

            //Case 1: Uncle is Red -> Recoloring (No rotation)
            if(uncle != NULL && uncle->color == RED){
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                z = grandparent;
            }else{
                //Case 2: Uncle is Black or NULL
                if(z == parent->right){
                    //Case 2.1 : Left-Right Rotation (LR) (First rotate Left then Right)
                    z = parent;
                    root = rotateLeft(root,z); //Rotate from LR to LL
                }
                //Case 2.2 Left-Left (LL)
                //Perform only right rotation on grandparent and recolor
                parent->color = BLACK;
                grandparent->color = RED;
                root = rotateRight(root,grandparent); //for both 2.1 and 2.2
            }
        }

        //Case 3 and 4: Parent is on the right of grandparent
        else{
            Node* uncle = grandparent->left;

            //Case 3: Uncle is RED-> Recoloring (No rotation)
            if(uncle != NULL && uncle->color == RED){
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                z = grandparent;
            }else{
                //Case 4: Uncle is BLACK or NULL

                if(z == parent->left){
                    //Case 4.1 Right-Left (RL) (First rotate right then rotate left)
                    z = parent;
                    root = rotateRight(root,z); //Rotate from RL to RR
                }

                //Case 4.2 Right Right (RR) (Only rotate left)
                parent->color = BLACK;
                grandparent->color = RED;
                root = rotateLeft(root,grandparent); //for both 4.1 and 4.2
            }
        }
    }

    //Root is always black
    root->color = BLACK;
    return root;
}

/*
    Before rotateLeft(root, x):

            P
            |
            x
           / \
         A     y
             /   \
            B     C

    After rotateLeft(root, x):

            P
            |
            y
           / \
          x   C
         / \
        A   B
*/

Node* rotateLeft(Node* root, Node* x){
    Node* y = x->right;
    x->right = y->left;
    if(y->left) y->left->parent = x;

    y->parent = x->parent;

    if(!x->parent) root = y;
    else if(x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;

    y->left = x;
    x->parent = y;

    return root;
}

/*
    Before rotateRight(root, x):

            P
            |
            x
           / \
         y     C
        / \
       A   B

    After rotateRight(root, x):

            P
            |
            y
           / \
          A   x
             / \
            B   C
*/

Node* rotateRight(Node* root,Node* x){
    Node* y = x->left;
    x->left = y->right;
    if(y->right) y->right->parent = x;

    y->parent = x->parent;

    if(!x->parent) root = y;
    else if(x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;

    x->right = x;
    x->parent = y;

    return root;
}

//Inorder traversal
void inOrder(Node* root){
    if(!root) return;
    inOrder(root->left);
    printf("%d(%s) ",root->data,root->color == RED ? "R" : "B");
    inOrder(root->right);
}

