/**
 * @file artista.h
 * @brief Declarações de funções e estruturas referentes à entidade 'Artista'.
 * 
 * Este arquivo define a estrutura `Artista`, as suas funções de criação, destruição, e
 * acesso a parâmetros desta. Define também funções para processar e validar a entidade 'Artista'.
 */
#ifndef ARTIST_H
#define ARTIST_H

#include "utils.h"

/**
 * @brief Enumeração para os tipos de artista.
 */
typedef enum {
    ARTISTA_INVALIDO = 0,/**< Representa um artista inválido */
    INDIVIDUAL = 1,      /**< Representa um artista individual */
    GROUP = 2,           /**< Representa um grupo de artistas */
    
} TipoArtista;


/**
 * @brief Estrutura para representar um artista.
 * 
 * A estrutura `Artista` contém os campos necessários para representar um artista.
 */
typedef struct Artista Artista;


/**
 * @brief Aloca memória para um novo `Artista`.
 * 
 * Esta função aloca memória para um novo `Artista` e inicializa os seus campos.
 * 
 * @return Um apontador para o novo `Artista`.
 */
Artista *artista_novo();


/**
 * @brief Liberta a memória associada a um `Artista`.
 * 
 * @param gp Apontador para o `Artista` a ser libertado.
 */
void artista_destroi(gpointer gp);


/**
 * @brief Retorna o ID de um `Artista`.
 * 
 * @param artista Apontador para o `Artista` a ser consultado.
 * @return O ID do `Artista`.
 */
int artista_get_idArtista(Artista *artista);

/**
 * @brief Retorna o nome de um `Artista`.
 * 
 * @param artista Apontador para o `Artista` a ser consultado.
 * @return O nome do `Artista`.
 */
const char* artista_get_nomeArtista(Artista *artista);

/**
 * @brief Retorna o ID de um artista constituinte associado a um `Artista` por índice.
 * 
 * @param artista Apontador para o `Artista` a ser consultado.
 * @param indice O índice do artista constituinte a ser consultado.
 * @return O ID do artista constituinte associado ao `Artista` no índice especificado.
 */
int  artista_get_idConstituintesArtistasPorIndice(Artista *artista, int indice);

/**
 * @brief Retorna o número de artistas constituintes associados a um `Artista`.
 * 
 * @param artista Apontador para o `Artista` a ser consultado.
 * @return O número de artistas constituintes associados ao `Artista`.
 */
short artista_get_numeroConstituintesArtistas(Artista *artista);

/**
 * @brief Retorna a nacionalidade de um `Artista`.
 * 
 * @param artista Apontador para o `Artista` a ser consultado.
 * @return A nacionalidade do `Artista`.
 */
const char* artista_get_nacionalidadeArtista(Artista *artista);

/**
 * @brief Retorna o tipo de um `Artista`.
 * 
 * @param artista Apontador para o `Artista` a ser consultado.
 * @return O tipo do `Artista`(`INDIVIDUAL`, `GROUP` ou `ARTISTA_INVALIDO`).
 */
TipoArtista artista_get_tipoArtista(Artista *artista);

/**
 * @brief Retorna a duração total da discografia de um `Artista`, em segundos.
 * 
 * @param artista Apontador para o `Artista` a ser consultado.
 * @return A duração total da discografia do `Artista` em segundos.
 */
int artista_get_duracaoDiscorgrafiaEmSegundos(Artista *artista);

/**
 * @brief Define a duração total da discografia de um `Artista`, em segundos.
 * 
 * @param artista Apontador para o `Artista` a ser modificado.
 * @param duracaoDiscorgrafiaEmSegundos A nova duração total da discografia do `Artista` a ser definida.
 */
void artista_acrescenta_duracaoDiscografiaEmSegundos(Artista *artista, int duracaoDiscorgrafiaEmSegundos);


/**
 * @brief Converte uma string para um `TipoArtista`.
 * 
 * @param tipo A string a ser convertida.
 * @return O `TipoArtista` correspondente à string (`INDIVIDUAL`, `GROUP` ou `ARTISTA_INVALIDO`).
 */
TipoArtista artista_tipo (char *tipo);


