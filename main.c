/* COP 3502C PA5
This program is written by: ANH NHAT LE (Robert) */

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 19
#define NUMGAMES 6

typedef struct NYT_String {

    char* str;
    int allowed[NUMGAMES];

} NYT_String;

typedef struct BST_Node {

    NYT_String* ptr;
    BST_Node* left;
    BST_Node* right;

} BST_Node;

BST_Node* createNode(char* str, int gameNo) {

    BST_Node* newNode = (BST_Node*)malloc(sizeof(BST_Node));
    if(newNode == NULL) {

        return NULL;
      
    }

    newNode->ptr = (NYT_String*)malloc(sizeof(NYT_String));
    if(newNode->ptr == NULL) {

        free(newNode);
        return NULL;
      
    }

    newNode->ptr->str = (char*)malloc(sizeof(char) * (strlen(str) + 1));
    if(newNode->ptr->str == NULL) {

        free(newNode->ptr);
        free(newNode);
        return NULL;
      
    }
    strcpy(newNode->ptr->str, str);

    for(int a = 0; a < NUMGAMES; a++) {
      
        newNode->ptr->allowed[a] = 0;
      
    }
    newNode->ptr->allowed[gameNo] = 1;

    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
    
}

BST_Node* insert(BST_Node* root, char* str, int gameNo) {

    if(root == NULL) {
        
        return createNode(str, gameNo);
        
    }

    int compare = strcmp(str, root->ptr->str);
    if(compare < 0) {
        
        root->left = insert(root->left, str, gameNo);
        
    } else if(compare > 0) {

        root->right = insert(root->right, str, gameNo);
        
    } else {

        root->ptr->allowed[gameNo] = 1;
        
    }
    
    return root;
    
}

void freeNodeData(BST_Node* node) {
    
    if(node == NULL) {
        
        return;
        
    }
    
    if(node->ptr != NULL) {
        
        if (node->ptr->str != NULL) {
            
            free(node->ptr->str);
            
        }
        free(node->ptr);
        
    }
    
}

BST_Node* findMin(BST_Node* root) {
    if(root == NULL) {
        
        return NULL;
        
    }

    while(root->left != NULL) {
        
        root = root->left;
        
    }
    return root;
    
}

BST_Node* deleteNode(BST_Node* root, char* str, int gameNo) {

    if(root == NULL) {
        
        return NULL;
        
    }

    int compare = strcmp(str, root->ptr->str);
    if(compare < 0) {
        
        root->left = deleteNode(root->left, str, gameNo);
        
    } else if(compare > 0) {
        
        root->right = deleteNode(root->right, str, gameNo);
        
    } else {

        root->ptr->allowed[gameNo] = 0;
        int isStillAllowed = 0;
        for(int b = 0; b < NUMGAMES; b++) {
            
            if(root->ptr->allowed[b] == 1) {
                
                isStillAllowed = 1;
                break;
                
            }
            
        }

        if(isStillAllowed) {
            
            return root;
            
        }
        
        if(root->left == NULL) {
            
            BST_Node* temp = root->right;
            freeNodeData(root); 
            free(root);         
            return temp;        
            
        } else if(root->right == NULL) {
            
            BST_Node* temp = root->left;
            freeNodeData(root);
            free(root);
            return temp;
            
        } else {

            BST_Node* successor = findMin(root->right);
            free(root->ptr->str);

            root->ptr->str = (char*)malloc(sizeof(char) * (strlen(successor->ptr->str) + 1));
            strcpy(root->ptr->str, successor->ptr->str);

            for(int c = 0; c < NUMGAMES; c++) {
                
                root->ptr->allowed[c] = successor->ptr->allowed[c];
                
            }
            root->right = deleteNode(root->right, successor->ptr->str, gameNo);
            
        }
        
    }
    
    return root;
    
}
