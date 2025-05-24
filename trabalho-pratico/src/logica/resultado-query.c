#include "resultado-query.h"

 struct Linha
{
    GPtrArray *celulas;
};

struct ResultadoQuery
{
    GPtrArray *linhas;
};

Linha *resultado_query_linha_novo()
{
    Linha *linha = g_new(Linha, 1);
    linha->celulas = g_ptr_array_new_with_free_func(g_free);
    return linha;
}

void resultado_query_linha_destroi(Linha *linha) {
    if (linha) {
        g_ptr_array_free(linha->celulas, TRUE);
        g_free(linha);
    }
}

void resultado_query_linha_adiciona_celula(Linha *linha, const char *celula)
{
    if (celula == NULL)
        return;
    g_ptr_array_add(linha->celulas, g_strdup(celula));
}


ResultadoQuery *resultado_query_novo()
{
    ResultadoQuery *tabelaResposta = g_new(ResultadoQuery, 1);
    tabelaResposta->linhas = g_ptr_array_new_with_free_func((GDestroyNotify)resultado_query_linha_destroi);
    return tabelaResposta;
}


void resultado_query_destroi(ResultadoQuery *tabelaResposta){
    if (tabelaResposta == NULL)
    {
        return;
    }
    g_ptr_array_free(tabelaResposta->linhas, TRUE);
    g_free(tabelaResposta);
}

void resultado_query_adiciona_linha(ResultadoQuery *tabelaResposta, Linha *linha)
{
    g_ptr_array_add(tabelaResposta->linhas, linha);
}

char *resultado_query_toString(void *tabelaRespostas, const char *delimitador) {

    ResultadoQuery *tabelaResposta = (ResultadoQuery *)tabelaRespostas;

    if (tabelaRespostas == NULL || tabelaResposta->linhas == NULL || tabelaResposta->linhas->len == 0) 
        return g_strdup(""); 

    GString *resultado = g_string_new("");
    guint num_linhas = tabelaResposta->linhas->len;

    for (guint i = 0; i < num_linhas; i++) {
        Linha *linha = g_ptr_array_index(tabelaResposta->linhas, i);

        if (linha == NULL || linha->celulas == NULL || linha->celulas->len == 0) 
            continue; // salta para a próxima linha, se inválida
        
        guint num_celulas = linha->celulas->len;

        for (guint j = 0; j < num_celulas; j++) {
            char *valor = g_ptr_array_index(linha->celulas, j);
            
            if (valor == NULL) 
                valor = "";
                
            if (j > 0)  {
                g_string_append(resultado, delimitador);
            }
            g_string_append(resultado, valor);
        }

        if (i < num_linhas - 1) {
            g_string_append(resultado, "\n");
        }
    }

    return g_string_free(resultado, FALSE); // Retorna a string final sem libertar a memória interna da GString
}


//compara por ordem decrescente do segundo elemento e desempata por ordem alfabetica do primeiro 
int compara_linhas_decrescente_alfabetico(const void *a, const void *b)
{
    Linha *linha_a = *(Linha **)a;
    Linha *linha_b = *(Linha **)b;

    char *primeiro_elemento_a = g_ptr_array_index(linha_a->celulas, 0);
    char *primeiro_elemento_b = g_ptr_array_index(linha_b->celulas, 0);

    char *segundo_elemento_a_str = g_ptr_array_index(linha_a->celulas, 1);
    char *segundo_elemento_b_str = g_ptr_array_index(linha_b->celulas, 1);

    int segundo_elemento_a = atoi(segundo_elemento_a_str);
    int segundo_elemento_b = atoi(segundo_elemento_b_str);

    if (segundo_elemento_a != segundo_elemento_b)
    {
        return segundo_elemento_b - segundo_elemento_a; // Ordem decrescente 
    }

    return g_strcmp0(primeiro_elemento_a, primeiro_elemento_b);  // ordem alfabética
}

void resultado_query_ordena(ResultadoQuery *result, GCompareFunc compare_func)
{
    if (result == NULL || result->linhas == NULL || compare_func == NULL)
    {
        return;
    }
    g_ptr_array_sort(result->linhas, compare_func);
}
