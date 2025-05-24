#ifndef GESTOR_QUERY5_H
#define GESTOR_QUERY5_H

#include "repositorio-dados.h"
#include "resultado-query.h"
#include "recomendador.h"

/**
 * @brief Executa a Query 5, que gera recomendações de utilizadores
 *
 * Esta função executa a Query 5, que tem como objetivo gerar recomendações de utilizadores com base nas suas audições anteriores.
 * A recomendação é feita com base no histórico de audições e nas semelhanças entre os utilizadores.
 * O resultado é uma lista de utilizadores recomendados para o utilizador alvo.
 * 
 * @param comando Apontador para o comando que contém os argumentos da query.
 * @param dados Apontador para os dados que contêm informações sobre os utilizadores e as suas audições.
 * @return ResultadoQuery* Apontador para o objeto `ResultadoQuery` que contém a lista de utilizadores recomendados.
 */
ResultadoQuery *gestor_query5_executa(Comando *comando, Dados *dados);

#endif
