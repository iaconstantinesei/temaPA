# GigiQuant 

Acest repository conține soluțiile algoritmice dezvoltate pentru o suită de interviuri tehnice simulând poziția de Manager de Portofoliu la "GigiQuant". Proiectul rezolvă probleme esențiale din domeniul financiar cantitativ folosind eficient structuri de date clasice (liste înlănțuite, stive, arbori binari, grafuri).

## 🚀 Despre Proiect

Programul este conceput să preia date financiare (prețuri zilnice ale acțiunilor) și să extragă insight-uri utile investițiilor. Proiectul implementează 4 concepte majore:

1. **Calculul Sharpe Ratio:** Evaluează "profitabilitatea" riscului asumat de un portofoliu modelând evoluția datelor prin liste simplu înlănțuite.
2. **Identificarea Oportunităților de Arbitraj:** Compară cronologic prețurile acțiunilor pe 3 piețe diferite simultan folosind structuri de tip stivă (LIFO) pentru a detecta ineficiențele pieței.
3. **Diversificarea și Optimizarea Portofoliului:** Modelează traiectoria prețurilor (creștere/scădere) folosind arbori binari pentru a identifica perechi de acțiuni perfect "oglindite", capabile să stabilizeze un portofoliu.
4. **Lanțuri Markov pentru Prețuri:** Estimează algoritmic probabilitățile de tranziție ale unei acțiuni între diferite praguri de preț pe parcursul a *K* zile, utilizând grafuri și calcule exacte cu fracții ireductibile.

## 📂 Structura Fișierelor

* `interviu.c` - Conține logica principală de parsare a fișierelor de intrare și rutarea fluxului de date către rezolvarea unuia dintre cele 4 task-uri.
* `biblioteca.h` / `functii.c` - Definițiile structurilor de date (`Node`, `Fractie`, `TreeNode`, `StockList`) și funcțiile utilitare pentru matematică, manipularea arborilor și listelor.
