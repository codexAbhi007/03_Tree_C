//Search Operations in BST (both iterative and recursive approaches)

#include <stdio.h>
#include <stdlib.h>

//Node 
struct Node{
    int data;
    struct Node* left;
    struct Node* right;
};

//Function prototypes
struct Node* createNode(int value);
struct Node* insert(struct Node* root, int value);
struct Node* searchRecursive(struct Node* root, int key);
struct Node* searchIterative(struct Node* root, int key);

//main
int main(){
    struct Node* root = NULL;
    int n,value,key;

    printf("Enter no of Nodes: ");
    scanf("%d",&n);

    int i;
    for(i = 0;i<n;++i){
        printf("Enter: ");
        scanf("%d",&value);
        root = insert(root,value);
    }

    printf("Enter value to be searched: ");
    scanf("%d",&key);

    //Recursive Search
    struct Node* foundRec = searchRecursive(root,key);
    if(foundRec != NULL) printf("Found: %d\n",foundRec->data);
    else printf("Not Found!\n");

    //Iterative Search
    struct Node* foundIter = searchIterative(root,key);
    if(foundIter != NULL) printf("Found: %d\n",foundIter->data);
    else printf("Not Found!\n");

    return 0;
}

//Create node function
struct Node* createNode(int value){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//Insert into BST
struct Node* insert(struct Node* root,int value){
    if(root == NULL)
        return createNode(value);
    
    if(value < root->data)
        root->left = insert(root->left,value);
    
    else if(value > root->data)
        root->right = insert(root->right,value);

    return root;
}

//Recursive Search Function

struct Node* searchRecursive(struct Node* root, int key){
    if(root == NULL || root->data == key)
        return root;

    if(key < root->data)
        return searchRecursive(root->left, key);
    else    
        return searchRecursive(root->right,key);
}

//Iterative Search Function

struct Node* searchIterative(struct Node* root,int key){
    while(root != NULL){
        if(key == root->data)
            return root;
        else if(key < root->data)
            root = root->left;
        else  
            root = root->right;
    }

    return NULL;
}