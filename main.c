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

BST_Node* search(BST_Node* root, char* str) {

    if(root == NULL) {
        
        return NULL;
        
    }

    int compare = strcmp(str, root->ptr->str);
    if(compare == 0) {
        
        return root;
        
    }

    if (compare < 0) {
        
        return search(root->left, str);
        
    } else {
        
        return search(root->right, str);
        
    }
    
}

void freeTree(BST_Node* root) {
    
    if(root == NULL) {
        
        return;
        
    }
    
    freeTree(root->left);
    freeTree(root->right);
    freeNodeData(root);
    free(root);
    
}

int main(void) {
    
    int n;
    scanf("%d", &n);
    BST_Node* root = NULL;
    char buffer[MAXSIZE + 1];

    for(int d = 0; d < n; d++) {
        
        int t;
        scanf("%d", &t);
        if(t == 1) {
            
            int g;
            scanf("%d %s", &g, buffer);
            root = insert(root, buffer, g);

        } else if(t == 2) {
            
            int g;
            scanf("%d %s", &g, buffer);
            root = deleteNode(root, buffer, g);

        } else if(t == 3) {
            
            scanf("%s", buffer);
            BST_Node* result = search(root, buffer);

            if(result == NULL) {
                
                printf("-1\n");
                
            } else {
                
                int found = 0;
                for(int e = 0; e < NUMGAMES; e++) {
                    
                    if(result->ptr->allowed[e] == 1) {
                        
                        printf("%d ", e);
                        found = 1;
                        
                    }
                    
                }

                if(!found) {
                    
                    printf("-1\n");
                    
                } else {
                    
                    printf("\n");
                    
                }
                
            }
            
        } else if(t == 4) {
            
            int g;
            scanf("%d", &g);

        } else if(t == 5) {
            
            int g, L;
            scanf("%d %d", &g, &L);

        } else if(t == 6) {
            
            scanf("%s", buffer);

        }
        
    }

    return 0;
    
}
