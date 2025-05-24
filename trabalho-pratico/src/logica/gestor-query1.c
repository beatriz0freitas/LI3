#include "gestor-query1.h"

Linha *gestor_query1_resumo_utilizador(Utilizador *utilizador)
{
    const char *email = utilizador_get_emailDoUtilizador(utilizador);
    const char *nome = utilizador_get_nomeDoUtilizador(utilizador);
    const char *apelido = utilizador_get_apelidoDoUtilizador(utilizador);
    short idade = utilizador_get_idadeDoUtilizador(utilizador);
    char *idadeStr = g_strdup_printf("%d", idade);
    const char *pais = utilizador_get_paisDeRegisto(utilizador);

    Linha *linha = resultado_query_linha_novo();
    resultado_query_linha_adiciona_celula(linha, email);
    resultado_query_linha_adiciona_celula(linha, nome);
    resultado_query_linha_adiciona_celula(linha, apelido);
    resultado_query_linha_adiciona_celula(linha, idadeStr);
    resultado_query_linha_adiciona_celula(linha, pais);

    g_free(idadeStr);

    return linha;
}

Linha *gestor_query1_resumo_artista(Artista *artista)
{
    const char *nome = artista_get_nomeArtista(artista);
    const char *tipo = artista_tipo_para_string(artista_get_tipoArtista(artista));
    const char *pais = artista_get_nacionalidadeArtista(artista);
    short numeroAlbuns = artista_get_numeroDeAlbuns(artista);
    char *numeroAlbunsDup = g_strdup_printf("%d", numeroAlbuns);
    float profitTotal = artista_get_profitTotal(artista);
    char *profitTotalDup = g_strdup_printf("%.2f", profitTotal);

    Linha *linha = resultado_query_linha_novo();
    resultado_query_linha_adiciona_celula(linha, nome);
    resultado_query_linha_adiciona_celula(linha, tipo);
    resultado_query_linha_adiciona_celula(linha, pais);
    resultado_query_linha_adiciona_celula(linha, numeroAlbunsDup);
    resultado_query_linha_adiciona_celula(linha, profitTotalDup);

    g_free(numeroAlbunsDup);
    g_free(profitTotalDup);

    return linha;
}

ResultadoQuery *gestor_query1_executa(Comando *comando, Dados *dados)
{
    char *idStr = comando_get_argumento_por_indice(comando, 0);
    if (idStr == NULL) { 
        return NULL;
    }

    if (strlen(idStr) < 2 || (idStr[0] != 'U' && idStr[0] != 'A')) { 
        return NULL;
    }

    int id = atoi(idStr + 1);
    
    ResultadoQuery *resultado = resultado_query_novo();
    if (resultado == NULL) {        
        return NULL;
    }

    if (idStr[0] == 'U')
    {
        RepositorioUtilizadores *repositorioUtilizadores = dados_get_repositorioUtilizadores(dados);
        Utilizador *utilizador = repositorio_utilizadores_get(repositorioUtilizadores, id);
        if (utilizador == NULL){
            g_free(idStr);
            return resultado;
        }

        Linha *linha = gestor_query1_resumo_utilizador(utilizador);
        resultado_query_adiciona_linha(resultado, linha);
    }
    else if (idStr[0] == 'A')
    {
        RepositorioArtistas *repositorioArtistas = dados_get_repositorioArtistas(dados);
        Artista *artista = repositorio_artistas_get_artista_por_id(repositorioArtistas, id);
        if (artista == NULL){
            g_free(idStr);
            return resultado;
        }

        Linha *linha = gestor_query1_resumo_artista(artista);
        resultado_query_adiciona_linha(resultado, linha);
    }
    g_free(idStr);
    return resultado;
}
