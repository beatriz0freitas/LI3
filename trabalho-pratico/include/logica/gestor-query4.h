#ifndef GESTOR_QUERY4_H
#define GESTOR_QUERY4_H

#include "repositorio-dados.h"
#include "resultado-query.h"

/**
 * @brief Executa a Query 4 e retorna o resultado com o artista mais frequente
 *
 * Esta função executa a Query 4, que calcula o artista mais frequente que apareceu no top 10 durante um período de semanas.
 * Ela gera um objeto ResultadoQuery que contém a informação do artista mais frequente e sua respectiva contagem de aparições.
 * 
 * @param comando Apontador para o 'Comando' a ser executado.
 * @return ResultadoQuery* Apontador para o objeto ResultadoQuery com o artista mais frequente no top 10
 */
ResultadoQuery *gestor_query4_executa(Comando *comando, Dados *dados);

#endif
