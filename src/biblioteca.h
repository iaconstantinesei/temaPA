#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double Data;

struct Node {
    Data valoare;
    Data randament;
    struct Node *next;
};
typedef struct Node Node;
void addAtBeginning ( Node ** head , Data v);
void addAtEnd ( Node ** head , Data v);
double Randament(Node* head, int n);
double Volatilitate(Node* head, double media, int n);