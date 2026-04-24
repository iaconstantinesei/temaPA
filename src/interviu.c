#include "biblioteca.h"

int main(int argc, char const *argv[])
{

    if (argc < 3)
    {
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), f) == NULL)
    {
        fclose(f);
        
        return 1;
    }
    fclose(f);
    if (isdigit(buffer[0]))
    {
        FILE *fin = fopen(argv[1], "r");
        int n;
        fscanf(fin, "%d", &n);
        Node *head = NULL;
        double pret;
        for (int i = 0; i < n; i++)
        {
            fscanf(fin, "%lf", &pret);
            addAtEnd(&head, pret);
        }
        fclose(fin);
        Rt(head);
        double media = RandamentM(head, n);
        double volatil = Volatilitate(head, media, n);
        double sharpe = 0.0;
        if (volatil)
            sharpe = media / volatil;
        media = trunc(media * 1000.0) / 1000.0;
        volatil = trunc(volatil * 1000.0) / 1000.0;
        sharpe = trunc(sharpe * 1000.0) / 1000.0;
        FILE *fout = fopen(argv[2], "w");
        fprintf(fout, "%.3f\n", media);
        fprintf(fout, "%.3f\n", volatil);
        fprintf(fout, "%.3f\n", sharpe);
        freeList(&head);
        fclose(fout);
    }
    else
    {
        FILE *fin = fopen(argv[1], "r");
        FILE *fout = fopen(argv[2], "w");
        char nume1[50], nume2[50], nume3[50];
        Node *lista1 = NULL, *lista2 = NULL, *lista3 = NULL;
        char line[100];
        fgets(line, sizeof(line), fin);
        line[strcspn(line, "\r\n")] = 0;
        strcpy(nume1, line);
        int count1 = 0;
        while (fgets(line, sizeof(line), fin) && !isalpha(line[0]))
        {
            addAtBeginning(&lista1, atof(line));
            count1++;
        }
        line[strcspn(line, "\r\n")] = 0;
        strcpy(nume2, line);
        int count2 = 0;
        while (fgets(line, sizeof(line), fin) && !isalpha(line[0]))
        {
            addAtBeginning(&lista2, atof(line));
            count2++;
        }
        line[strcspn(line, "\r\n")] = 0;
        strcpy(nume3, line);
        int count3 = 0;
        while (fgets(line, sizeof(line), fin))
        {
            addAtBeginning(&lista3, atof(line));
            count3++;
        }
        int zi = 1;
        Node *c1 = lista1, *c2 = lista2, *c3 = lista3;

        while (c1 != NULL && c2 != NULL && c3 != NULL)
        {
            double v1 = c1->valoare;
            double v2 = c2->valoare;
            double v3 = c3->valoare;

            if (v1 == v2 && v1 != v3)
            {
                fprintf(fout, "ziua %d - %.2f - %s\n", zi, fabs(v1 - v3), nume3);
            }
            else if (v1 == v3 && v1 != v2)
            {
                fprintf(fout, "ziua %d - %.2f - %s\n", zi, fabs(v1 - v2), nume2);
            }
            else if (v2 == v3 && v2 != v1)
            {
                fprintf(fout, "ziua %d - %.2f - %s\n", zi, fabs(v2 - v1), nume1);
            }

            c1 = c1->next;
            c2 = c2->next;
            c3 = c3->next;
            zi++;
        }

        freeList(&lista1);
        freeList(&lista2);
        freeList(&lista3);
        fclose(fin);
        fclose(fout);
    }

    
    return 0;
}
