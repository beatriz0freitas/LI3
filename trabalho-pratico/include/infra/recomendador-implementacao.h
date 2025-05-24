/**
 * @file recomendador.h
 * @brief Header file do recomendador de utilizadores baseado em audição de músicas.
 *
 * Este arquivo define a interface de uma função de recomendação de utilizadores,
 * que sugere utilizadores com base nas audições de músicas de diferentes géneros.
 * 
 * A recomendação é feita tendo em consideração a similaridade entre os utilizadores,
 * e sugere aqueles que têm gostos musicais semelhantes ao utilizador alvo.
 */

#ifndef RECOMENDADOR_H
#define RECOMENDADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
 * @brief Gera recomendações de utilizadores com base nas classificações de músicas.
 * 
 * Esta função recomenda utilizadores com base nas classificações de músicas de diferentes géneros.
 * Ela utiliza as classificações fornecidas para identificar utilizadores com gostos semelhantes ao 
 * utilizador alvo e retorna um conjunto de recomendações.
 * 
 * @param idUtilizadorAlvo O ID do utilizador para o qual as recomendações serão geradas.
 * @param matrizClassificacaoMusicas A matriz de classificações onde cada linha representa um 
 *        utilizador e cada coluna um género de música. Os valores indicam o número de vezes que o 
 *        utilizador ouviu músicas de determinado género.
 * @param idsUtilizadores Um array com os IDs dos utilizadores, correspondendo à ordem das linhas 
 *        da matriz de classificações.
 * @param nomesGeneros Um array contendo os nomes dos géneros musicais, correspondendo à ordem das 
 *        colunas da matriz de classificações.
 * @param numUtilizadores O número total de utilizadores na base de dados.
 * @param numGeneros O número total de géneros musicais na base de dados.
 * @param numRecomendacoes O número de recomendações a serem geradas. O número de recomendações 
 *        será truncado caso seja maior que o número de utilizadores disponíveis.
 * 
 * @return Um array de strings contendo os IDs dos utilizadores recomendados, com tamanho igual ao 
 *         número de recomendações solicitadas.
 * 
 * @note Caso o número de recomendações seja maior que o número total de utilizadores, o valor 
 *       de `numRecomendacoes` será ajustado automaticamente.
 */
char **recomendador_de_utilizadores(char *idUtilizadorAlvo,
                                     int **matrizClassificacaoMusicas,
                                     char **idsUtilizadores, char **nomesGeneros,
                                     int numUtilizadores, int numGeneros,
                                     int numRecomendacoes);

#endif