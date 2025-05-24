/**
 * @file album.h
 * @brief Declarações de funções e estruturas para manipulação de álbuns.
 *
 * Este arquivo define a estrutura `Album` e as funções associadas para criar,
 * destruir e aceder os dados de um álbum musical.
 */

#ifndef ALBUM_H
#define ALBUM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

/**
 * @brief Estrutura que representa um álbum musical.
 */
typedef struct Album Album;

/**
 * @brief Cria uma nova instância de `Album`.
 *
 * @return Apontador para um novo `Album` inicializado.
 */
Album *album_novo();

/**
 * @brief Liberta a memória associada a um `Album`.
 *
 * @param gp Apontador genérico para a estrutura `Album` a ser destruída.
 */
void album_destroi(gpointer gp);

/**
 * @brief Obtém o ID do álbum.
 *
 * @param album Apontador para a estrutura `Album`.
 * @return O ID do álbum.
 */
int album_get_idAlbum(Album *album);

/**
 * @brief Obtém o ID de um artista associado ao álbum por índice.
 *
 * @param album Apontador para a estrutura `Album`.
 * @param indice Índice do artista a ser acessado.
 * @return O ID do artista no índice especificado ou -1 se o índice for inválido.
 */
int album_get_idArtistaPorIndice(Album *album, int indice);

/**
 * @brief Obtém a quantidade de artistas associados ao álbum.
 *
 * @param album Apontador para a estrutura `Album`.
 * @return A quantidade de artistas associados ao álbum.
 */
short album_get_quantidadeDeArtistas(Album *album);

/**
 * @brief Converte um ID de álbum numa string no formato "ALXXXXXX".
 *
 * @param id O ID do álbum.
 * @return String representando o ID formatado. Deve ser libertada com `free` após o uso.
 */
char *album_id_para_string(int id);

/**
 * @brief Constroi uma estrutura `Album` a partir de uma linha de dados.
 *
 * @param coluna Array de strings representando os campos de uma linha de dados, separada por colunas.
 * @return Apontador para um `Album` preenchido com os dados fornecidos.
 */
Album *album_constroi_de_linha(char **coluna);

#endif
