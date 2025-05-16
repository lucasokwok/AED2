//AP03 AED2 Prof Álvaro
//Lucas de Oliveira Kwok - 163919

#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

int comparacoesMerge = 0;
int comparacoesQuick = 0;

void swap(int* x, int* y){
    int aux = *x;
    *x = *y;
    *y = aux;
}

void copiar_vetor(int origem[], int destino[], int n){
    for (int i = 0; i < n; i++){
        destino[i] = origem[i];
    }
}

void merge(int vetor[], int esquerda, int meio, int direita)
{
    int tamEsq = meio - esquerda + 1;
    int tamDir = direita - meio;

    int *esq = (int *)malloc(tamEsq * sizeof(int));
    int *dir = (int *)malloc(tamDir * sizeof(int));

    for (int i = 0; i < tamEsq; i++)
        esq[i] = vetor[esquerda + i];
    for (int j = 0; j < tamDir; j++)
        dir[j] = vetor[meio + 1 + j];

    int i = 0;
    int j = 0;
    int k = esquerda;

    while (i < tamEsq && j < tamDir) {
        comparacoesMerge++; 
        if (esq[i] <= dir[j]){
            vetor[k] = esq[i];
            i++;
            k++;
        } else {
            vetor[k] = dir[j];
            j++;
            k++;
        }
    }

    while (i < tamEsq) {
        comparacoesMerge++; 
        vetor[k] = esq[i];
        k++;
        i++;
    }

    while (j < tamDir) {
        comparacoesMerge++;
        vetor[k] = dir[j];
        k++;
        j++;
    }

    free(esq);
    free(dir);
}

void mergeSort(int vetor[], int esquerda, int direita)
{
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;

        mergeSort(vetor, esquerda, meio);
        mergeSort(vetor, meio + 1, direita);
        merge(vetor, esquerda, meio, direita);
    }
}

int mediana3(int vetor[], int inicio, int fim) {
    int meio = inicio + (fim - inicio) / 2;
    
    comparacoesQuick++;
    if (vetor[inicio] > vetor[meio])
        swap(&vetor[inicio], &vetor[meio]);
    
    comparacoesQuick++;
    if (vetor[inicio] > vetor[fim])
        swap(&vetor[inicio], &vetor[fim]);
    
    comparacoesQuick++;
    if (vetor[meio] > vetor[fim])
        swap(&vetor[meio], &vetor[fim]);
    
    return meio;
}

void insertionSort(int vetor[], int inicio, int fim) {
    for (int i = inicio + 1; i <= fim; i++) {
        int atual = vetor[i];
        int j = i - 1;
        
        while (j >= inicio && vetor[j] > atual) {
            comparacoesQuick++;
            vetor[j + 1] = vetor[j];
            j--;
        }
        if (j >= inicio) 
            comparacoesQuick++;
        vetor[j + 1] = atual;
    }
}

int partition(int vetor[], int inicio, int fim) {
    int pivo_pos = mediana3(vetor, inicio, fim);
    int pivo = vetor[pivo_pos];
    swap(&vetor[pivo_pos], &vetor[fim]);
    
    int i = inicio;
    for (int j = inicio; j < fim; j++) {
        comparacoesQuick++;
        if (vetor[j] <= pivo) {
            swap(&vetor[i], &vetor[j]);
            i++;
        }
    }
    swap(&vetor[i], &vetor[fim]);
    return i;
}

void quicksort(int vetor[], int inicio, int fim) {
    if (inicio < fim) {
        int p = partition(vetor, inicio, fim);
        quicksort(vetor, inicio, p - 1);
        quicksort(vetor, p + 1, fim);
    }
}

void quicksortHibrido(int vetor[], int inicio, int fim) {
    if (inicio < fim) {
        if (fim - inicio + 1 <= 5) {
            insertionSort(vetor, inicio, fim);
        } else {
            int p = partition(vetor, inicio, fim);
            quicksortHibrido(vetor, inicio, p - 1);
            quicksortHibrido(vetor, p + 1, fim);
        }
    }
}

int main()
{
    int n = 0;

    scanf("%d", &n);
    int* vetorOriginal = malloc(sizeof(int) * n);
    int* vetorNovo = malloc(sizeof(int) * n);

    for(int i = 0; i < n; i++){
        scanf("%d", &vetorOriginal[i]);
    }

    copiar_vetor(vetorOriginal, vetorNovo, n);
    mergeSort(vetorNovo, 0, n - 1);

    for(int i = 0; i<n; i++)
        printf("%d ", vetorNovo[i]);

    printf("\n");
    printf("%d\n", comparacoesMerge);

    copiar_vetor(vetorOriginal, vetorNovo, n);
    quicksort(vetorNovo, 0, n - 1);

    for(int i = 0; i<n; i++)
        printf("%d ", vetorNovo[i]);

    printf("\n");
    printf("%d\n", comparacoesQuick);
    comparacoesQuick = 0;

    copiar_vetor(vetorOriginal, vetorNovo, n);
    quicksortHibrido(vetorNovo, 0, n - 1);

    for(int i = 0; i<n; i++)
        printf("%d ", vetorNovo[i]);

    printf("\n");
    printf("%d\n", comparacoesQuick);
    
    free(vetorOriginal);
    free(vetorNovo);

    return 0;
}
