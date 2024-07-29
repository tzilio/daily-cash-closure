#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MAX_FUNCIONARIOS 3 // Ajustado para o número de funcionários fornecido
#define MAX_LABELS_ENTRADA 17
#define MAX_LABELS_SAIDA 10
#define MAX_NOME_FUNCIONARIO 50
#define MAX_PATH 256

typedef struct {
    float valores[MAX_LABELS_ENTRADA];
} DadosEntrada;

typedef struct {
    float valores[MAX_LABELS_SAIDA];
} DadosSaida;

char* nomes[] = {"Nilton", "Raquel", "Jamile"};

char* labels_entrada_text[] = {
    "Dinheiro", "Cheque à Vista", "Boleto", "Rede Débito", "Rede Crédito", 
    "Rede Parcelado", "Deposito / PIX (Itaú)", "Deposito Outros Bancos", 
    "Mercado Livre", "Cheque à Prazo", "Cielo Débito", "Cielo Crédito", 
    "Cielo Parcelado", "Sicredi/Stone Débito", "Sicredi/Stone Crédito", 
    "Sicredi/Stone Parcelado", "Sicredi"
};

char* labels_saida_text[] = {
    "Pagamentos", "Motoboy Vandex", "Motoboy Batore", "Motoboy Paraiba", 
    "Motoboy Diversos", "Compras", "Água", "Frete", "Neiva", "Outros"
};

DadosEntrada entrada[MAX_FUNCIONARIOS];
DadosSaida saida[MAX_FUNCIONARIOS];

void lerDadosFuncionario(const char *filename, int index) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Não foi possível abrir o arquivo %s para leitura.\n", filename);
        return;
    }

    char line[256];
    fgets(line, sizeof(line), file);

    fgets(line, sizeof(line), file); // Ler a linha em branco
    fgets(line, sizeof(line), file); // Ler o cabeçalho

    // Ler os dados de entrada
    for (int i = 0; i < MAX_LABELS_ENTRADA; i++) {
        if (fgets(line, sizeof(line), file)) {
            sscanf(line, "Entrada;%*[^;];%f", &entrada[index].valores[i]);
        }
    }

    // Ler os dados de saída
    for (int i = 0; i < MAX_LABELS_SAIDA; i++) {
        if (fgets(line, sizeof(line), file)) {
            sscanf(line, "Saída;%*[^;];%f", &saida[index].valores[i]);
        }
    }

    fclose(file);
}

void gerarRelatorioGeral(const char *filename, int dia, int mes, int ano) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Não foi possível criar o arquivo %s.\n", filename);
        return;
    }

    fprintf(file, "Relatório %d/%d/%d\n\n", dia, mes, ano);
    // Escrever o cabeçalho
    fprintf(file, "Tipo;Descrição;Valor\n");

    float total_entrada[MAX_LABELS_ENTRADA] = {0};
    float total_saida[MAX_LABELS_SAIDA] = {0};

    // Somar os dados de todos os funcionários
    for (int i = 0; i < MAX_FUNCIONARIOS; i++) {
        for (int j = 0; j < MAX_LABELS_ENTRADA; j++) {
            total_entrada[j] += entrada[i].valores[j];
        }
        for (int j = 0; j < MAX_LABELS_SAIDA; j++) {
            total_saida[j] += saida[i].valores[j];
        }
    }

    // Escrever os dados de entrada
    for (int i = 0; i < MAX_LABELS_ENTRADA; i++) {
        fprintf(file, "Entrada;%s;%.2f\n", labels_entrada_text[i], total_entrada[i]);
    }

    // Escrever os dados de saída
    for (int i = 0; i < MAX_LABELS_SAIDA; i++) {
        fprintf(file, "Saída;%s;%.2f\n", labels_saida_text[i], total_saida[i]);
    }

    // Calcular e escrever os totais
    float total_entrada_geral = 0;
    float total_saida_geral = 0;
    for (int i = 0; i < MAX_LABELS_ENTRADA; i++) {
        total_entrada_geral += total_entrada[i];
    }
    for (int i = 0; i < MAX_LABELS_SAIDA; i++) {
        total_saida_geral += total_saida[i];
    }

    float saldo_total = total_entrada_geral - total_saida_geral;

    fprintf(file, "Total de Entrada;;%.2f\n", total_entrada_geral);
    fprintf(file, "Total de Saída;;%.2f\n", total_saida_geral);
    fprintf(file, "Saldo Total;;%.2f\n", saldo_total);

    fclose(file);
}

void processarRelatorioGeral() {
    // Solicitar entrada do usuário
    int dia, mes, ano;
    printf("Digite o dia: ");
    scanf("%d", &dia);
    printf("Digite o mês: ");
    scanf("%d", &mes);
    printf("Digite o ano: ");
    scanf("%d", &ano);

    char filename[MAX_PATH];
    snprintf(filename, sizeof(filename), "relat_%02d_%02d_%04d.csv", dia, mes, ano);

    // Ler dados dos funcionários
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("reports")) != NULL) {
        int index = 0;
        while ((ent = readdir(dir)) != NULL) {
            if (strstr(ent->d_name, ".csv") != NULL) {
                char filepath[MAX_PATH];
                // Garantir que o tamanho da string não exceda o buffer
                if (snprintf(filepath, sizeof(filepath), "reports/%s", ent->d_name) >= sizeof(filepath)) {
                    fprintf(stderr, "O nome do arquivo %s é muito longo\n", ent->d_name);
                    continue;
                }
                lerDadosFuncionario(filepath, index++);
            }
        }
        closedir(dir);
    } else {
        fprintf(stderr, "Não foi possível abrir o diretório 'reports'.\n");
        return;
    }

    // Gerar o relatório geral
    gerarRelatorioGeral(filename, dia, mes, ano);
}

int main() {
    processarRelatorioGeral();
    return 0;
}

