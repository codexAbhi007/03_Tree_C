//Implementation of Splay Tree 

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int key;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
}Node;

//Function prototypes
Node* createNode(int key);
Node* rightRotate(Node* x); //zig
Node* leftRotate(Node* x); //zag
Node* splay(Node* root, Node* x);
Node* insert(Node* root,int key);
void inorder(Node* root);

//main
int main(){
    Node* root = NULL;
    int n, key;

    printf("Enter no of elements to insert: ");
    scanf("%d",&n);

    int i;
    for(i=0;i<n;++i){
        printf("Enter: ");
        scanf("%d",&key);
        root = insert(root,key);
    }

    printf("Inorder Traversal: ");
    inorder(root);
    return 0;
}

//Function definitions

Node* createNode(int key){
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = node->parent = NULL;
    return node;
}

Node* rightRotate(Node* x){
    Node* y = x->left;
    if(!y) return x;

    x->left = y->right;
    if(y->right)
        y->right->parent = x;

    y->right = x;
    y->parent = x->parent;
    x->parent = y;

    if(y->parent != NULL){
        if(y->parent->left == x)
            y->parent->left = y;
        else
            y->parent->right = y;
    }

    return y;
}

Node* leftRotate(Node* x){
    Node* y = x->right;
    if (!y) return x;

    x->right = y->left;
    if(y->left)
        y->left->parent = x;

    y->left = x;
    y->parent = x->parent;
    x->parent = y;

    if(y->parent != NULL){
        if(y->parent->left == x)
            y->parent->left = y;
        else
            y->parent->right = y;
    }


    return y;
}

Node* splay(Node* root, Node* x){
    while(x->parent != NULL){
        Node* p = x->parent;
        Node* gp = p->parent; //grandparent

        if(gp == NULL) {
            if(x == p->left)
                root = rightRotate(p); //Zig rotation
            else 
                root = leftRotate(p); //Zag rotation
        }else if (x == p->left && p == gp->left){
            //Zig-Zig rotation (left left case)
            root = rightRotate(gp);
            root = rightRotate(p);
        }else if(x==p->right && p == gp->right){
            //Zag-Zag rotation (right right case)
            root = leftRotate(gp);
            root = leftRotate(p);
        }else if(x == p->left && p == gp->right){
            //Zig-Zag rotation (Right Left)
            root = rightRotate(p);
            root = leftRotate(gp);
        }else if(x == p->right && p == gp->left){
            //Zag-Zig rotation (Left Right)
            root = leftRotate(p);
            root = rightRotate(gp);
        }
    }
    return x;
}

Node* insert(Node* root, int key){
    Node* newNode = createNode(key);
    Node* curr = root;
    Node* parent = NULL;

    while(curr != NULL){
        parent = curr;
        if(key < curr->key)
            curr = curr->left;
        else 
            curr = curr->right;
    }

    newNode->parent = parent;

    if(parent == NULL)
        root = newNode;
    else if(key < parent->key)
        parent->left = newNode;
    else 
        parent->right = newNode;

    return splay(root,newNode);
}

void inorder(Node* root){
    if(root==NULL) return;
    inorder(root->left);
    printf("%d ",root->key);
    inorder(root->right);
}