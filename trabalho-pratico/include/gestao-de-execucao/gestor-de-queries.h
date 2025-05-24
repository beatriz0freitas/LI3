/**
 * @file gestor-de-queries.h
 * @brief Declarações de funções e estruturas para gerir e executar queries.
 *
 * Este gestor contém as declarações de funções e estruturas de dados
 * usadas para gerir e executar queries.
 *
 * @note Este arquivo faz parte do projeto 2425.
 */

#ifndef GESTOR_DE_QUERIES_H
#define GESTOR_DE_QUERIES_H

#include "gestor-query1.h"
#include "gestor-query2.h"
#include "gestor-query3.h"
#include "gestor-query4.h"
#include "gestor-query5.h"
#include "gestor-query6.h"
#include "estatisticas.h"
#include "output.h"

/**
 * @brief Estrutura principal do gestor de queries.
 *
 * Estrutura responsável por gerir diferentes tipos de queries no sistema.
 */
typedef struct GestorDeQueries GestorDeQueries;

/**
 * @brief Função que faz o output do resultado da query
 * 
 * O tipo `FuncaoOutput` representa uma função que recebe uma estrutura, um delimitador, 
 * uma função que passa a estrutura para uma string e o número do comando executado, 
 * fazendo de seguida o output dessa string.
*/

typedef void (*FuncaoOutput)(void *structure, const char *delimitador, FuncaoToString funcao_ToString, int numeroDoComando);

/**
 * @brief Cria um novo de 'GestorDeQueries'.
 * 
 * Esta função inicializa e retorna um novo 'GestorDeQueries'.
 * 
 * @param estatisticas Pode receber uma estrutura de estatísticas quando usado pelo programa de testes 
 * ou receber NULL quando usado pelo programa principal.
 * 
 * @return Um apontador para o novo 'GestorDeQueries'.
 */
GestorDeQueries *gestor_queries_novo(Estatisticas *estatisticas);

/**
 * @brief Destrói um 'GestorDeQueries'.
 * 
 * Esta função dá free a 'GestorDeQueries'.
 * 
 * @param gestor Apontador para o 'GestorDeQueries' a ser destruído.
 */
void gestor_queries_destroi(GestorDeQueries *gestor);

/**
 * @brief Executa as queries.
 *
 * Esta função executa as queries dado um certo comando e faz as estatísticas da execução.
 *
 * @param gestorqueries Apontador para o 'GestorDeQueries'.
 * @param comando Apontador para o 'Comando' a ser executado.
 * @param dados Dados a serem usados.
 * 
 * @return Um apontador para a estrutura de 'ResultadoQuery'.
 */
ResultadoQuery *gestor_queries_executa(GestorDeQueries *gestorqueries, Comando *comando, Dados *dados);

/**
 * @brief Obtém as estatísticas associadas ao gestor de queries.
 *
 * Esta função retorna um apontador para a estrutura de estatísticas
 * associada ao gestor de queries.
 *
 * @param gestorQueries Apontador para o 'GestorDeQueries'.
 * @return Um apontador para a estrutura de estatísticas.
 */
Estatisticas *gestor_queries_get_estatisticas (GestorDeQueries *gestorQueries);

#endif