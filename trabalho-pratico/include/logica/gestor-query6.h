#ifndef GESTOR_QUERY6_H
#define GESTOR_QUERY6_H

#include "repositorio-dados.h"
#include "resultado-query.h"

/**
 * @brief Executa a Query 6, que analisa o histórico de um utilizador e fornece informações detalhadas
 *
 * Esta função executa a Query 6, que é projetada para analisar o histórico de audições de um utilizador específico e retornar informações detalhadas, como:
 * - Tempo total de audição
 * - Número total de músicas ouvidas
 * - Artista mais ouvido
 * - Álbum mais ouvido
 * - Hora mais ouvida
 * - Gênero mais ouvido
 * - Dia mais ouvido
 * Além disso, pode retornar uma lista de artistas mais ouvidos, dependendo do número de artistas especificado.
 * 
 * @param comando Apontador para o comando que contém os argumentos da query.
 * @param dados Apontador para os dados que contêm informações sobre os utilizadores e seus históricos de audição.
 * @return ResultadoQuery* Apontador para o objeto `ResultadoQuery` que contém os resultados da análise.
 */
ResultadoQuery *gestor_query6_executa(Comando *comando, Dados *dados);

#endif
