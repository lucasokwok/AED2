/*  AP06 – AVL × Árvore Vermelho-Preta
    Autor: seu_nome
    Compilar:  gcc ap06.c -o ap06
*/

#include <stdio.h>
#include <stdlib.h>

/* ---------- Estruturas ---------- */
typedef struct AVLNode {
    int chave;
    int altura;
    struct AVLNode *esq, *dir;
} AVLNode;

typedef enum { VERMELHO, PRETO } Cor;

typedef struct RBNode {
    int chave;
    Cor cor;
    struct RBNode *pai, *esq, *dir;
} RBNode;

/* ---------- Contadores globais ---------- */
long rotAVL = 0;
long rotRB  = 0;
long corRB  = 0;

/* ---------- Funções utilitárias ---------- */
static inline int max(int a, int b) { return a > b ? a : b; }

/* ---------- AVL ---------- */
static int alturaAVL(AVLNode *n) { return n ? n->altura : -1; }

static AVLNode *novoAVL(int k) {
    AVLNode *n = (AVLNode *)malloc(sizeof(AVLNode));
    n->chave = k; n->altura = 0; n->esq = n->dir = NULL;
    return n;
}

static AVLNode *rotDir(AVLNode *y) {
    rotAVL++;
    AVLNode *x = y->esq;
    y->esq = x->dir;
    x->dir = y;
    y->altura = 1 + max(alturaAVL(y->esq), alturaAVL(y->dir));
    x->altura = 1 + max(alturaAVL(x->esq), alturaAVL(x->dir));
    return x;
}

static AVLNode *rotEsq(AVLNode *x) {
    rotAVL++;
    AVLNode *y = x->dir;
    x->dir = y->esq;
    y->esq = x;
    x->altura = 1 + max(alturaAVL(x->esq), alturaAVL(x->dir));
    y->altura = 1 + max(alturaAVL(y->esq), alturaAVL(y->dir));
    return y;
}

static AVLNode *balancearAVL(AVLNode *n) {
    if (!n) return n;
    int fb = alturaAVL(n->esq) - alturaAVL(n->dir);

    if (fb > 1) {                       /* pesado à esquerda */
        if (alturaAVL(n->esq->esq) < alturaAVL(n->esq->dir))
            n->esq = rotEsq(n->esq);    /* dupla esq-dir */
        n = rotDir(n);
    } else if (fb < -1) {               /* pesado à direita */
        if (alturaAVL(n->dir->dir) < alturaAVL(n->dir->esq))
            n->dir = rotDir(n->dir);    /* dupla dir-esq */
        n = rotEsq(n);
    }
    return n;
}

static AVLNode *inserirAVL(AVLNode *n, int k) {
    if (!n) return novoAVL(k);
    if (k < n->chave)       n->esq = inserirAVL(n->esq, k);
    else if (k > n->chave)  n->dir = inserirAVL(n->dir, k);
    else                    return n;         /* chaves únicas */

    n->altura = 1 + max(alturaAVL(n->esq), alturaAVL(n->dir));
    return balancearAVL(n);
}

/* ---------- Árvore Vermelho-Preta ---------- */
static RBNode *NULO;        /* sentinela preta */

static RBNode *novoRB(int k) {
    RBNode *n = (RBNode *)malloc(sizeof(RBNode));
    n->chave = k; n->cor = VERMELHO;
    n->esq = n->dir = n->pai = NULO;
    return n;
}

/* incrementa corRB apenas se a cor realmente mudar */
static inline void recolor(RBNode *n, Cor nova) {
    if (n->cor != nova) {
        n->cor = nova;
        corRB++;
    }
}

static void rotEsqRB(RBNode **raiz, RBNode *x) {
    rotRB++;
    RBNode *y = x->dir;
    x->dir = y->esq;
    if (y->esq != NULO) y->esq->pai = x;
    y->pai = x->pai;
    if (x->pai == NULO)        *raiz = y;
    else if (x == x->pai->esq) x->pai->esq = y;
    else                       x->pai->dir = y;
    y->esq = x;
    x->pai = y;
}

static void rotDirRB(RBNode **raiz, RBNode *y) {
    rotRB++;
    RBNode *x = y->esq;
    y->esq = x->dir;
    if (x->dir != NULO) x->dir->pai = y;
    x->pai = y->pai;
    if (y->pai == NULO)        *raiz = x;
    else if (y == y->pai->dir) y->pai->dir = x;
    else                       y->pai->esq = x;
    x->dir = y;
    y->pai = x;
}

