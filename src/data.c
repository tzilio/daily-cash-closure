#include "data.h"
#include "user_file.h"

Entrada entrada[3];
Saida saida[3];

int codigo_autenticado = -1;

char* nomes[] = {"Nilton", "Raquel", "Jamile"};
int codigos[] = {NILTON, RAQUEL, JAMILE};

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

char* buttons_text[] = {"Autenticar", "Coletar Dados"};

GtkWidget *window;
GtkWidget *grid;
GtkWidget *labels_entrada[17];
GtkWidget *entries_entrada[17];
GtkWidget *labels_saida[10];
GtkWidget *entries_saida[10];
GtkWidget *buttons[2];
GtkWidget *entry_codigo;


void ativarCampos(int codigo) {
    // Ativa ou desativa os campos de entrada com base no código do funcionário
    gboolean isFuncionario = (codigo == NILTON || codigo == RAQUEL || codigo == JAMILE);
    for (int i = 0; i < 17; i++) {
        gtk_widget_set_sensitive(entries_entrada[i], isFuncionario);
    }
    for (int i = 0; i < 10; i++) {
        gtk_widget_set_sensitive(entries_saida[i], isFuncionario);
    }
}

int autenticarFuncionario(int codigo) {
    switch (codigo) {
        case NILTON: return 0;
        case RAQUEL: return 1;
        case JAMILE: return 2;
        default: return -1;
    }
}

void coletarDadosFuncionario(int codigo) {
    if (codigo_autenticado == -1) {
        printf("Você precisa autenticar primeiro!\n");
        return;
    }

    int index = -1;

    // Encontrar o índice correto no array
    for (int i = 0; i < sizeof(codigos) / sizeof(codigos[0]); i++) {
        if (codigos[i] == codigo) {
            index = i;
            break;
        }
    }

    // Verificar se o código é válido
    if (index == -1) {
        printf("Código de funcionário inválido!\n");
        return;
    }

    // Ler valores dos campos de entrada
    for (int i = 0; i < 17; i++) {
        entrada[index].valores[i] = atof(gtk_entry_get_text(GTK_ENTRY(entries_entrada[i])));
    }
    for (int i = 0; i < 10; i++) {
        saida[index].valores[i] = atof(gtk_entry_get_text(GTK_ENTRY(entries_saida[i])));
    }

    salvarRelatorioFuncionario(index);

    // Fechar janela após coleta dos dados
    gtk_widget_destroy(window);
}
