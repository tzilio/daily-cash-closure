#include <gtk/gtk.h>
#include "data.h"
#include "user_file.h"

void button_clicked(GtkWidget *widget, gpointer data) {
    int button_index = GPOINTER_TO_INT(data);
    int codigo = atoi(gtk_entry_get_text(GTK_ENTRY(entry_codigo)));

    if (button_index == 0) {
        codigo_autenticado = autenticarFuncionario(codigo);
        if (codigo_autenticado == -1) {
            printf("Código de funcionário inválido!\n");
        } else {
            ativarCampos(codigo);
            printf("Autenticado como %s\n", nomes[codigo_autenticado]);
        }
    } else if (button_index == 1) {
        coletarDadosFuncionario(codigo);
    }
}
