/**
 * @file gestor-query2.h
 * @brief Declarações de funções e estrutura para o gerenciamento e execução da Query2.
 *
 * Este arquivo define a estrutura `GestorQuery2` e as funções associadas para criar, destruir,
 * e executar consultas do tipo Query2.
 */
#ifndef GESTOR_QUERY2_H
#define GESTOR_QUERY2_H

#include "repositorio-dados.h"
#include "resultado-query.h"

/**
 * @brief Executa a Query2.
 * 
 * @param comando Apontador para o 'Comando' a ser executado.
 * @param dados Apontador para os `Dados`.
 * @return O resultado da execução da Query2.
 */
ResultadoQuery* gestor_query2_executa(Comando *comando, Dados *dados);

#endif