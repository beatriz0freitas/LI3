/**
 * @file estatisticas.h
 * @brief Declarações de funções e estruturas para o módulo de estatísticas.
 *
 * Este módulo gere estatísticas relacionadas a diferentes itens, incluindo
 * contagem de execuções e tempo total de execução.
 */

#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <time.h>

/**
 * @brief Estrutura que gere estatísticas de múltiplos itens.
 */
typedef struct Estatisticas Estatisticas;

/**
 * @brief Estrutura que representa estatísticas de um único item.
 */
typedef struct EstatisticasItem EstatisticasItem;

/**
 * @brief Cria e inicializa um novo objeto de estatísticas.
 * 
 * @return Um apontador para uma nova instância de `Estatisticas`.
 */
Estatisticas *estatisticas_novo();

/**
 * @brief Liberta a memória associada a uma instância de `Estatisticas`.
 * 
 * @param estatisticas Apontador para a instância de `Estatisticas` a ser destruída.
 */
void estatisticas_destroi(Estatisticas *estatisticas);

/**
 * @brief Inicia a contagem de tempo para um item específico.
 * 
 * @param estatisticas Apontador para a instância de `Estatisticas`.
 * @param item Nome do item para o qual iniciar a contagem.
 */
void estatisticas_inicia_contagem(Estatisticas *estatisticas, const char *item);

/**
 * @brief Finaliza a contagem de tempo para um item específico.
 * 
 * @param estatisticas Apontador para a instância de `Estatisticas`.
 * @param item Nome do item para o qual finalizar a contagem.
 */
void estatisticas_termina_contagem(Estatisticas *estatisticas, const char *item);

/**
 * @brief Obtém as estatísticas de um item específico.
 * 
 * @param estatisticas Apontador para a instância de `Estatisticas`.
 * @param item Nome do item cujas estatísticas serão retornadas.
 * @return Um apontador para `EstatisticasItem` associado ao item ou `NULL` se o item não existir.
 */
EstatisticasItem *estatisticas_get_item(Estatisticas *estatisticas, const char *item);

/**
 * @brief Obtém o número de execuções registadas para um item.
 * 
 * @param estatisticasItem Apontador para o item de estatísticas.
 * @return O número de execuções registadas.
 */
int estatisticas_item_get_numero_de_execucoes(EstatisticasItem *estatisticasItem);

/**
 * @brief Obtém o tempo total de execução registado para um item.
 * 
 * @param estatisticasItem Apontador para o item de estatísticas.
 * @return O tempo total de execução em segundos.
 */
double estatisticas_item_get_tempo_de_execucao(EstatisticasItem *estatisticasItem);

/**
 * @brief Converte um objeto `Estatisticas` para uma string.
 * 
 * @param estatisticas Apontador para a instância de `Estatisticas`.
 * @return Uma string contendo as estatísticas.
 */
char *estatisticas_to_string(Estatisticas *estatisticas);

#endif