#include "recomendador-implementacao.h"

// Estrutura auxiliar para associar distâncias aos índices
typedef struct {
    double distancia;
    int indice;
} DistanciaIndice;

// Função de comparação para ordem crescente de distância
static int compararDistancia(const void *a, const void *b) {
    double diff = ((DistanciaIndice *)a)->distancia - ((DistanciaIndice *)b)->distancia;
    return (diff > 0) - (diff < 0); // Retorna -1, 0, ou 1
}

// Função auxiliar para calcular a distância Euclidiana entre dois vetores
double recomendador_calcula_distancia(int *vetorA, int *vetorB, int tamanho) {
    double soma = 0;
    for (int i = 0; i < tamanho; i++) {
        double diferenca = vetorA[i] - vetorB[i];
        soma += diferenca * diferenca;
    }
    return sqrt(soma);
}

// Função auxiliar para encontrar o índice de um utilizador a partir do ID
int recomendador_encontra_indice_utilizador(char *idUtilizador, char **idsUtilizadores, int numUtilizadores) {
    for (int i = 0; i < numUtilizadores; i++) {
        if (strcmp(idUtilizador, idsUtilizadores[i]) == 0) {
            return i;
        }
    }
    return -1;
}

char **recomendaUtilizadores(char *idUtilizadorAlvo, int **matrizClassificacaoMusicas, char **idsUtilizadores,
                                    char **nomesGeneros, int numUtilizadores, int numGeneros, int numRecomendacoes){
    

    int indiceUtilizadorAlvo = recomendador_encontra_indice_utilizador(idUtilizadorAlvo, idsUtilizadores, numUtilizadores);
    if (indiceUtilizadorAlvo == -1) {
        return NULL; 
    }

    // Calcular a distância entre o utilizador alvo e os restantes utilizadores
    DistanciaIndice *distancias = malloc(numUtilizadores * sizeof(DistanciaIndice));
    for (int i = 0; i < numUtilizadores; i++) {
        if (i == indiceUtilizadorAlvo) {
            distancias[i].distancia = INFINITY; // Ignora o próprio utilizador
        } else {
            distancias[i].distancia = recomendador_calcula_distancia(matrizClassificacaoMusicas[indiceUtilizadorAlvo],
                                                        matrizClassificacaoMusicas[i],
                                                        numGeneros);
        }
        distancias[i].indice = i;
    }

    // Ordena as distâncias por ordem crescente
    qsort(distancias, numUtilizadores, sizeof(DistanciaIndice), compararDistancia);

    char **recomendacoes = malloc(numRecomendacoes * sizeof(char *));
    for (int r = 0; r < numRecomendacoes; r++) {
        recomendacoes[r] = idsUtilizadores[distancias[r].indice];
    }

    free(distancias);

    return recomendacoes;
}

                            
                            
