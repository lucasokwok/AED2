#include <stdio.h>

int compBubble, compCock = 0;

void bubble(int v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            compBubble++;
            if (v[j] > v[j + 1]) {
                int tmp = v[j]; 
                v[j] = v[j + 1];
                v[j + 1] = tmp;
                trocou = 1;
            }
        }
        if (!trocou) break;
    }
}

void cocktail(int v[], int n) {
    int ini = 0, fim = n - 1, trocou = 1;
    while (trocou) {
        trocou = 0;
        for (int i = ini; i < fim; i++) {
            compCock++;
            if (v[i] > v[i + 1]) {
                int t = v[i]; 
                v[i] = v[i + 1]; 
                v[i + 1] = t;
                trocou = 1;
            }
        }
        if (!trocou) break;
        fim--;
        for (int i = fim; i > ini; i--) {
            compCock++;
            if (v[i - 1] > v[i]) {
                int t = v[i]; 
                v[i] = v[i - 1]; 
                v[i - 1] = t;
                trocou = 1;
            }
        }
        ini++;
    }
}