/**
 * @brief Converte um `TipoArtista` para uma string.
 * 
 * @param tipoArtista O `TipoArtista` a ser convertido.
 * @return A string correspondente ao `TipoArtista` (`INDIVIDUAL`, `GROUP` ou `ARTISTA_INVALIDO`).
 */
char* artista_tipo_para_string(TipoArtista tipoArtista);


/**
 * @brief Verifica se um `Artista` é válido.
 * 
 * O artista é inválido se for do tipo individual e tiver artistas constituintes.
 * 
 * @param artista Apontador para o `Artista` a ser validado.
 * @return `TRUE` se o `Artista` é válido, `FALSE` caso contrário.
 */
gboolean artista_valida(Artista *artista);


/**
 * @brief Constrói uma estrutura `Artista` a partir de uma linha de um ficheiro CSV.
 *
 * @param linha Linha de texto com os dados do artista.
 * @return Um apontador para o novo `Artista`.
 */
Artista *artista_constroi_de_linha(char **coluna);


/**
 * @brief Compara dois `Artista` por duração de discografia e nome.
 * 
 * Compara por ordem decrescente de discografia e, caso a discografia seja igual, por ordem alfabética
 * 
 * @param a Apontador para o primeiro `Artista`.
 * @param b Apontador para o segundo `Artista`.
 * @return Um valor negativo se `a` é menor que `b`, um valor positivo se `a` é maior que `b`, ou zero se forem iguais.
 */
gint artista_compara_decrescente(gconstpointer a, gconstpointer b);

/**
 * @brief Incrementa o número de álbuns associados a um `Artista`.
 * 
 * Esta função aumenta em 1 o contador de álbuns de um determinado `Artista`.
 * 
 * @param artista Apontador para o `Artista` cujo número de álbuns será incrementado.
 */
void artista_incrementa_numeroDeAlbuns(Artista *artista);

/**
 * @brief Obtém o número total de álbuns associados a um `Artista`.
 * 
 * Esta função retorna o número de álbuns registados para um determinado `Artista`.
 * 
 * @param artista Apontador para o `Artista` a ser consultado.
 * @return Um inteiro representando o número total de álbuns associados ao `Artista`.
 */
short artista_get_numeroDeAlbuns(Artista *artista);

/**
 * @brief Obtém o lucro total acumulado de um `Artista`.
 * 
 * Esta função retorna o valor total do lucro gerado pelo `Artista` a partir de reproduções.
 * 
 * @param artista Apontador para o `Artista` a ser consultado.
 * @return Um valor de ponto flutuante representando o lucro total do `Artista`.
 */
float artista_get_profitTotal(Artista *artista);

/**
 * @brief Obtém o lucro por reprodução associado a um `Artista`.
 * 
 * Esta função retorna o valor de lucro gerado por cada reprodução das músicas do `Artista`.
 * 
 * @param artista Apontador para o `Artista` a ser consultado.
 * @return Um valor de ponto flutuante representando o lucro por reprodução do `Artista`.
 */
float artista_get_profitPorReproducao(Artista *artista);

/**
 * @brief Incrementa o lucro total do `Artista` considerando os lucros dos constituintes.
 * 
 * Esta função adiciona um valor específico de lucro ao total acumulado de um `Artista`.
 * É útil para registar lucros gerados por constituintes de um grupo artístico.
 * 
 * @param artista Apontador para o `Artista` a ser modificado.
 * @param profit Valor de lucro a ser adicionado ao total do `Artista`.
 */
void artista_constituintes_incrementa_profitTotal(Artista *artista, float profit);

/**
 * @brief Incrementa o lucro total de um `Artista`.
 * 
 * Esta função soma o valor do lucro por reprodução ao lucro total do `Artista`.
 * 
 * @param artista Apontador para o `Artista` a ser modificado.
 */
void artista_incrementa_profitTotal(Artista *artista);

/**
 * @brief Converte o ID de um `Artista` para uma string formatada.
 * 
 * Esta função retorna uma string contendo o ID do `Artista` no formato "A######", onde
 * o número é representado com 7 dígitos, preenchendo com zeros à esquerda se necessário.
 * 
 * @param id O ID do `Artista` a ser convertido.
 * @return Uma string contendo o ID formatado.
 */
char *artista_id_para_string(int id);


#endif