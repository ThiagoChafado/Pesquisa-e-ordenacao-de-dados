#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estruturado nó
struct Node {
    char data;
    unsigned int frequencia;
    struct Node* left;
    struct Node* right;
};

// Função para criar um novo nó da árvore de Huffman
struct Node* createNode(char data, unsigned int frequencia) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->frequencia = frequencia;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Função para trocar a posição de dois nós na floresta
void swapNodes(struct Node** a, struct Node** b) {
    struct Node* temp = *a;
    *a = *b;
    *b = temp;
}

// Função para ordenar a lista de árvores em ordem crescente de frequência
void sortForest(struct Node** forest, int size) {
    int i, j;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (forest[j]->frequencia > forest[j + 1]->frequencia) {
                swapNodes(&forest[j], &forest[j + 1]);
            }
        }
    }
}

// Função para unir duas árvores e criar uma nova árvore
struct Node* mergeTrees(struct Node* left, struct Node* right) {
    struct Node* newNode = createNode('\0', left->frequencia + right->frequencia);
    newNode->left = left;
    newNode->right = right;
    return newNode;
}

// Função para construir a árvore de Huffman
struct Node* buildHuffmanTree(char* text) {
    int frequencies[256] = {0}; // Array para armazenar as frequências de cada caractere
    int i;

    // Contar a frequência de cada caractere no texto
    for (i = 0; text[i] != '\0'; i++) {
        frequencies[(int)text[i]]++;
    }

    // Montar a floresta inicial com árvores unitárias
    struct Node** forest = (struct Node**)malloc(256 * sizeof(struct Node*));
    int forestSize = 0;
    for (i = 0; i < 256; i++) {
        if (frequencies[i] > 0) {
            forest[forestSize++] = createNode((char)i, frequencies[i]);
        }
    }

    // Ordenar a lista de árvores em ordem crescente de frequência
    sortForest(forest, forestSize);

    // Unir todas as árvores até formar uma única árvore
    while (forestSize > 1) {
        // Selecionar as duas árvores com as menores frequências
        struct Node* smallest1 = forest[0];
        struct Node* smallest2 = forest[1];

        // Criar uma nova árvore combinando as duas árvores selecionadas
        struct Node* mergedTree = mergeTrees(smallest1, smallest2);

        // Realocar a nova árvore no conjunto de árvores, mantendo a ordenação
        forest[0] = mergedTree;
        forest[1] = forest[forestSize - 1];
        forestSize--;

        sortForest(forest, forestSize);
    }

    // A árvore final é a raiz da árvore de Huffman
    struct Node* huffmanTree = forest[0];

    // Liberar memória
    free(forest);

    return huffmanTree;
}

// Função para imprimir os códigos de Huffman
void printHuffmanCodes(struct Node* root, int* code, int depth) {
    if (root->left == NULL && root->right == NULL) {
        int i;
        printf("%c: ", root->data);
        for (i = 0; i < depth; i++) {
            printf("%d", code[i]);
        }
        printf("\n");
    }
    else {
        code[depth] = 0;
        printHuffmanCodes(root->left, code, depth + 1);

        code[depth] = 1;
        printHuffmanCodes(root->right, code, depth + 1);
    }
}


/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do Nó da árvore
struct Node {
    char data;
    unsigned frequencia;
    struct Node* left, * right;
};


int main() {
    char input[100];

    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';  // remove o caractere de nova linha

    return 0;
}*/
int main() {
    char input[100];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    struct Node* huffmanTree = buildHuffmanTree(input);

    int code[256];
    int depth = 0;

    
    printHuffmanCodes(huffmanTree, code, depth);
    

    return 0;
}
