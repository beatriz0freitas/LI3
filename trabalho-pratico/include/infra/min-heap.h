/**
 * @file min-heap.h
 * @brief Definição e manipulação de uma heap mínima genérica.
 * 
 * Este arquivo define a estrutura e funções para manipulação de uma heap mínima genérica.
 * A heap é uma estrutura de dados que mantém a propriedade de que o menor elemento está sempre na raiz.
 * As operações básicas incluem inserção de elementos e remoção do mínimo.
 */

#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Definição da função de comparação genérica.
 * 
 * Função que compara dois elementos para determinar a ordem entre eles.
 * Deve retornar:
 * - Um valor negativo se o primeiro elemento for menor que o segundo.
 * - Zero se os elementos forem iguais.
 * - Um valor positivo se o primeiro elemento for maior que o segundo.
 */
typedef int (*Comparador)(const void *, const void *);

/**
 * @brief Definição da função para destruir os dados armazenados na heap.
 * 
 * Função usada para libertar a memória alocada para os dados de um elemento.
 */
typedef void (*DestroiDados)(void *);

/**
 * @brief Estrutura que representa uma heap mínima genérica.
 * 
 * A heap é implementada como um vetor dinâmico que armazena apontadores para os dados.
 * A propriedade da heap mínima é garantida pela função de comparação fornecida.
 */
typedef struct MinHeap MinHeap;

/**
 * @brief Cria uma nova heap mínima.
 * 
 * Aloca e inicializa uma nova heap mínima com a capacidade fornecida.
 * A função de comparação é usada para manter a propriedade de heap mínima.
 * 
 * @param capacidade A capacidade máxima da heap.
 * @param comparador A função de comparação utilizada para ordenar os elementos.
 * 
 * @return Um apontador para a nova heap mínima.
 */
MinHeap *heap_nova(int capacidade, Comparador comparador);

/**
 * @brief Destrói a heap mínima e liberta a memória alocada.
 * 
 * A função libera a memória utilizada pela heap e, destrói os dados armazenados.
 * A função `destroiDados` é chamada para cada elemento armazenado, se fornecida.
 * 
 * @param heap O apontador para a heap a ser destruída.
 * @param destroiDados A função que destrói os dados dos elementos armazenados, ou NULL.
 */
void heap_destroi(MinHeap *heap, DestroiDados destroiDados);

/**
 * @brief Obtém um elemento da heap pelo índice.
 * 
 * Esta função retorna o elemento armazenado na heap no índice especificado.
 * 
 * @param heap O apontador para a heap.
 * @param index O índice do elemento na heap.
 * 
 * @return O apontador para o elemento, ou NULL se o índice for inválido.
 */
void *min_heap_get_dados_por_indice(const MinHeap *heap, int index);

/**
 * @brief Obtém o número de elementos na heap.
 * 
 * Esta função retorna a quantidade de elementos atualmente armazenados na heap.
 * 
 * @param heap O apontador para a heap.
 * 
 * @return O número de elementos na heap.
 */
int min_heap_get_tamanho(const MinHeap *heap);

/**
 * @brief Insere um novo elemento na heap mínima.
 * 
 * Insere um novo item na heap, mantendo a propriedade de heap mínima. Se a heap estiver cheia,
 * o menor elemento é substituído pelo novo item se ele for maior que o atual elemento mínimo.
 * 
 * @param heap O apontador para a heap.
 * @param item O item a ser inserido na heap.
 * @param destroiDados A função que destrói o item se ele for removido.
 */
void heap_insere(MinHeap *heap, void *item, DestroiDados destroiDados);


#endif
