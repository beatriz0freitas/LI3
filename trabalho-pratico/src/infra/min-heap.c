#include "min-heap.h"

// Estrutura da heap genérica
struct MinHeap{
    void **dados;         // Array de apontadores para armazenar os dados
    int tamanho;          // Número de elementos atualmente na heap
    int capacidade;       // Capacidade máxima da heap
    Comparador comparador; // Função de comparação
};

MinHeap *heap_nova(int capacidade, Comparador comparador) {
    MinHeap *heap = malloc(sizeof(MinHeap));
    heap->dados = malloc(sizeof(void *) * capacidade);
    heap->tamanho = 0;
    heap->capacidade = capacidade;
    heap->comparador = comparador;
    return heap;
}

void heap_destroi(MinHeap *heap, DestroiDados destroiDados) {
    if (destroiDados) {
    for (int i = 0; i < heap->tamanho; i++) {
        destroiDados(heap->dados[i]);
    }
    }
    free(heap->dados);
    free(heap);
}

void troca(void **a, void **b) {
    void *temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(MinHeap *heap, int index) {
    int pai = (index - 1) / 2;
    if (index > 0 && heap->comparador(heap->dados[index], heap->dados[pai]) < 0) {
        troca(&heap->dados[index], &heap->dados[pai]);
        heapify_up(heap, pai);
    }
}

void heapify_down(MinHeap *heap, int index) {
    int menor = index;
    int esquerdo = 2 * index + 1;
    int direito = 2 * index + 2;

    if (esquerdo < heap->tamanho && heap->comparador(heap->dados[esquerdo], heap->dados[menor]) < 0) {
        menor = esquerdo;
    }
    if (direito < heap->tamanho && heap->comparador(heap->dados[direito], heap->dados[menor]) < 0) {
        menor = direito;
    }
    if (menor != index) {
        troca(&heap->dados[index], &heap->dados[menor]);
        heapify_down(heap, menor);
    }
}

void heap_insere(MinHeap *heap, void *item, DestroiDados destroiItem) {
    if (heap->tamanho < heap->capacidade) {
        heap->dados[heap->tamanho] = item;
        heapify_up(heap, heap->tamanho);
        heap->tamanho++;
    } else if (heap->comparador(item, heap->dados[0]) > 0) { // Substitui o menor elemento (raiz) se o novo item for maior
        destroiItem (heap->dados[0]);
        heap->dados[0] = item;
        heapify_down(heap, 0);
    } else {
        destroiItem(item);
    }
}

void *heap_remove_min(MinHeap *heap) {
    if (heap->tamanho == 0) {
        return NULL;
    }
    void *min = heap->dados[0];
    heap->dados[0] = heap->dados[heap->tamanho - 1];
    heap->tamanho--;
    heapify_down(heap, 0);
    return min;
}


void *min_heap_get_dados_por_indice(const MinHeap *heap, int index) {
    if (index < 0 || index >= heap->tamanho) {
        return NULL;
    }
    return heap->dados[index];
}

int min_heap_get_tamanho(const MinHeap *heap) {
    return heap->tamanho;
}

