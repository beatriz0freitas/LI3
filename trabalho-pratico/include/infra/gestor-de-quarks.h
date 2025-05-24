/**
 * @file gestor-de-quarks.h
 * 
 * @brief Módulo de gestão de quarks baseado em GLib
 * 
 * Este módulo implementa um sistema de gestão de quarks, que são identificadores
 * únicos associados a strings. Ele utiliza GHashTable da biblioteca GLib
 * para mapear strings para quarks e vice-versa.
 */

#ifndef GESTOR_DE_QUARKS_H
#define GESTOR_DE_QUARKS_H

#include <glib.h>
#include <stdlib.h>

/**
 * @typedef Quark
 * 
 * @brief Um identificador único associado a uma string.
 */

typedef guint32 Quark;


/**
 * @struct GestorDeQuarks 
 * 
 * @brief Estrutura de dados para armazenar quarks e suas strings associadas.
 * 
 */
typedef struct GestorDeQuarks GestorDeQuarks;

/**
 * @brief Obtém o quark associado a uma string.
 * 
 * Esta função retorna um quark único associado a uma string. Se a string já
 * tiver um quark associado, o quark existente será retornado. Caso contrário,
 * um novo quark será criado e associado à string.
 * 
 * @param string A string para a qual o quark será obtido.
 * @return Quark associado à string.
 */

Quark quark_de_string(const char *string);

/**
 * @brief Obtém a string associada a um quark.
 * 
 * Dado um quark previamente obtido, esta função retorna a string associada a ele.
 * 
 * @param quark O quark para o qual a string será obtida.
 * @return A string associada ao quark ou NULL se o quark não existir.
 * 
 */

const char *string_de_quark(Quark quark);


/**
 * @brief Libera os recursos alocados pelo gestor de quarks.
 * 
 * Esta função destrói as tabelas hash utilizadas e libera toda a memória
 * alocada pelo gestor de quarks.
 * 
 */

void gestor_de_quarks_destroi();

#endif 
