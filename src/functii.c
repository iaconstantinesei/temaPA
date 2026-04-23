#include "biblioteca.h"

void addAtBeginning ( Node **head , Data v)
{
    Node *newNode=(Node*)malloc(sizeof(Node));
    newNode->valoare=v;
    newNode->next=*head ;
    *head=newNode ;
}

void addAtEnd ( Node **head , Data v)
{
    Node *aux=* head ;
    Node *newNode=(Node*)malloc(sizeof(Node));
    newNode->valoare=v; 
    if (* head==NULL) 
        addAtBeginning (&* head , v);
    else 
    { 
        while (aux->next!=NULL) aux=aux->next ;
        aux->next=newNode ;
        newNode->next=NULL ; 
    }
}
void Rt(Node *head) {
    if (head==NULL || head->next==NULL) return;

    Node *prev=head;
    Node *curent=head->next;

    while (curent != NULL) {
        curent->randament=(curent->valoare-prev->valoare)/prev->valoare;
        prev=curent;
        curent=curent->next;
    }
}

double RandamentM(Node *head, int n)
{
    if(head==NULL || n<=0)
        return 0.0;
    double suma=0.0;
    Node *curent=head->next;
    while(curent!=NULL)
    {
        suma+=curent->randament;
        curent=curent->next;
    }
    return suma/n;
}

double Volatilitate(Node* head, double media, int n)
{
     if(head==NULL || n<=0)
        return 0.0;
    double sp=0.0;
    Node *curent=head->next;
    while(curent!=NULL)
    {
        sp+=pow(curent->randament-media, 2);
        curent=curent->next;
    }
    return sqrt(sp/n);
}
