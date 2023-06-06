#include <stdio.h>
#include <stdlib.h>

// Função para realizar a ordenação externa
void externalSort() {
    // Abrir o arquivo de entrada
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return;
    }

    // Criar um buffer para armazenar os elementos em memória
    int buffer[5];

    // Variável para contar o número de elementos lidos
    int count = 0;

    // Ler os elementos do arquivo de entrada
    while (!feof(inputFile)) {
        // Ler um elemento do arquivo
        int element;
        fscanf(inputFile, "%d", &element);

        // Armazenar o elemento no buffer
        buffer[count] = element;
        count++;

        // Se o buffer estiver cheio, ordenar e escrever no arquivo de saída
        if (count == 5) {
            // Ordenar o buffer (por exemplo, usando bubble sort)
            for (int i = 0; i < count - 1; i++) {
                for (int j = 0; j < count - i - 1; j++) {
                    if (buffer[j] > buffer[j + 1]) {
                        int temp = buffer[j];
                        buffer[j] = buffer[j + 1];
                        buffer[j + 1] = temp;
                    }
                }
            }

            // Abrir o arquivo de saída para escrita
            FILE *outputFile = fopen("output.txt", "a");
            if (outputFile == NULL) {
                printf("Erro ao abrir o arquivo de saída.\n");
                return;
            }

            // Escrever os elementos ordenados no arquivo de saída
            for (int i = 0; i < count; i++) {
                fprintf(outputFile, "%d ", buffer[i]);
            }

            // Fechar o arquivo de saída
            fclose(outputFile);

            // Reiniciar o contador e limpar o buffer
            count = 0;
            memset(buffer, 0, sizeof(buffer));
        }
    }

    // Fechar o arquivo de entrada
    fclose(inputFile);
}

// Função principal
int main() {
    // Chamar a função de ordenação externa
    externalSort();

    return 0;
}