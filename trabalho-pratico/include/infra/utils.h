/**
 * @file utils.h
 * @brief Declarações de funções utilitárias para manipulação de strings, validações e conversões.
 *
 * Este arquivo contém funções auxiliares para realizar operações como conversão de tempo, 
 * validações de formato e manipulação de strings em diversos contextos.
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <glib.h>

/**
 * @brief Converte segundos para string no formato 'HH:MM:SS'
 * 
 * Converte um número de segundos inteiros para uma string representando o tempo no formato 'HH:MM:SS'.
 * 
 * @param segundos Número de segundos a converter
 * @return char* String resultante no formato 'HH:MM:SS', ou NULL se a conversão falhar
 */
char *utils_segundos_para_string(int segundos);


/**
 * @brief Remove caracteres de uma string a partir de uma posição inicial e final
 * 
 * Remove uma parte de uma string, excluindo os caracteres da posição inicial até a posição final.
 * 
 * @param string Apontador para a string a ser manipulada
 * @param inicio Posição inicial a ser removida
 * @param fim Posição final a ser removida
 * @return Apontador para a string resultante após remoção dos caracteres
 */
char *utils_remove_caracteres_inicio_e_fim(char *string, int inicio, int fim);


/**
 * @brief Remove aspas de uma string
 * 
 * Esta função remove as aspas do início e do final de uma string.
 * 
 * @param coluna Apontador para a string a ser manipulada
 */
void utils_remove_aspas(char *coluna);


/**
 * @brief Valida se uma string está entre parênteses
 * 
 * Verifica se uma string está corretamente encapsulada entre parênteses.
 * 
 * @param lista String a ser validada
 * @return TRUE se a string está entre parênteses, FALSE caso contrário
 */
gboolean utils_valida_parentises(char *lista);


/**
 * @brief Valida se um endereço de e-mail é válido.
 *
 * Esta função valida a sintaxe de um endereço de e-mail, verificando se ele segue o padrão de um e-mail 
 * válido, incluindo a presença de "@" e "." em locais apropriados.
 *
 * @param email Apontador para o endereço de e-mail a ser validado
 * @return gboolean Retorna TRUE se o e-mail for válido, ou FALSE caso contrário
 */
gboolean utils_valida_email(const char *email);


/**
 * @brief Obtem o nome de um ficheiro a partir de um caminho
 * 
 * Esta função extrai o nome do arquivo a partir de um caminho completo, sem a extensão.
 * 
 * @param caminho Caminho completo do ficheiro
 * @return Apontador para o nome do ficheiro sem a extensão
 */
char* utils_obtem_nome_ficheiro(char* caminho);


/**
 * @brief Valida a duração de uma música no formato 'HH:MM:SS'
 * 
 * Valida se uma string de duração de música está no formato correto 'HH:MM:SS' e se os valores de horas,
 * minutos e segundos estão dentro de limites válidos.
 * 
 * @param duracaoMusica String contendo a duração da música
 * @return gboolean TRUE se a duração for válida, FALSE caso contrário
 */
gboolean utils_valida_duracao(char* duracaoMusica);


/**
 * @brief Converte uma duração de música no formato 'HH:MM:SS' para segundos inteiros
 * 
 * Converte uma duração de música no formato 'HH:MM:SS' para o total de segundos correspondentes.
 * 
 * @param duracao String contendo a duração no formato 'HH:MM:SS'
 * @return int Número total de segundos correspondentes à duração fornecida
 */
short utils_converte_duracao_para_segundos(char* duracao);


/**
 * @brief Calcula o número da semana juliana a partir de uma data
 * 
 * Calcula o número da semana juliana para uma data fornecida, baseado no calendário juliano.
 * 
 * @param data Data a ser utilizada no cálculo
 * @return int Número da semana juliana correspondente
 */
int utils_calcular_numero_semana_juliana(GDate *data);


/**
 * @brief Calcula a idade de uma pessoa com base na data de nascimento
 * 
 * Calcula a idade de uma pessoa com base na data de nascimento fornecida e na data atual.
 * 
 * @param dataNascimento Data de nascimento da pessoa
 * @return int Idade calculada
 */
int utils_calcula_idade(GDate *dataNascimento);


/**
 * @brief Dá free a inteiros alocados com g_slice_new
 * 
 * @param gp Apontador para o inteiro a ser libertado.
 */
void utils_g_slice_free_int(gpointer gp);

#endif
