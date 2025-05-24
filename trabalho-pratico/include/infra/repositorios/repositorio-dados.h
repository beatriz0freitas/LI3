/**
 * @file repositorio-dados.h
 * @brief Declarações de funções e estruturas referentes ao repositório dos dados de artistas, músicas, utilizadores e estruturas auxiliares para queries.
 *
 * Este arquivo contém as definições da estrutura `Dados` e as funções associadas
 * para criar, destruir e validar dados no repositório, assim como para operações 
 * auxiliares relacionadas ás entidades e ás queries.
 */
#ifndef REPOSITORIO_DADOS_H
#define REPOSITORIO_DADOS_H

#include "repositorio-artistas.h"
#include "repositorio-musicas.h"
#include "repositorio-utilizadores.h"
#include "repositorio-album.h"
#include "repositorio-historico.h"
#include "estatisticas.h"
#include "min-heap.h"
#include "parser.h"

/**
 * @brief Estrutura para representar os dados do repositório.
 * 
 * A estrutura `Dados` fornece uma forma centralizada de aceder e gerir
 * os restantes repositórios e estruturas auxiliares.
 */
typedef struct Dados Dados;

/**
 * @brief Cria e inicializa um novo `Dados`.
 * 
 * @return Um apontador para o novo `Dados`.
 */
Dados *dados_novo(GHashTable *HistoricoNecessario, GHashTable *UtilizadoresNecessarios);

/**
 * @brief Liberta a memória associada à estrutura `Dados`.
 * 
 * Esta função liberta todos os recursos associados a `Dados`.
 * 
 * @param dados Apontador para o `Dados` a ser libertado.
 */
void dados_destroi(Dados *dados);

/**
 * @brief Retorna o repositório de artistas de `Dados`.
 * 
 * @param dados Apontador para o `Dados`.
 * @return Um apontador para o repositório de artistas de `Dados`.
 */
RepositorioArtistas *dados_get_repositorioArtistas(Dados *dados);

/**
 * @brief Retorna o repositório de músicas de `Dados`.
 * 
 * @param dados Apontador para o `Dados`.
 * @return Um apontador para o repositório de músicas de `Dados`.
 */
RepositorioMusicas *dados_get_repositorioMusicas(Dados *dados);

/**
 * @brief Retorna o repositório de utilizadores de `Dados`.
 * 
 * @param dados Apontador para o `Dados`.
 * @return Um apontador para o repositório de utilizadores de `Dados`.
 */
RepositorioUtilizadores *dados_get_repositorioUtilizadores(Dados *dados);

/**
 * @brief Retorna o repositório de históricos de `Dados`.
 * 
 * @param dados Apontador para o `Dados`.
 * @return Um apontador para o repositório de históricos de `Dados`.
 */
RepositorioHistoricos *dados_get_repositorioHistoricos(Dados *dados);


/**
 * @brief Retorna o top 10 artistas da semana pedida de `Dados`.
 * 
 * @param dados Apontador para `Dados`.
 * @return Um apontador para a `MinHeap` de top 10 artistas da semana pedida.
 */

const MinHeap *dados_get_top10_da_semana(Dados *dados, int semana);

int dados_get_numero_semanas (Dados *dados);


/**
 * @brief Carrega os dados a partir de arquivos armazenados em disco.
 * 
 * @param estatisticas Apontador para a estrutura de estatísticas.
 * @param pastaDados Caminho para a pasta contendo os dados.
 * @return Um apontador para a estrutura `Dados` carregada.
 */
Dados* dados_carregar(void* estatisticas, char *pastaDados, Dados *dados);


/**
 * @brief Estrutura para representar uma reprodução de artista.
 */
typedef struct ArtistaReproducao ArtistaReproducao;


/**
 * @brief Obtém o ID do artista de um 'ArtistaReproducao'.
 * 
 * @param artista Apontador para uma estrutra de Artista com Reproduções.
 * @return O ID do artista.
 */
int artista_reproducao_get_idArtista(struct ArtistaReproducao *artista);


/**
 * @brief Obtém o número de reproduções do artista.
 * 
 * @param artista Apontador para a reprodução de artista.
 * @return O número de reproduções.
 */
int artista_reproducao_get_reproducoes(struct ArtistaReproducao *artista);


/**
 * @brief Liberta os recursos de um heap de reproduções de artistas.
 * 
 * @param heap Apontador para o heap a ser destruído.
 */
void repositorio_dados_heap_artista_reproducao_destroi(MinHeap *heap);


/**
 * @brief Obtém a ordem das colunas de gêneros musicais.
 * 
 * @param dados Apontador para a estrutura `Dados`.
 * @return Um apontador para a ordem das colunas de gêneros musicais.
 */
char **dados_get_ordemColunasGeneros(Dados *dados);

/**
 * @brief Obtém a matriz de audições de utilizadores por gênero.
 * 
 * @param dados Apontador para a estrutura `Dados`.
 * @return Um apontador para a matriz de audições.
 */
int **dados_get_audicoesUtilizadoresPorGenero(Dados *dados);


/**
 * @brief Obtém o próximo índice de coluna para audições.
 * 
 * @param dados Apontador para a estrutura `Dados`.
 * @return O próximo índice de coluna.
 */
int dados_get_proximoIndiceColuna(Dados *dados);

/**
 * @brief Estrutura para iterar sobre os gêneros musicais.
 */
typedef struct GenerosIterador GenerosIterador;

/**
 * @brief Cria um iterador novo
 * 
 * @param dados Apontador para a estrutura `Dados`.

 * @return Um apontador para a estrutura `GenerosIterador`.
 */

GenerosIterador *generos_iterador_novo(Dados *dados);

/**
 * @brief Itera sobre a entrada seguinte na hashTable
 * 
 * @param iterador Apontador para a estrutura `GenerosIterador`.
 * @param genero Apontador para a key.
 * @param array Apontador para o valor.
 * @return TRUE se iterou ou FALSE caso contrário
 */

gboolean generos_iterador_proximo(GenerosIterador *iterador, Quark *genero, GArray **array);


/**
 * @brief Destroi o iterador criado.
 * 
 * @param iterador Apontador para a estrutura `GenerosIterador` a libertar.
 */
void generos_iterador_destroi(GenerosIterador *iterador);

#endif