static void corrigirRB(RBNode **raiz, RBNode *z) {
    while (z->pai->cor == VERMELHO) {
        if (z->pai == z->pai->pai->esq) {
            RBNode *y = z->pai->pai->dir;
            if (y->cor == VERMELHO) {          /* caso 1 */
                recolor(z->pai,      PRETO);
                recolor(y,           PRETO);
                recolor(z->pai->pai, VERMELHO);
                z = z->pai->pai;
            } else {
                if (z == z->pai->dir) {        /* caso 2 */
                    z = z->pai;
                    rotEsqRB(raiz, z);
                }                              /* caso 3 */
                recolor(z->pai,      PRETO);
                recolor(z->pai->pai, VERMELHO);
                rotDirRB(raiz, z->pai->pai);
            }
        } else {                               /* simétrico */
            RBNode *y = z->pai->pai->esq;
            if (y->cor == VERMELHO) {
                recolor(z->pai,      PRETO);
                recolor(y,           PRETO);
                recolor(z->pai->pai, VERMELHO);
                z = z->pai->pai;
            } else {
                if (z == z->pai->esq) {
                    z = z->pai;
                    rotDirRB(raiz, z);
                }
                recolor(z->pai,      PRETO);
                recolor(z->pai->pai, VERMELHO);
                rotEsqRB(raiz, z->pai->pai);
            }
        }
    }
    recolor(*raiz, PRETO);  /* garante raiz preta */
}

static void inserirRB(RBNode **raiz, int k) {
    RBNode *z = novoRB(k);
    RBNode *y = NULO, *x = *raiz;

    while (x != NULO) {
        y = x;
        if (k < x->chave)            x = x->esq;
        else if (k > x->chave)       x = x->dir;
        else { free(z); return; }    /* chaves únicas */
    }

    z->pai = y;
    if (y == NULO)        *raiz = z;
    else if (k < y->chave) y->esq = z;
    else                   y->dir = z;

    corrigirRB(raiz, z);
}

/* ---------- Alturas ---------- */
static int alturaNodoRB(RBNode *n) {
    if (n == NULO) return -1;
    int a = alturaNodoRB(n->esq);
    int b = alturaNodoRB(n->dir);
    return 1 + (a > b ? a : b);
}

static int alturaNegra(RBNode *n) {
    if (n == NULO) return 0;
    int a = alturaNegra(n->esq);
    int b = alturaNegra(n->dir);
    int maior = a > b ? a : b;
    return maior + (n->cor == PRETO);
}

/* ---------- Liberação ---------- */
static void liberaAVL(AVLNode *n) {
    if (!n) return;
    liberaAVL(n->esq);
    liberaAVL(n->dir);
    free(n);
}
static void liberaRB(RBNode *n) {
    if (n == NULO) return;
    liberaRB(n->esq);
    liberaRB(n->dir);
    free(n);
}

/* ---------- Main ---------- */
int main(void) {
    /* cria sentinela preto */
    NULO = (RBNode *)malloc(sizeof(RBNode));
    NULO->cor = PRETO; NULO->esq = NULO->dir = NULO->pai = NULO;

    AVLNode *avl = NULL;
    RBNode  *rb  = NULO;

    int v;
    while (scanf("%d", &v) == 1 && v >= 0) {
        avl = inserirAVL(avl, v);
        inserirRB(&rb, v);
    }

    /* Alturas AVL */
    int h_avl  = avl ? avl->altura : -1;
    int he_avl = (avl && avl->esq) ? avl->esq->altura : -1;
    int hd_avl = (avl && avl->dir) ? avl->dir->altura : -1;

    /* Alturas RB */
    int h_rb   = alturaNodoRB(rb);
    int he_rb  = (rb->esq != NULO) ? alturaNodoRB(rb->esq) : -1;
    int hd_rb  = (rb->dir != NULO) ? alturaNodoRB(rb->dir) : -1;

    /* Altura negra RB */
    int hn_rb  = alturaNegra(rb);

    /* Saída */
    printf("%d, %d, %d\n", h_avl, he_avl, hd_avl);
    printf("%d, %d, %d\n", h_rb,  he_rb,  hd_rb);
    printf("%d\n", hn_rb);
    printf("%ld, %ld, %ld\n", corRB, rotRB, rotAVL);

    /* limpeza */
    liberaAVL(avl);
    liberaRB(rb);
    free(NULO);
    return 0;
}
