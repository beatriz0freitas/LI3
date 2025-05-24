/**
 * @file gestor-query3.h
 * @brief Declarações de funções e estrutura para o gerenciamento e execução da Query3.
 *
 * Este arquivo define a estrutura `GestorQuery3` e as funções associadas para criar, destruir,
 * e executar consultas do tipo Query3.
 */
#ifndef GESTOR_QUERY3_H
#define GESTOR_QUERY3_H

#include "repositorio-dados.h"
#include "resultado-query.h"

/**
 * @brief Executa a Query3.
 * 
 * 
 * @param comando Apontador para o 'Comando' a ser executado.
 * @return Um apontador para o resultado da Query3, ou `NULL` se ocorrer algum erro.
 */
ResultadoQuery* gestor_query3_executa(Comando *comando, Dados* dados);

#endif