#include <stdio.h>
#include <stdlib.h>

//ERRADO

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

// Função para obter a altura de um nó
int height(Node *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Função para calcular o máximo entre dois números
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Função para criar um novo nó
Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Função para realizar rotação à direita
Node* rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Função para realizar rotação à esquerda
Node* leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Função para obter o fator de balanceamento de um nó
int getBalance(Node *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Função para inserir um nó na árvore AVL
Node* insert(Node* node, int key) {
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Casos de desbalanceamento

    // Esquerda-Esquerda
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Direita-Direita
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Esquerda-Direita
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Direita-Esquerda
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Função para encontrar o nó com valor mínimo
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Função para remover um nó da árvore AVL
Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;

            free(temp);
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // Casos de desbalanceamento

    // Esquerda-Esquerda
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Esquerda-Direita
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Direita-Direita
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Direita-Esquerda
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Função para pesquisar um valor na árvore
Node* search(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (root->key < key)
        return search(root->right, key);

    return search(root->left, key);
}

// Função para imprimir nós em um intervalo
void printRange(Node* root, int k1, int k2, int* found) {
    if (root == NULL)
        return;

    if (k1 < root->key)
        printRange(root->left, k1, k2, found);

    if (k1 <= root->key && root->key <= k2) {
        if (*found > 0)
            printf(", ");
        printf("%d", root->key);
        (*found)++;
    }

    if (k2 > root->key)
        printRange(root->right, k1, k2, found);
}

// Função para coletar nós em um intervalo
void collectRange(Node* root, int k1, int k2, Node** nodes, int* count) {
    if (root == NULL)
        return;

    if (k1 < root->key)
        collectRange(root->left, k1, k2, nodes, count);

    if (k1 <= root->key && root->key <= k2) {
        nodes[*count] = root;
        (*count)++;
    }

    if (k2 > root->key)
        collectRange(root->right, k1, k2, nodes, count);
}

// Função para liberar a memória da árvore
void freeTree(Node* root) {
    if (root == NULL)
        return;
    
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Função principal
int main() {
    Node *root = NULL;
    int num;
    
    // Leitura da primeira linha (construção inicial da árvore)
    while (1) {
        scanf("%d", &num);
        if (num < 0) break;
        root = insert(root, num);
    }
    
    // Saída 1: altura da árvore após primeira linha
    if (root != NULL) {
        printf("%d, %d, %d\n", root->height-1, height(root->left)-1, height(root->right)-1);
    } else {
        printf("ARVORE VAZIA\n");
    }
    
    // Leitura da segunda linha (operações de pesquisa/inserção/remoção)
    while (1) {
        scanf("%d", &num);
        if (num < 0) break;
        
        Node* found = search(root, num);
        if (found != NULL) {
            root = deleteNode(root, num);
        } else {
            root = insert(root, num);
        }
    }
    
    // Saída 2: altura da árvore após segunda linha
    if (root != NULL) {
        printf("%d, %d, %d\n", root->height-1, height(root->left)-1, height(root->right)-1);
    } else {
        printf("ARVORE VAZIA\n");
    }
    
    // Leitura da terceira linha (faixa de pesquisa)
    int k1, k2;
    scanf("%d %d", &k1, &k2);
    
    // Ajuste se k1 > k2
    if (k1 > k2) {
        int temp = k1;
        k1 = k2;
        k2 = temp;
    }
    
    // Saída 3: nós no intervalo
    int found = 0;
    printRange(root, k1, k2, &found);
    if (found == 0) {
        printf("NADA A EXIBIR");
    } else {
        printf("\n");
        
        // Coletar nós no intervalo para imprimir suas alturas
        Node* nodes[1000];
        int count = 0;
        collectRange(root, k1, k2, nodes, &count);
        
        for (int i = 0; i < count; i++) {
            Node* node = nodes[i];
            printf("%d, %d, %d\n", node->height-1, height(node->left)-1, height(node->right)-1);
        }
    }
    
    // Liberar memória
    freeTree(root);
    
    return 0;
}