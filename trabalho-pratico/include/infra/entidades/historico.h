/**
 * @file historico.h
 * @brief Declarações de funções e estruturas referentes à entidade 'Historico'. 
 * 
 * Este arquivo define a estrutura `Historico`, as suas funções de criação, destruição, e 
 * acesso a parâmetros desta. Define também funções para processar e validar a entidade 'Historico'.
 */

#ifndef HISTORICO_H
#define HISTORICO_H

#include "utils.h"

/**
 * @brief Enumeração que representa os tipos de plataformas de reprodução.
 */
typedef enum {
    PLATAFORMA_INVALIDA = 0, /**< Plataforma inválida */
    MOBILE = 1,             /**< Plataforma móvel */
    DESKTOP = 2             /**< Plataforma desktop */
} TipoPlataforma;

/**
 * @brief Estrutura que representa o histórico de reprodução de músicas.
 */
typedef struct Historico Historico;

/**
 * @brief Cria um novo objeto `Historico` com valores iniciais padrão.
 * 
 * @return Um apontador para a estrutura `Historico` alocada.
 */
Historico *historico_novo();

/**
 * @brief Liberta os recursos associados a um objeto `Historico`.
 * 
 * @param gp Apontador genérico para o objeto `Historico` a ser destruído.
 */
void historico_destroi(gpointer gp);

/**
 * @brief Obtém o ID do registro do histórico.
 * 
 * @param historico Apontador para a estrutura `Historico`.
 * @return Um inteiro representando o ID do registro.
 */
int historico_get_idRegistoHistorico(Historico *historico);

/**
 * @brief Obtém o ID do utilizador associado ao histórico.
 * 
 * @param historico Apontador para a estrutura `Historico`.
 * @return Um inteiro representando o ID do utilizador.
 */
int historico_get_idUtilizador(Historico *historico);

/**
 * @brief Obtém o ID da música associada ao histórico.
 * 
 * @param historico Apontador para a estrutura `Historico`.
 * @return Um inteiro representando o ID da música.
 */
int historico_get_idMusica(Historico *historico);

/**
 * @brief Obtém a data em que a música foi ouvida.
 * 
 * @param historico Apontador para a estrutura `Historico`.
 * @return Um apontador para a estrutura `GDate` representando a data.
 */
GDate* historico_get_dataMusicaOuvida(Historico *historico);

/**
 * @brief Obtém a hora em que a música foi ouvida.
 * 
 * @param historico Apontador para a estrutura `Historico`.
 * @return Um valor `short` representando a hora em formato 24 horas.
 */
short historico_get_horaMusicaOuvida(Historico *historico);

/**
 * @brief Obtém a duração da audição da música em segundos.
 * 
 * @param historico Apontador para a estrutura `Historico`.
 * @return Um inteiro representando a duração em segundos.
 */
short historico_get_duracaoAudicaoMusicaSegundos(Historico *historico);

/**
 * @brief Constrói um objeto `Historico` a partir de uma linha de dados.
 * 
 * @param colunas Array de strings representando os valores da linha, separada em colunas.
 * @return Um apontador para a estrutura `Historico` criada ou `NULL` em caso de erro.
 */
Historico *historico_constroi_de_linha(char **colunas);

#endif // HISTORICO_H
