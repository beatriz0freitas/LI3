#include "gestor-query5.h"

ResultadoQuery *gestor_query5_executa(Comando *comando, Dados *dados)
{
    char *idUtilizadorAlvo = comando_get_argumento_por_indice(comando, 0);
    if (idUtilizadorAlvo == NULL || strlen(idUtilizadorAlvo) < 8) { 
        return NULL;
    }
    char* numeroRecomendacoesStr = comando_get_argumento_por_indice(comando, 1);
    if (numeroRecomendacoesStr == NULL) { 
        return NULL;
    }
    int numeroRecomendacoes = atoi(numeroRecomendacoesStr);

    ResultadoQuery *resultado = resultado_query_novo();
    int idUtilizador = atoi (&idUtilizadorAlvo[1]);

    RepositorioUtilizadores *repositorioUtilizadores = dados_get_repositorioUtilizadores(dados);

    gboolean utilizadorExiste = repositorio_utilizadores_existe(repositorioUtilizadores, idUtilizador);

    if (utilizadorExiste){

    int **matrizAudicoes = dados_get_audicoesUtilizadoresPorGenero(dados);
    char **ordemLinhasUtilizadores = repositorio_utilizadores_get_ordemLinhasUtilizadores(repositorioUtilizadores);
    char **ordemColunasGeneros = dados_get_ordemColunasGeneros(dados);
    int numUtilizadores = repositorio_utilizadores_get_proximoIndiceLinha(repositorioUtilizadores);
    int numGeneros = dados_get_proximoIndiceColuna(dados);

    char **recomendacoes = recomendaUtilizadores(
        idUtilizadorAlvo, 
        matrizAudicoes, 
        ordemLinhasUtilizadores, 
        ordemColunasGeneros, 
        numUtilizadores, 
        numGeneros, 
        numeroRecomendacoes
    );

    for (int j = 0; j < numeroRecomendacoes; j++) {
            Linha *linha = resultado_query_linha_novo();  
            resultado_query_linha_adiciona_celula(linha, recomendacoes[j]);
            resultado_query_adiciona_linha(resultado, linha);
        }

}
    g_free(idUtilizadorAlvo);
    g_free(numeroRecomendacoesStr);
    return resultado;
}
