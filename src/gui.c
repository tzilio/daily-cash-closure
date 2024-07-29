#include <gtk/gtk.h>
#include "callbacks.h"
#include "data.h"
#include "user_file.h"

void activate(GtkApplication *app, gpointer user_data) {
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "AZ ROLAMENTOS");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Espaçamento ao redor do grid
    gtk_container_set_border_width(GTK_CONTAINER(grid), 10);

    // Rótulo para "Código:"
    GtkWidget *label_codigo = gtk_label_new("Código:");
    gtk_widget_set_halign(label_codigo, GTK_ALIGN_START); // Alinhar à esquerda
    gtk_grid_attach(GTK_GRID(grid), label_codigo, 0, 0, 1, 1);

    // Entrada para o código do funcionário
    entry_codigo = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_codigo), "Código do funcionário");
    gtk_grid_attach(GTK_GRID(grid), entry_codigo, 1, 0, 1, 1);


    gtk_container_set_border_width(GTK_CONTAINER(window), 10);  // Define uma margem de 10 pixels ao redor da janela
    gtk_container_set_border_width(GTK_CONTAINER(grid), 10);  // Define uma margem de 10 pixels ao redor do grid

    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);  // Define o espaçamento vertical entre as linhas para 10 pixels
    gtk_grid_set_column_spacing(GTK_GRID(grid), 30);  // Define o espaçamento horizontal entre as colunas para 10 pixels


    // Adicionando o título "ENTRADA"
    GtkWidget *label_titulo_entrada = gtk_label_new("ENTRADA");
    gtk_widget_set_halign(label_titulo_entrada, GTK_ALIGN_START); // Alinhar ao centro horizontalmente
    gtk_grid_attach(GTK_GRID(grid), label_titulo_entrada, 0, 2, 1, 1);

    // Adicionando o título "SAÍDA"
    GtkWidget *label_titulo_saida = gtk_label_new("SAÍDA");
    gtk_widget_set_halign(label_titulo_saida, GTK_ALIGN_START); // Alinhar ao centro horizontalmente
    gtk_grid_attach(GTK_GRID(grid), label_titulo_saida, 2, 2, 1, 1); 

    // Adicionar campos de entrada
    for (int i = 0; i < 17; i++) {
        labels_entrada[i] = gtk_label_new(labels_entrada_text[i]);
        gtk_widget_set_halign(labels_entrada[i], GTK_ALIGN_START); // Alinhar à esquerda
        gtk_grid_attach(GTK_GRID(grid), labels_entrada[i], 0, i + SPACING, 1, 1);

        entries_entrada[i] = gtk_entry_new();
        gtk_entry_set_placeholder_text(GTK_ENTRY(entries_entrada[i]), "Insira o valor");
        gtk_grid_attach(GTK_GRID(grid), entries_entrada[i], 1, i + SPACING, 1, 1);
    }

    // Adicionar campos de saída
    for (int i = 0; i < 10; i++) {
        labels_saida[i] = gtk_label_new(labels_saida_text[i]);
        gtk_widget_set_halign(labels_saida[i], GTK_ALIGN_START); // Alinhar à esquerda
        gtk_grid_attach(GTK_GRID(grid), labels_saida[i], 2, i + SPACING, 1, 1);

        entries_saida[i] = gtk_entry_new();
        gtk_entry_set_placeholder_text(GTK_ENTRY(entries_saida[i]), "Insira o valor");
        gtk_grid_attach(GTK_GRID(grid), entries_saida[i], 3, i + SPACING, 1, 1);
    }

    // Botões para autenticar e coletar
    buttons[0] = gtk_button_new_with_label(buttons_text[0]);
    g_signal_connect(buttons[0], "clicked", G_CALLBACK(button_clicked), GINT_TO_POINTER(0));
    gtk_grid_attach(GTK_GRID(grid), buttons[0], 2, 0, 1, 1);

    buttons[1] = gtk_button_new_with_label(buttons_text[1]);
    g_signal_connect(buttons[1], "clicked", G_CALLBACK(button_clicked), GINT_TO_POINTER(1));
    gtk_grid_attach(GTK_GRID(grid), buttons[1], 3, 15, 1, 1);


    gtk_widget_show_all(window);
}
