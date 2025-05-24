#include "output.h"

void output_print(void *estrutura, const char *delimitador, FuncaoToString funcao_ToString, int numeroDoCommando) {

    char nomeFicheiro[256];
    snprintf(nomeFicheiro, sizeof(nomeFicheiro), "resultados/command%d_output.txt", numeroDoCommando);
    FILE *file = fopen(nomeFicheiro, "w");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro de saída\n");
        return;
    }

    if (estrutura != NULL) {
        char *structureStr = funcao_ToString(estrutura, delimitador);
        fprintf(file, "%s\n", structureStr);
        g_free(structureStr);
    } else {
        fprintf(file, "\n");
    }
    fclose(file);
}

void output_terminal(void *estrutura, const char *delimitador, FuncaoToString funcao_ToString, int numeroDaQuery) {
    
    int altura = 20, largura = 80;
    int starty = (LINES - altura) / 2;
    int startx = (COLS - largura) / 2;

    WINDOW *janela = newwin(altura, largura, starty, startx);

    wclear(janela);  
    box(janela, 0, 0); 

    if (estrutura != NULL) {
        mvwprintw(janela, 2, (largura/2) - 25, "-------------------------------------------------");
        mvwprintw(janela, 3, (largura/2) - 10 , "Resultado da Query %d:", numeroDaQuery);
        mvwprintw(janela, 4, (largura/2) - 25, "-------------------------------------------------");

        char *structureStr = funcao_ToString(estrutura, delimitador);
        if (strlen(structureStr) > 5) {
            mvwprintw(janela, 6, 2, "%s", structureStr);
            g_free(structureStr);
        } else {
        mvwprintw(janela, 2, 2, "O resultado da query %d nao pode ser exibido.", numeroDaQuery);
        mvwprintw(janela, 3, 2, "Erro nos dados inseridos. Nenhum resultado encontrado.");
    }
    } else {
        mvwprintw(janela, 2, 2, "O resultado da query %d nao pode ser exibido.", numeroDaQuery);
        mvwprintw(janela, 3, 2, "Erro nos dados inseridos. Nenhum resultado encontrado.");
    }

    wrefresh(janela);  
    wgetch(janela); 
    wclear(janela);     

    delwin(janela);  
}