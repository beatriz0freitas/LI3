#include "gestor-de-programa.h"


int main(int argc, char *argv[]) {
    
    char *pastaDados = argv[1];
    char *caminhoFicheiroInput = argv[2];

    gboolean modoEconomiaMemoria = TRUE;

    if (argc > 3 && strcmp(argv[3], "normal") == 0){
        modoEconomiaMemoria = FALSE;
    }

    printf("Programa principal inicializado no modo %s\n", modoEconomiaMemoria ? "Economia de memória" : "Normal");

    GestorDePrograma *gestorPrograma = gestor_programa_novo(NULL, modoEconomiaMemoria);

    gestor_programa_executa(gestorPrograma, pastaDados, caminhoFicheiroInput);

    gestor_programa_destroi(gestorPrograma);

    return 0;
}