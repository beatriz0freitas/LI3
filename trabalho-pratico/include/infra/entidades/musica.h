/**
 * @file musica.h
 * @brief Declarações de funções e estruturas referentes à entidade 'Musica'. 
 * 
 * Este arquivo define a estrutura `Musica`, as suas funções de criação, destruição, e 
 * acesso a parâmetros desta. Define também funções para processar e validar a entidade 'Musica'.
 */
#ifndef MUSIC_H
#define MUSIC_H

#include "utils.h"
#include "gestor-de-quarks.h"

/**
 * @brief Estrutura para representar uma música.
 * 
 * A estrutura `Musica` contém os campos necessários para representar uma música.
 */
typedef struct Musica Musica;


/**
 * @brief Aloca memória para uma nova `Musica`.
 * 
 * Esta função aloca memória para uma nova `Musica` e inicializa os seus campos.
 * 
 * @return Um apontador para a nova `Musica`.
 */
Musica *musica_nova();


/**
 * @brief Liberta a memória associada a uma `Musica`.
 * 
 * @param gp Apontador para a `Musica` a ser libertada.
 */
void musica_destroi(gpointer gp);


/**
 * @brief Retorna o ID de uma `Musica`.
 * 
 * @param musica Apontador para a `Musica` a ser consultada.
 * @return O ID da `Musica`.
 */
int musica_get_idMusica(Musica *musica);


/**
 * @brief Retorna o ID do álbum associado a uma `Musica`.
 * 
 * @param musica Apontador para a `Musica` a ser consultada.
 * @return O ID do álbum associado à `Musica`.
 */
int musica_get_idAlbum(Musica *musica);

/**
 * @brief Retorna o ID de um artista associado a uma `Musica` por índice.
 * 
 * @param musica Apontador para a `Musica` a ser consultada.
 * @param indice O índice do artista a ser consultado.
 * @return O ID do artista associado à `Musica` no índice especificado.
 */
int  musica_get_idArtistaPorIndice(Musica *musica, int indice);


/**
 * @brief Retorna o número de artistas associados a uma `Musica`.
 * 
 * @param musica Apontador para a `Musica` a ser consultada.
 * @return O número de artistas associados à `Musica`.
 */
short  musica_get_quantidadeDeArtistas (Musica *musica);

/**
 * @brief Retorna a duração de uma `Musica` em segundos.
 * 
 * @param musica Apontador para a `Musica` a ser consultada.
 * @return A duração da `Musica` em segundos.
 */
short  musica_get_duracaoMusicaEmSegundos (Musica *musica);


/**
 * @brief Retorna o género de uma `Musica`.
 * 
 * @param musica Apontador para a `Musica` a ser consultada.
 * @return O género da `Musica`.
 */
const char *musica_get_generoMusica(Musica *musica);


/**
 * @brief Retorna o género de uma `Musica` em formato `Quark`.
 * 
 * @param musica Apontador para a `Musica` a ser consultada.
 * @return O género da `Musica` em formato `Quark`.
 */
Quark musica_get_generoMusicaQuark(Musica *musica);


/**
 * @brief Constrói uma `Musica` a partir de uma linha de um ficheiro CSV.
 * 
 * @param coluna A linha do ficheiro CSV a ser processada, separada pelas colunas.
 * @return Um apontador para a nova `Musica` construída a partir da linha.
 */
Musica *musica_constroi_de_linha(char **coluna);


#endif