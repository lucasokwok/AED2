//Atividade 1 AED2 Prof Álvaro
//Lucas de Oliveira Kwok - 163919
#include <stdio.h>
#include <windows.h> 
// Não foi utilizado o exemplo clock_gettime(CLOCK_MONOTONIC, &end); por incompatibilidade com o Windows

//Teste para o tamanho do vetor: N=10^8 = 100000000. 
#define TAM 100000000
//Melhor caso = 0; Pior caso = n; Caso médio = n/2
//Melhor caso = 0; Pior caso = 99999999; Caso médio = 49999999
#define BUSCA 0

int buscaLinear(long int vetor[], long int busca){
    for (int i = 0; i < TAM; i++) {
        if (vetor[i] == busca)
            return i;
    }
    return -1; 
}

int buscaBinaria(long int vetor[], long int busca){
    int inicio = 0;
    int fim = TAM - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        if (vetor[meio] == busca)
            return meio;
        else if (vetor[meio] < busca)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1; 
}

int buscaBinariaRecursivo(long int vetor[], int inicio, int fim, long int busca){
    if (inicio > fim)
        return -1; // caso base 

    int meio = (inicio + fim) / 2;

    if (vetor[meio] == busca)
        return meio;
    else if (vetor[meio] > busca)
        return buscaBinariaRecursivo(vetor, inicio, meio - 1, busca);
    else
        return buscaBinariaRecursivo(vetor, meio + 1, fim, busca);
}

void preencheVetor(long int vetor[]){
    for (int i = 0; i < TAM; i++) {
        vetor[i] = i;
        //printf("%ld", vetor[i]);
    }
}

int main(){
    long int *vetor = malloc(TAM * sizeof(long int));
    LARGE_INTEGER freq, start, end;
    double tempo_percorrido = 0;
    double soma_tempo = 0;

    QueryPerformanceFrequency(&freq);

    // ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
    preencheVetor(vetor);

    for (int i = 0; i < 20; i++) {
        QueryPerformanceCounter(&start);
        buscaLinear(vetor, BUSCA);
         //printf("%d", buscaLinear(vetor, BUSCA));
        QueryPerformanceCounter(&end);

        soma_tempo += (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
    }
    tempo_percorrido = soma_tempo / 20;
    printf("Busca Linear: %lf ms\n", tempo_percorrido);

    soma_tempo = 0; // resetar

    for (int i = 0; i < 20; i++) {
        QueryPerformanceCounter(&start);
        buscaBinaria(vetor, BUSCA);
        //printf("%d", buscaBinaria(vetor, BUSCA));
        QueryPerformanceCounter(&end);

        soma_tempo += (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
    }
    tempo_percorrido = soma_tempo / 20;
    printf("Busca Binaria: %lf ms\n", tempo_percorrido);

    soma_tempo = 0;

    for (int i = 0; i < 20; i++) {
        QueryPerformanceCounter(&start);
        buscaBinariaRecursivo(vetor, 0, TAM - 1, BUSCA);
        //printf("%d", buscaBinariaRecursivo(vetor, 0, TAM - 1, BUSCA));
        QueryPerformanceCounter(&end);

        soma_tempo += (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
    }
    tempo_percorrido = soma_tempo / 20;
    printf("Busca Binaria Recursiva: %lf ms\n", tempo_percorrido);
    free(vetor);
    return 0;
}