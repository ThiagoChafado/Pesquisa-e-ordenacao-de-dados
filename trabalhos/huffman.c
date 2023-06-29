#include <stdio.h>
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
}