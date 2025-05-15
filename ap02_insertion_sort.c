//AP02 AED2 Prof Álvaro
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

void selection_sort(int vetor[], int n){
    int comparacoes = 0;
    int trocas = 0;

    for(int i = 0; i < n - 1; i++){
        int menor = i;
        for(int j = i + 1; j < n; j++){
            comparacoes++;
            if(vetor[j] < vetor[menor])
                menor = j;

        }

        if (menor != i) {                     
            swap(&vetor[i], &vetor[menor]);
            trocas++;
        }
    }

    printf("%d %d \n", comparacoes, trocas);
}

void bubble_sort(int vetor[], int n){
    int comparacoes = 0;
    int trocas = 0;
    int trocou = 0;
    for(int i = 1; i < n; i++){
        trocou = FALSE;
        for(int j = 0; j < n - i; j++){
            comparacoes++;
            if(vetor[j] > vetor[j + 1]){
                swap(&vetor[j], &vetor[j + 1]);
                trocas++;
                trocou = TRUE;
            }
        }

        if(!trocou) {
            break; //nenhuma troca aconteceu então vetor ja está ordenado
        }
    }
    printf("%d %d \n", comparacoes, trocas);
}

void insertion_sort(int vetor[], int n){
    int comparacoes = 0;
    int trocas = 0;

    for (int i = 1; i < n; i++) {
        int atual = vetor[i];
        int j = i - 1;
        /*
        comparacoes++; //somando errado as comparacoes
        while (j >= 0 && vetor[j] > atual) {
            comparacoes++;
            vetor[j + 1] = vetor[j]; 
            trocas++;
            j--;
        }*/

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