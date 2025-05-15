//AP03 AED2 Prof Álvaro
//Lucas de Oliveira Kwok - 163919

#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

int comparacoesMerge = 0;
int comparacoesQuick = 0;
int comparacoesQuickHibrido = 0;

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
        if (esq[i] <= dir[j])
            vetor[k++] = esq[i++];
        else
            vetor[k++] = dir[j++];
    }

    while (i < tamEsq) {
        comparacoesMerge++; 
        vetor[k++] = esq[i++];
    }

    while (j < tamDir) {
        comparacoesMerge++;
        vetor[k++] = dir[j++];
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

int partition(int A[], int inicio, int fim, int pivo) {
    int i = inicio;
    int j = fim;

    while (i <= j) {
        while (A[i] < pivo) i++;
        while (A[j] > pivo) j--;

        comparacoesQuick++;
        if (i <= j) {
            swap(&A[i], &A[j]);
            i++;
            j--;
        }
    }

    return i;
}

void quicksortMedianaDeTres(int A[], int inicio, int fim) {
    if (inicio >= fim) return;

    int meio = inicio + (fim - inicio) / 2;
    int a = A[inicio], b = A[meio], c = A[fim];

    // calcula valor da mediana entre os 3
    //comparacoesQuick += 3; // ou 5, dependendo do que o exercício espera
    int pivo;
    if (a < b) {
        if (b < c) {
            // a < b < c
            pivo = b;
        } else if (a < c) {
            // a < c <= b
            pivo = c;
        } else {
            // c <= a < b
            pivo = a;
        }
    } else {
        if (c < b) {
            // c < b <= a
            pivo = b;
        } else if (c < a) {
            // b <= c < a
            pivo = c;
        } else {
            // b <= a <= c
            pivo = a;
        }
    }


    int index = partition(A, inicio, fim, pivo);

    quicksortMedianaDeTres(A, inicio, index - 1);
    quicksortMedianaDeTres(A, index, fim);
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
    quicksortMedianaDeTres(vetorNovo, 0, n - 1);

    for(int i = 0; i<n; i++)
        printf("%d ", vetorNovo[i]);

    printf("\n");
    printf("%d\n", comparacoesQuick);
    
    free(vetorOriginal);
    free(vetorNovo);

    return 0;
}
