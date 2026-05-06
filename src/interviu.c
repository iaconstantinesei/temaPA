#include "biblioteca.h"

int main(int argc, char const *argv[])
{

    if (argc < 3)
    {
        return 1;
    }

    FILE *f = fopen(argv[1], "r");

    char buffer[1000];
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
        if (strchr(buffer, ','))
        {
            FILE *fin = fopen(argv[1], "r");
            FILE *fout = fopen(argv[2], "w");

            char symbols[50][15];
            int moves[1000][50];
            double prevPrices[50], currPrices[50];
            int numStocks = 0, dayCount = 0;
            const char *p = strtok(buffer, ", \r\n");
            while (p && numStocks < 50)
            {
                int j = 0;
                for (int i = 0; p[i]; i++)
                {
                    if (isalnum((unsigned char)p[i]))
                        symbols[numStocks][j++] = p[i];
                }
                symbols[numStocks][j] = '\0';
                if (j > 0)
                    numStocks++;
                p = strtok(NULL, ", \r\n");
            }

            char line[4096];
            fgets(line, sizeof(line), fin);
            if (fgets(line, sizeof(line), fin))
            {
                const char *ptr = strtok(line, ", \r\n");
                for (int i = 0; i < numStocks && ptr; i++)
                {
                    prevPrices[i] = atof(ptr);
                    ptr = strtok(NULL, ", \r\n");
                }
                dayCount = 1;
            }
            while (fgets(line, sizeof(line), fin))
            {
                const char *ptr = strtok(line, ", \r\n");
                for (int i = 0; i < numStocks && ptr; i++)
                {
                    currPrices[i] = atof(ptr);
                    if (currPrices[i] >= prevPrices[i])
                    {
                        moves[dayCount][i] = 1; 
                    }
                    else
                    {
                        moves[dayCount][i] = 0; 
                    }
                    prevPrices[i] = currPrices[i];
                    ptr = strtok(NULL, ", \r\n");
                }
                dayCount++;
            }
            TreeNode *root = createNode(0);
            int firstPair = 1;
            for (int i = 0; i < numStocks; i++)
            {
                TreeNode *curr = root;
                for (int d = 1; d < dayCount; d++)
                {
                    if (moves[d][i] == 1)
                    {
                        if (!curr->right)
                            curr->right = createNode(d);
                        curr = curr->right;
                    }
                    else
                    {
                        if (!curr->left)
                            curr->left = createNode(d);
                        curr = curr->left;
                    }
                }
                addStock(&(curr->stocks), symbols[i]); 
            }
            for (int i = 0; i < numStocks; i++)
            {
                TreeNode *m = root;
                int ok = 1;
                for (int d = 1; d < dayCount; d++)
                {
                    if (moves[d][i] == 1)
                    {
                        if (m->left)
                            m = m->left;
                        else
                        {
                            ok = 0;
                            break;
                        }
                    }
                    else
                    {
                        if (m->right)
                            m = m->right;
                        else
                        {
                            ok = 0;
                            break;
                        }
                    }
                }
                if (ok && m->stocks)
                {
                    StockList *s = m->stocks;
                    while (s)
                    {
                        int cnt = -1;
                        for (int k = 0; k < numStocks; k++)
                        {
                            if (strcmp(s->symbol, symbols[k]) == 0)
                            {
                                cnt = k;
                                break;
                            }
                        }
                        if (cnt > i)
                        {
                            if (!firstPair)
                            {
                                fprintf(fout, "\n");
                            }
                            fprintf(fout, "%s-%s", symbols[i], s->symbol);
                            firstPair = 0; 
                        }
                        s = s->next;
                    }
                }
            }
            fclose(fin);
            fclose(fout);
            freeTree(root);
        }
        else{
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
    }

    return 0;
}
