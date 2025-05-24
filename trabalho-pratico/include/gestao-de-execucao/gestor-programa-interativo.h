/**
 * @file gestor-programa-interativo.h
 * @brief Declarações de funções para execução interativa de queries.
 *
 * Este arquivo define as funções para interação com o usuário em modo texto,
 * utilizando a biblioteca ncurses para execução de queries de forma interativa.
 */

#ifndef GESTOR_PROGRAMA_INTERATIVO_H
#define GESTOR_PROGRAMA_INTERATIVO_H

#include <ncurses.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <panel.h>
#include <form.h>
#include "gestor-de-queries.h"
#include "repositorio-dados.h"

/**
 * @brief Estrutura principal do gestor de programa interativo.
 *
 * Estrutura responsável por gerir o programa interativo.
 */
typedef struct GestorDeProgramaInterativo GestorDeProgramaInterativo;


/**
 * @brief Estrutura de estado do programa interativo.
 *
 * Estrutura responsável por armazenar o estado do programa interativo.
 */
typedef struct EstadoProgramaInterativo EstadoProgramaInterativo;


/**
 * @brief Cria um novo estado do programa interativo.
 *
 * Esta função inicializa e retorna um novo estado do programa interativo.
 *
 * @return Um apontador para o novo estado do programa interativo.
 */
GestorDeProgramaInterativo *gestor_programa_interativo_novo();


/**
 * @brief Destrói um estado do programa interativo.
 *
 * Esta função dá free a um estado do programa interativo.
 *
 * @param gestorPrograma Apontador para o estado do programa interativo a ser destruído.
 */
void gestor_programa_interativo_destroi(GestorDeProgramaInterativo *gestorPrograma);


/**
 * @brief Executa o programa interativo.
 *
 * Esta função executa o programa interativo, carregando os dados, lendo do input e executando as queries
 * fornecidas.
 *
 * @param pastaDados Diretório onde os ficheiros de dados a serem carregados estão localizados.
 */
void gestor_programa_interativo_executa(GestorDeProgramaInterativo *gestorProgramaInterativo);


#endif
