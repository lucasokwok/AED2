//AP04 AED2 Prof Álvaro
//Lucas de Oliveira Kwok - 163919

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int C[27];

int mapear_caractere(char c, char *chave) {
    if (c == ' ') return 0;
    for (int i = 0; i < 26; i++) {
        if (chave[i] == c) 
            return i + 1;
    }
    return -1;
}

void counting_sort(char palavras[][21], int n, int pos, char *chave) {
    int i, index;
    char saida[100][21];//estipulado maximo de 100 palavras p nao utilizar alocacao dinamica

    for (i = 0; i < 27; i++) 
        C[i] = 0;

    for (i = 0; i < n; i++) {
        char c = palavras[i][pos];
        index = mapear_caractere(c, chave);
        C[index]++;
    }

    for (i = 1; i < 27; i++) {
        C[i] = C[i] + C[i - 1];
    }

    for (i = 0; i < 27; i++) {
        printf("%d", C[i]);
        if (i == 26)
            printf("\n");
        else
            printf(" ");
    }


    for (i = n - 1; i >= 0; i--) {
        char c = palavras[i][pos];
        index = mapear_caractere(c, chave);
        strcpy(saida[C[index] - 1], palavras[i]);
        C[index]--;
    }

    for (i = 0; i < n; i++) {
        strcpy(palavras[i], saida[i]);
    }
}

void radix_sort(char palavras[][21], int n, int d, char *chave) {
    for (int i = d - 1; i >= 0; i--) {
        counting_sort(palavras, n, i, chave);
    }
}

void converter_minusculas(char *s) {
    for (int i = 0; s[i]; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] += 32; // diferença entre 'A' e 'a' na tabela asc
        }
    }
}

int main() {
    int n, i;
    char chave[27];
    char palavras[100][21];
    char temp[100];
    int tam_maiorpalavra = 0;

    scanf("%d", &n);
    scanf("%s", chave);
    getchar(); // limpa '\n' depois da chave

    for (i = 0; i < n; i++) {
        scanf("%s", temp);
        //verificar maiusculas
        converter_minusculas(temp); 
        strcpy(palavras[i], temp);
        int tam_palavraatual = strlen(temp);
        if (tam_palavraatual > tam_maiorpalavra)     
            tam_maiorpalavra = tam_palavraatual;
    }

    for (i = 0; i < n; i++) {
        int tam_palavraatual = strlen(palavras[i]);
        for (int j = tam_palavraatual; j < tam_maiorpalavra; j++) {
            palavras[i][j] = ' ';
        }
        palavras[i][tam_maiorpalavra] = '\0';
    }

    for (i = 0; i < n; i++) {
        int j = strlen(palavras[i]) - 1;

        while (j >= 0 && palavras[i][j] == ' ') {
            j--;
        }
        for (int k = 0; k <= j; k++) {
            putchar(palavras[i][k]);
        }
        printf(".\n");
    }


    printf("%d\n", tam_maiorpalavra); 

    radix_sort(palavras, n, tam_maiorpalavra, chave);

    for (i = 0; i < n; i++) {
        printf("%s\n", palavras[i]);
    }

    return 0;
}
