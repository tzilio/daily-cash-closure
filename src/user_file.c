#include "user_file.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <sys/stat.h> // Para mkdir

void salvarRelatorioFuncionario(int index) {
    // Verificar se o index está dentro do intervalo válido
    if (index < 0 || index >= NUM_FUNCIONARIOS) {
        fprintf(stderr, "Index %d fora do intervalo válido.\n", index);
        return;
    }

    // Nome do arquivo para salvar os dados
    char filename[100];
    snprintf(filename, sizeof(filename), "reports/%s.csv", nomes[index]);

    // Garantir que o diretório existe
    struct stat st = {0};
    if (stat("reports", &st) == -1) {
        if (mkdir("reports", 0700) != 0) {
            fprintf(stderr, "Não foi possível criar o diretório 'reports'.\n");
            return;
        }
    }

    // Abrir o arquivo para escrita
    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Não foi possível abrir o arquivo %s para escrita.\n", filename);
        return;
    }

    // Escrever o nome do funcionário
    fprintf(file, "%s\n\n", nomes[index]);

    // Escrever o cabeçalho
    fprintf(file, "Tipo;Descrição;Valor\n");

    // Escrever os dados de entrada no arquivo
    for (int i = 0; i < 17; i++) {
        fprintf(file, "Entrada;%s;%.2f\n", labels_entrada_text[i], entrada[index].valores[i]);
    }

    // Escrever os dados de saída no arquivo
    for (int i = 0; i < 10; i++) {
        fprintf(file, "Saída;%s;%.2f\n", labels_saida_text[i], saida[index].valores[i]);
    }

    // Calcular e escrever o total no arquivo
    float total_entrada = 0;
    float total_saida = 0;
    for (int i = 0; i < 17; i++) {
        total_entrada += entrada[index].valores[i];
    }
    for (int i = 0; i < 10; i++) {
        total_saida += saida[index].valores[i];
    }
    float saldo_total = total_entrada - total_saida;

    fprintf(file, "Total de Entrada;;%.2f\n", total_entrada);
    fprintf(file, "Total de Saída;;%.2f\n", total_saida);
    fprintf(file, "Saldo Total;;%.2f\n", saldo_total);

    // Fechar o arquivo
    fclose(file);
}

