#ifndef DATA_H
#define DATA_H

#include <gtk/gtk.h>

// Códigos dos funcionários
#define NILTON 123
#define RAQUEL 456
#define JAMILE 789

#define NUM_FUNCIONARIOS 3
#define NUM_ENTRADAS 17
#define NUM_SAIDAS 10
#define NUM_BOTOES 2

#define SPACING 3

// Tipos para entradas e saídas
typedef struct {
    float valores[NUM_ENTRADAS]; // 17 tipos diferentes de entrada
} Entrada;

typedef struct {
    float valores[NUM_SAIDAS]; // 10 tipos diferentes de saída
} Saida;

extern Entrada entrada[NUM_FUNCIONARIOS];
extern Saida saida[NUM_FUNCIONARIOS];

extern int codigo_autenticado;

// Array de nomes dos funcionários e seus índices correspondentes
extern char* nomes[NUM_FUNCIONARIOS];
extern int codigos[NUM_FUNCIONARIOS];

extern char* labels_entrada_text[];
extern char* labels_saida_text[];
extern char* buttons_text[];

extern GtkWidget *window;
extern GtkWidget *grid;
extern GtkWidget *labels_entrada[NUM_ENTRADAS];
extern GtkWidget *entries_entrada[NUM_ENTRADAS];
extern GtkWidget *labels_saida[NUM_SAIDAS];
extern GtkWidget *entries_saida[NUM_SAIDAS];
extern GtkWidget *buttons[NUM_BOTOES];
extern GtkWidget *entry_codigo;

void ativarCampos(int codigo);
int autenticarFuncionario(int codigo);

#endif // DATA_H

