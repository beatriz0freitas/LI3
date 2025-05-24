/**
 * @file utilizador.h
 * @brief Declarações de funções e estruturas referentes à entidade 'Utilizador'.
 * 
 * Este arquivo define a estrutura `Utilizador`, as suas funções de criação, destruição, e
 * acesso a parâmetros desta. Define também funções para processar e validar a entidade 'Utilizador'.
 */

#ifndef UTILIZADOR_H
#define UTILIZADOR_H

#include "utils.h"

/**
 * @brief Enumeração para os tipos de subscrição de um `Utilizador`.
 */
typedef enum {
    NORMAL,
    PREMIUM,
    UTILIZADOR_INVALIDO
} TipoSubscricao;


/**
 * @brief Estrutura para representar um utilizador.
 * 
 * A estrutura `Utilizador` contém os campos necessários para representar um utilizador.
 */
typedef struct Utilizador Utilizador;


/**
 * @brief Aloca memória para um novo `Utilizador`.
 * 
 * Esta função aloca memória para um novo `Utilizador` e inicializa os seus campos.
 * 
 * @return Um apontador para o novo `Utilizador`.
 */
Utilizador *utilizador_novo();


/**
 * @brief Liberta a memória associada a um `Utilizador`.
 * 
 * @param gp Apontador para o `Utilizador` a ser libertado.
 */
void utilizador_destroi(gpointer utilizador);


/**
 * @brief Retorna o ID de um `Utilizador`.
 * 
 * @param utilizador Apontador para o `Utilizador` a ser consultado.
 * @return  ID do `Utilizador`.
 */
int utilizador_get_idDoUtilizador(Utilizador *utilizador);


/**
 * @brief Retorna o email de um `Utilizador`.
 * 
 * @param utilizador Apontador para o `Utilizador` a ser consultado.
 * @return O email do `Utilizador`.
 */
const char *utilizador_get_emailDoUtilizador(Utilizador *utilizador);


/**
 * @brief Retorna o nome de um `Utilizador`.
 * 
 * @param utilizador Apontador para o `Utilizador` a ser consultado.
 * @return O nome do `Utilizador`.
 */
const char *utilizador_get_nomeDoUtilizador(Utilizador *utilizador);


/**
 * @brief Retorna o apelido de um `Utilizador`.
 * 
 * @param utilizador Apontador para o `Utilizador` a ser consultado.
 * @return O apelido do `Utilizador`.
 */
const char *utilizador_get_apelidoDoUtilizador(Utilizador *utilizador);


/**
 * @brief Retorna a idade de um `Utilizador`.
 * 
 * @param utilizador Apontador para o `Utilizador` a ser consultado.
 * @return A idade do `Utilizador`.
 */
short utilizador_get_idadeDoUtilizador(Utilizador *utilizador);


/**
 * @brief Retorna o país de registo de um `Utilizador`.
 * 
 * @param utilizador Apontador para o `Utilizador` a ser consultado.
 * @return O país de registo do `Utilizador`.
 */
const char *utilizador_get_paisDeRegisto(Utilizador *utilizador);


/**
 * @brief Retorna o ID da música gostada de um `Utilizador` num índice especifico.
 * 
 * @param utilizador Apontador para o `Utilizador` a ser consultado.
 * @param indice Índice da música gostada a ser consultada.
 * @return O ID da música gostada no índice especificado.
 */
int utilizador_get_musicasGostadasPorIndice(Utilizador *utilizador, int indice);


/**
 * @brief Retorna a quantidade de músicas gostadas de um `Utilizador`.
 * 
 * @param utilizador Apontador para o `Utilizador` a ser consultado.
 * @return A quantidade de músicas gostadas do `Utilizador`.
 */
short utilizador_get_quantidadeDeMusicasGostadas(Utilizador *utilizador);


/**
 * @brief Constrói um `Utilizador` a partir de uma linha de um ficheiro CSV.
 * 
 * @param linha Linha do ficheiro CSV a ser processada, dividida por colunas.
 * @return Apontador para o novo `Utilizador` construído a partir da linha.
 */
Utilizador *utilizador_constroi_de_linha(char **coluna);


/**
 * @brief Verifica se o `Utilizador` é válido.
 * 
 * Esta função valida o tipo de subscrição, a data de nascimento e o email do utilizador.
 *
 * @param utilizador Apontador para o `Utilizador`.
 * @return `TRUE` se o `Utilizador` for válido, `FALSE` caso contrário.
 */
gboolean utilizador_valida(char **coluna,  GDate *dataNascimento);

/**
 * @brief Converte um ID de utilizador em uma string formatada.
 * 
 * Esta função recebe um ID de utilizador do tipo `int` e retorna uma string
 * formatada que representa o ID. O formato da string é composto pela letra 'U'
 * seguida de um número com 7 dígitos, completando com zeros à esquerda, caso necessário.
 * 
 * @param id O ID do utilizador a ser convertido para string.
 * 
 * @return Uma string formatada representando o ID do utilizador, no formato "UXXXXXXX"
 * 
 * @note A função aloca memória para a string resultante. É responsabilidade do
 *       chamador libertar a memória quando não for mais necessária.
 * 
 * @warning A alocação de memória pode falhar se o sistema estiver sem recursos.
 */
char *utilizador_id_para_string(int id);


#endif