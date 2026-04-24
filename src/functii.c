#include "biblioteca.h"



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
