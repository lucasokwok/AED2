//AP03 AED2 Prof Álvaro
//Lucas de Oliveira Kwok - 163919

#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

int comparacoes = 0;

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

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = vetor[l + i];
    for (j = 0; j < n2; j++)
        R[j] = vetor[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    comparacoes++;
    while (i < n1 && j < n2) {
        comparacoes++;
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

    while (i < n1) {
        vetor[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        vetor[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int vetor[], int esq, int dir)
{
    //comparacoes++;
    if (esq >= dir)
        return;//caso base

    int meio = esq + (dir - esq) / 2;
    mergeSort(vetor, esq, meio);
    mergeSort(vetor, meio + 1, dir);
    merge(vetor, esq, meio, dir);
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

        comparacoes++;
        if (i < j)
            swap(&v[i], &v[j]);
        else
            break;
    }

    swap(&v[i], &v[pivo_pos]); 
    return i;
}

void quick_sort(int v[], int inicio, int fim) {
    comparacoes++;
    if (fim - inicio <= 2) {
        comparacoes++;
        if (v[inicio] > v[fim])
            swap(&v[inicio], &v[fim]);
        return;
    }

    int pivo = partition(v, inicio, fim);
    quick_sort(v, inicio, pivo - 1);
    quick_sort(v, pivo + 1, fim);
}

void insertion_sort(int vetor[], int inicio, int fim) {
    //int comparacoes = 0;
    //int trocas = 0;

    for (int i = inicio + 1; i <= fim; i++) {
        int atual = vetor[i];
        int j = i - 1;

        while (j >= inicio) {
            comparacoes++; 
            if (vetor[j] > atual) {
                vetor[j + 1] = vetor[j]; 
                //trocas++;
                j--;
            } else {
                break;
            }
        }

        comparacoes++;
        if (j + 1 != i) {
            vetor[j + 1] = atual; // insercao na posicao
            //trocas++;
        }
    }
    //printf("%d %d\n", comparacoes, trocas);
}

void quick_sort_hibrido(int vetor[], int inicio, int fim){
     while (inicio < fim) {
        comparacoes++;
        if (fim - inicio + 1 < 10) {
            insertion_sort(vetor, inicio, fim);
            break;
        } else {
            int pivo = partition(vetor, inicio, fim);
            comparacoes++;
            if (pivo - inicio < fim - pivo) {
                quick_sort_hibrido(vetor, inicio, pivo - 1);
                inicio = pivo + 1;
            } else {
                quick_sort_hibrido(vetor, pivo + 1, fim);
                fim = pivo - 1;
            }
        }
    }
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
    mergeSort(vetorNovo, 0, n - 1);

    for(int i = 0; i<n; i++)
        printf("%d ", vetorNovo[i]);

    printf("\n");
    printf("%d", comparacoes);
    comparacoes = 0;
    printf("\n");
        
    copiar_vetor(vetorOriginal, vetorNovo, n);
    quick_sort(vetorNovo, 0, n - 1);

    for(int i = 0; i<n; i++)
        printf("%d ", vetorNovo[i]);

    printf("\n");
    printf("%d", comparacoes);
    comparacoes = 0;
    printf("\n");
        
    copiar_vetor(vetorOriginal, vetorNovo, n);
    quick_sort_hibrido(vetorNovo, 0, n - 1);

    for(int i = 0; i<n; i++)
        printf("%d ", vetorNovo[i]);

    printf("\n");
    printf("%d", comparacoes);

    free(vetorOriginal);
    free(vetorNovo);

    return 0;
}