#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <gtk/gtk.h>

void startSolve(GtkWidget *solve, gpointer data);
void printBoard(int board[9][9]);
bool solveBoard(int board[9][9]);
GtkWidget *entries[9][9], *window;

static int board[9][9] =    {{1, 0, 0, 4, 0, 2, 8, 0, 0},
                            {8, 2, 0, 6, 0, 0, 0, 0, 4},
                            {7, 3, 4, 0, 5, 0, 0, 0, 0},
                            {2, 4, 0, 5, 0, 0, 3, 0, 0},
                            {0, 0, 3, 0, 0, 0, 2, 0, 0},
                            {0, 0, 1, 0, 0, 3, 0, 8, 5},
                            {0, 0, 0, 0, 9, 0, 1, 4, 8},
                            {9, 0, 0, 0, 0, 8, 0, 5, 6},
                            {0, 0, 8, 1, 0, 7, 0, 0, 2}};

int main(int argc, char **argv){

    printf("Starting board:\n");
    printBoard(board);

    /*
    if (!solveBoard(board)) printf("No Solution :(\n");
    else printBoard(board);
    */

    GtkWidget *grid, *innerGrid[9], *solve;

    gtk_init(&argc, &argv);

    //creating main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //creating grid
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    /*
    //initialize inner 3x3 grids
    int counter = 0;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            innerGrid[counter] = gtk_grid_new();
            gtk_grid_attach(GTK_GRID(grid), innerGrid[counter], i, j, 1, 1);
            gtk_container_add(GTK_CONTAINER(window), grid);
            counter++;
        }
    }
    */

    //initialize entries in inner 3x3 grids
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            entries[i][j] = gtk_entry_new();
            gtk_entry_set_width_chars(GTK_ENTRY(entries[i][j]), 1);
            gtk_entry_set_max_length(GTK_ENTRY(entries[i][j]), 1);
            gtk_widget_set_size_request(entries[i][j], 20, 20);
            gtk_grid_attach(GTK_GRID(grid), entries[i][j], j, i, 1, 1);
        }
    }
    
    
    
    solve = gtk_button_new_with_label("Solve Board");
    g_signal_connect(solve, "clicked", G_CALLBACK(startSolve), NULL);
    gtk_grid_attach(GTK_GRID(grid), solve, 10, 0, 1, 1);
    

    gtk_widget_show_all(window);
    gtk_main();

    return 0;

}

void startSolve(GtkWidget *solve, gpointer data){
    GtkWidget *alert;

    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            board[i][j] = atoi((char *) gtk_entry_get_text(GTK_ENTRY(entries[i][j])));
        }
    }

    if (solveBoard(board)){
        char buffer[2];
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++){
                snprintf(buffer, sizeof(buffer), "%d", board[i][j]);
                gtk_entry_set_text(GTK_ENTRY(entries[i][j]), buffer);
            }
        }
    }   else{
        printf("..\n");
        alert = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Invalid Sudoku board :(");
        gtk_dialog_run(GTK_DIALOG(alert));
        gtk_widget_destroy(alert);
    }
}