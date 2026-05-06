#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <ctype.h> 
typedef double Data;
#define MAX_SYM 5
struct Node {
    Data valoare;
    Data randament;
    struct Node *next;
};
typedef struct Node Node;
typedef struct StockList {
    char symbol[MAX_SYM];
    struct StockList *next;
} StockList;

typedef struct TreeNode {
    StockList *stocks;
    struct TreeNode *left;  
    struct TreeNode *right; 
    int depth;
} TreeNode;
void addStock(StockList **head, const char *sym);
TreeNode* createNode(int depth);
void freeTree(TreeNode *root);
int isEmpty(const Node *top);
Data pop(Node **top);
void addAtBeginning(Node ** head , Data v);
void addAtEnd ( Node ** head , Data v);
void freeList(Node **head);
void Rt(Node *head);
double RandamentM(Node* head, int n);
double Volatilitate(Node* head, double media, int n);
