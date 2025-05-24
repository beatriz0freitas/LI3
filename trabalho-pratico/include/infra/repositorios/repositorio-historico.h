/**
 * @file repositorio-historico.h
 * @brief Declarações de funções e estruturas relacionadas ao repositório de históricos.
 *
 * Este arquivo contém as definições da estrutura `RepositorioHistoricos` e as funções
 * associadas para gerenciar os históricos de utilização.
 */

#ifndef REPOSITORIO_HISTORICO_H
#define REPOSITORIO_HISTORICO_H

#include "historico.h"
#include "musica.h"
#include <glib.h>

/**
 * @brief Estrutura que representa o repositório de históricos.
 */
typedef struct RepositorioHistoricos RepositorioHistoricos;

/**
 * @brief Cria um novo repositório de históricos.
 *
 * @return Apontador para uma nova instância de `RepositorioHistoricos`.
 */
RepositorioHistoricos *repositorio_historicos_novo();

/**
 * @brief Destroi o repositório de históricos.
 *
 * Liberta toda a memória associada ao repositório e seus elementos.
 *
 * @param repo Apontador para o repositório a ser destruído.
 */
void repositorio_historicos_destroi(RepositorioHistoricos *repo);

/**
 * @brief Adiciona um histórico ao repositório.
 *
 * Adiciona um registo de histórico ao repositório, associando-o ao utilizador e ao ano correspondente.
 *
 * @param repo Apontador para o repositório.
 * @param historico Apontador para o histórico a ser adicionado.
 */
void repositorio_historicos_adicionar(RepositorioHistoricos *repo, Historico *historico);


/**
 * @brief Obtém históricos por utilizador e ano.
 *
 * Recupera um array de históricos associados a um utilizador e a um ano específicos.
 *
 * @param repo Apontador para o repositório.
 * @param userID ID do utilizador.
 * @param ano Ano dos históricos desejados.
 * @return Apontador para um `GArray` contendo os históricos ou `NULL` se não houver registos.
 */
GArray *repositorio_historicos_get_por_utilizador_e_ano(RepositorioHistoricos *repo, int userID, int ano);

#endif // REPOSITORIO_HISTORICO_H
