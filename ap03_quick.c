//AP03 AED2 Prof Álvaro
//Lucas de Oliveira Kwok - 163919

#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

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

void merge(int vetor[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp vetorays
    int L[n1], R[n2];

    // Copy data to temp vetorays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = vetor[l + i];
    for (j = 0; j < n2; j++)
        R[j] = vetor[m + 1 + j];

    // Merge the temp vetorays back into vetor[l..r
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vetor[k] = L[i];
            i++;
        }
        else {
            vetor[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        vetor[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        vetor[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(){

}

int mediana_de_tres(int v[], int inicio, int fim) {
    int meio = (inicio + fim) / 2;

    if (v[inicio] > v[meio])
        swap(&v[inicio], &v[meio]);

    if (v[inicio] > v[fim])
        swap(&v[inicio], &v[fim]);

    if (v[meio] > v[fim])
        swap(&v[meio], &v[fim]);

    swap(&v[meio], &v[fim - 1]);
    return fim - 1; 
}

int partition(int v[], int inicio, int fim) {
    int pivo_pos = mediana_de_tres(v, inicio, fim);
    int pivo = v[pivo_pos];

    int i = inicio;
    int j = fim - 1;

    while (1) {
        while (v[++i] < pivo);
        while (v[--j] > pivo);

        if (i < j)
            swap(&v[i], &v[j]);
        else
            break;
    }

    swap(&v[i], &v[pivo_pos]); 
    return i;
}

void quicksort(int v[], int inicio, int fim) {
    if (fim - inicio <= 2) {
        if (v[inicio] > v[fim])
            swap(&v[inicio], &v[fim]);
        return;
    }

    int pivo = partition(v, inicio, fim);
    quicksort(v, inicio, pivo - 1);
    quicksort(v, pivo + 1, fim);
}

void quick_sort_hibrido(){

}

void insertion_sort(int vetor[], int n){
    int comparacoes = 0;
    int trocas = 0;

    for (int i = 1; i < n; i++) {
        int atual = vetor[i];
        int j = i - 1;

        while (j >= 0) {
            comparacoes++; 
            if (vetor[j] > atual) {
                vetor[j + 1] = vetor[j]; 
                trocas++;
                j--;
            } else {
                break;
            }
        }

        if (j + 1 != i) {
            vetor[j + 1] = atual; // insercao na posicao
            trocas++;
        }
    }
    printf("%d %d\n", comparacoes, trocas);
}

int main(){
    int n = 0;

    scanf("%d", &n);
    int* vetorOriginal = malloc(sizeof(int) * n);
    int* vetorNovo = malloc(sizeof(int) * n);

    for(int i = 0; i < n; i++){
        scanf("%d", &vetorOriginal[i]);
    }

    copiar_vetor(vetorOriginal, vetorNovo, n);
    selection_sort(vetorNovo, n);

    copiar_vetor(vetorOriginal, vetorNovo, n);
    bubble_sort(vetorNovo, n);

    copiar_vetor(vetorOriginal, vetorNovo, n);
    insertion_sort(vetorNovo, n);

    free(vetorOriginal);
    free(vetorNovo);

    return 0;
}