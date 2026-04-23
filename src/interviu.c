#include "biblioteca.h"

int main(int argc, char const *argv[])
{
    int n;
    if (argc<3) 
    {
        return 1; 
    }
    FILE *fin=fopen(argv[1], "r");
    fscanf(fin, "%d", &n);
    Node *head=NULL;
    double pret;
    for(int i=0; i<n; i++)
    {
        fscanf(fin, "%lf", &pret);
        addAtEnd(&head, pret);
    }
    fclose(fin);
    Rt(head);
    double media=RandamentM(head, n);
    double volatil=Volatilitate(head, media, n);
    double sharpe=0.0;
    if(volatil)
        sharpe=media/volatil;
    media=trunc(media*1000.0)/1000.0;
    volatil=trunc(volatil*1000.0)/1000.0;
    sharpe=trunc(sharpe*1000.0)/1000.0;
    FILE *fout = fopen(argv[2], "w");
    fprintf(fout, "%.3f\n", media);
    fprintf(fout, "%.3f\n", volatil);
    fprintf(fout, "%.3f\n", sharpe);
    freeList(&head);
    fclose(fout);
    return 0;
}