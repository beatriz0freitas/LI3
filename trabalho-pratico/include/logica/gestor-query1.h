/**
 * @file gestor-query1.h
 * @brief Declarações de funções e estrutura para o gerenciamento e execução da Query1.
 *
 * Este gestor é responsável por gerir e executar a Query1, que consiste em obter
 * os dados de um utilizador a partir do seu ID.
 */
#ifndef GESTOR_QUERY1_H
#define GESTOR_QUERY1_H

#include "repositorio-dados.h"
#include "resultado-query.h"

/**
 * @brief Executa a Query1.
 * 
 * @param comando Apontador para o 'Comando' a ser executado.
 * @param dados Apontador para os `Dados`.
 * @return O resultado da execução da Query1.
 */
ResultadoQuery *gestor_query1_executa(Comando *comando, Dados *dados);

#endif