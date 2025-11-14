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
