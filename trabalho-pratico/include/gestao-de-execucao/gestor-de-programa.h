/**
 * @file gestor-de-programa.h
 * @brief Declarações de funções e estruturas para gerir o programa principal.
 *
 * Este gestor define a estrutura `GestorDePrograma` e as funções associadas para gerir
 * a execução do programa principal, incluindo a execução de queries.
 */

#ifndef GESTOR_DE_PROGRAMA_H
#define GESTOR_DE_PROGRAMA_H

#include "gestor-de-queries.h"
#include "input.h"


/**
 * @brief Estrutura principal para gerir o programa.
 *
 * A estrutura `GestorDePrograma` encapsula a lógica para execução de operações
 * no sistema principal.
 */
typedef struct GestorDePrograma GestorDePrograma;


/**
 * @brief Cria um novo ´GestorDePrograma'.
 * 
 * Esta função inicializa e retorna um novo `GestorDePrograma`.
 * 
 * @param estatisticas Pode receber uma estrutura de estatísticas quando usado pelo programa de testes 
 * ou receber NULL quando usado pelo programa principal.
 * 
 * @return Um apontador para o novo `GestorDePrograma`.
 */
GestorDePrograma *gestor_programa_novo(Estatisticas *estatisticas, gboolean modoEconomiaMemoria);


/**
 * @brief Destrói um `GestorDePrograma'.
 *
 * Esta função liberta todos os recursos associados ao gestor de programa.
 *
 * @param gestorPrograma Apontador para o `GestorDePrograma` a ser destruído.
 */
void gestor_programa_destroi(GestorDePrograma *gestorPrograma);


/**
 * @brief Executa o programa principal.
 *
 * Esta função executa o programa, carregando os dados, lendo do input e executando as queries
 * fornecidas.
 *
 * @param gestor Apontador para o `GestorDePrograma` a ser executado.
 * @param pastaDados Diretório onde os ficheiros de dados a serem carregados estão localizados.
 * @param caminhoFicheiroInput Caminho para o ficheiro de input com as queries a serem executadas.
 */
void gestor_programa_executa(GestorDePrograma* gestor, char *pastaDados, char *caminhoFicheiroInput);

/**
 * @brief Retorna o gestor de queries associado ao `GestorDePrograma`.
 *
 * @param gestorDePrograma Apontador para o `GestorDePrograma` a ser consultado.
 * @return O apontador para o `GestorDeQueries` associado a este gestor de programa.
 */
GestorDeQueries *gestor_programa_get_gestor_queries(GestorDePrograma* gestorDePrograma);


#endif