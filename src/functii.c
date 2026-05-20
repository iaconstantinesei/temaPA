#include "biblioteca.h"

long long cmmdc(long long a, long long b) {
    if (b == 0) return a;
    return cmmdc(b, a % b);
}

Fractie simplifica(Fractie f) {
    if (f.numarator == 0) return (Fractie){0, 1};
    long long divizor = cmmdc(llabs(f.numarator), llabs(f.numitor));
    f.numarator /= divizor;
    f.numitor /= divizor;
    if (f.numitor < 0) { 
        f.numarator = -f.numarator;
        f.numitor = -f.numitor;
    }
    return f;
}

Fractie aduna(Fractie a, Fractie b) {
    if (a.numarator == 0) return b;
    if (b.numarator == 0) return a;
    Fractie rezultat;
    rezultat.numarator = a.numarator * b.numitor + b.numarator * a.numitor;
    rezultat.numitor = a.numitor * b.numitor;
    return simplifica(rezultat);
}

Fractie inmulteste(Fractie a, Fractie b) {
    if (a.numarator == 0 || b.numarator == 0) return (Fractie){0, 1};
    Fractie rezultat;
    rezultat.numarator = a.numarator * b.numarator;
    rezultat.numitor = a.numitor * b.numitor;
    return simplifica(rezultat);
}


TreeNode* createNode(int depth) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->stocks = NULL;
    node->left = node->right = NULL;
    node->depth = depth;
    return node;
}
void addStock(StockList **head, const char *sym) {
    StockList *newNode = (StockList*)malloc(sizeof(StockList));
    int j = 0;
    for (int i = 0; sym[i] != '\0'; i++) {
        if (isalnum(sym[i])) newNode->symbol[j++] = sym[i];
    }
    newNode->symbol[j] = '\0';
    newNode->next = NULL;

    if (*head == NULL) *head = newNode;
    else {
        StockList *temp = *head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
}
void freeTree(TreeNode *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    StockList *curr = root->stocks;
    while (curr != NULL) {
        StockList *temp = curr;
        curr = curr->next;
        free(temp); 
    }
    free(root);
}


void addAtBeginning(Node **head, Data v) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return; 
    newNode->valoare = v;
    newNode->randament = 0; 
    newNode->next = *head;
    *head = newNode;
}

void addAtEnd(Node **head, Data v) {
    if (*head == NULL) {
        addAtBeginning(head, v); 
        return; 
    }
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return;
    newNode->valoare = v;
    newNode->randament = 0;
    newNode->next = NULL;
    Node *aux = *head;
    while (aux->next != NULL) {
        aux = aux->next;
    }
    aux->next = newNode;
}

void freeList(Node **head) {
    while (*head != NULL) {
        Node *temp;
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

void Rt(Node *head) {
    if (head == NULL || head->next == NULL) return;
    const Node *prev = head;
    Node *curent = head->next;
    while (curent != NULL) {
        curent->randament = (curent->valoare - prev->valoare) / prev->valoare;
        prev = curent;
        curent = curent->next;
    }
}

double RandamentM(Node *head, int n) {
    if (head == NULL || n <= 1) return 0.0;
    double suma = 0.0;
    Node *curent = head->next; 
    while (curent != NULL) {
        suma += curent->randament;
        curent = curent->next;
    }
    return suma / (n - 1); 
}

double Volatilitate(Node *head, double media, int n) {
    if (head == NULL || n <= 1) return 0.0;
    double sp = 0.0;
    Node *curent = head->next;
    while (curent != NULL) {
        sp += pow(curent->randament - media, 2);
        curent = curent->next;
    }
    return sqrt(sp / (n - 1)); 
}
