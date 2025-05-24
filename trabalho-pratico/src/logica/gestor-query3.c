#include "gestor-query3.h"

#define IDADE_MAXIMA 120

ResultadoQuery *gestor_query3_executa(Comando *comando, Dados *dados) {
    char *idadeMinimaStr = comando_get_argumento_por_indice(comando, 0);
        if (idadeMinimaStr == NULL) { 
        return NULL;
    }
    int idadeMinima = atoi(idadeMinimaStr);
    g_free(idadeMinimaStr);

    char *idadeMaximaStr = comando_get_argumento_por_indice(comando, 1);
    if (idadeMaximaStr == NULL) { 
        return NULL;
    }
    int idadeMaxima = atoi(idadeMaximaStr);
    g_free(idadeMaximaStr);

    ResultadoQuery *resultado = resultado_query_novo();

    GenerosIterador *iterador = generos_iterador_novo(dados);

    Quark generoQuark;
    GArray *array;
    int totalLikesFaixaEtaria = 0;

    while (generos_iterador_proximo(iterador, &generoQuark, &array)) {
        int totalLikesFaixaEtariaGenero = 0;
        for (int i = idadeMinima; i <= idadeMaxima && i < IDADE_MAXIMA; i++) {
            totalLikesFaixaEtariaGenero += g_array_index(array, int, i);
        }
        totalLikesFaixaEtaria += totalLikesFaixaEtariaGenero;

        Linha *linha = resultado_query_linha_novo();
        char *likes = g_strdup_printf("%d", totalLikesFaixaEtariaGenero);

        resultado_query_linha_adiciona_celula(linha, string_de_quark(generoQuark));
        resultado_query_linha_adiciona_celula(linha, likes);

        resultado_query_adiciona_linha(resultado, linha);
        g_free(likes);
    }

    generos_iterador_destroi(iterador);

    if (totalLikesFaixaEtaria == 0) {
        resultado_query_destroi(resultado);
        return NULL;
    }

    resultado_query_ordena(resultado, compara_linhas_decrescente_alfabetico);
    return resultado;
}

