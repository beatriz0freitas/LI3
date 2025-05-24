#ifndef RESULTADO_QUERY_H
#define RESULTADO_QUERY_H

/**
 * @file resultado-query.h
 * @brief Declarações de funções e estruturas para manipulação de resultados de consultas.
 * 
 * Este arquivo define as funções e estruturas necessárias para a criação, manipulação e
 * destruição de resultados de consultas. O resultado de uma consulta é representado por um
 * conjunto de linhas e células, onde cada célula é uma string.
 * 
 * @todo Confirmar se os includes são necessários.
 */

#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "comando.h"

/**
 * @struct ResultadoQuery
 * @brief Estrutura que representa um resultado de consulta (tabela).
 */
typedef struct ResultadoQuery ResultadoQuery;

/**
 * @struct Linha
 * @brief Estrutura que representa uma linha dentro de um resultado de consulta.
 */
typedef struct Linha Linha;

/**
 * @brief Cria um novo objeto ResultadoQuery.
 * 
 * Esta função aloca e inicializa uma nova instância de ResultadoQuery, representando uma
 * tabela vazia.
 * 
 * @return Um apontador para o novo ResultadoQuery.
 */
ResultadoQuery *resultado_query_novo();

/**
 * @brief Destroi um objeto ResultadoQuery.
 * 
 * Liberta a memória associada ao objeto ResultadoQuery e todas as suas 
 * estruturas internas, incluindo todas as suas linhas.
 * 
 * @param tabelaResposta Apontador para o objeto ResultadoQuery a ser destruído.
 */
void resultado_query_destroi(ResultadoQuery *tabelaResposta);

/**
 * @brief Adiciona uma linha ao ResultadoQuery.
 * 
 * Esta função adiciona uma linha (instância de Linha) ao objeto ResultadoQuery.
 * 
 * @param tabelaResposta Apontador para o objeto ResultadoQuery.
 * @param linha Apontador para a linha a ser adicionada.
 */
void resultado_query_adiciona_linha(ResultadoQuery *tabelaResposta, Linha *linha);

/**
 * @brief Cria uma nova Linha.
 * 
 * Esta função aloca e inicializa uma nova Linha, que representa uma linha de dados em
 * uma consulta.
 * 
 * @return Um apontador para a nova Linha.
 */
Linha *resultado_query_linha_novo();

/**
 * @brief Destroi uma Linha.
 * 
 * Liberta a memória associada a uma instância de Linha.
 * 
 * @param linha Apontador para a Linha a ser destruída.
 */
void resultado_query_linha_destroi(Linha *linha);

/**
 * @brief Adiciona uma célula à Linha.
 * 
 * Esta função adiciona uma célula (string) a uma Linha. As células representam os dados
 * em cada coluna da linha.
 * 
 * @param linha Apontador para a Linha.
 * @param celula A célula (string) a ser adicionada.
 */
void resultado_query_linha_adiciona_celula(Linha *linha, const char *celula);

/**
 * @brief Converte o ResultadoQuery em uma string.
 * 
 * Esta função converte o conteúdo do ResultadoQuery em uma string formatada, onde cada
 * linha é separada por uma nova linha e as células são separadas por um delimitador.
 * 
 * @param tabelaRespostas Apontador para o ResultadoQuery.
 * @param delimitador O delimitador que será utilizado para separar as células.
 * @return A string resultante da conversão que deve ser liberada pelo chamador com g_free().
 */
char *resultado_query_toString(void *tabelaRespostas, const char *delimitador);

/**
 * @brief Função de comparação para ordenar linhas.
 * 
 * Esta função é usada para ordenar as linhas de um ResultadoQuery com base num número
 * em ordem decrescente e, em caso de empate, por ordem alfabética.
 * 
 * @param a Apontador para a primeira linha a ser comparada.
 * @param b Apontador para a segunda linha a ser comparada.
 * @return Valor negativo se a < b, positivo se a > b, e zero se a == b.
 */
int compara_linhas_decrescente_alfabetico(const void* a, const void* b);

/**
 * @brief Ordena as linhas do ResultadoQuery.
 * 
 * Esta função ordena as linhas de um ResultadoQuery utilizando uma função de comparação
 * fornecida pelo usuário.
 * 
 * @param result Apontador para o ResultadoQuery a ser ordenado.
 * @param compare_func A função de comparação a ser utilizada.
 */
void resultado_query_ordena(ResultadoQuery *result, GCompareFunc compare_func);

#endif
