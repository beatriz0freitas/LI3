#include "gestor-de-queries.h"

struct GestorDeQueries {
    Estatisticas *estatisticas;
};  

GestorDeQueries *gestor_queries_novo(Estatisticas *estatisticas){
    GestorDeQueries *gestor = g_new(GestorDeQueries, 1);
    gestor->estatisticas = estatisticas;
    return gestor;
}

void gestor_queries_destroi(GestorDeQueries *gestor){

    g_free(gestor);
}

ResultadoQuery *gestor_queries_executa(GestorDeQueries *gestorqueries, Comando *comando, Dados *dados){
    
    int numeroDaQuery = comando_get_numero_query(comando);
    const char *delimitador = comando_get_separador(comando);
    int numeroComando = comando_get_numero_comando (comando);

    ResultadoQuery * resultado = NULL;
    switch (numeroDaQuery) {
    case 1:
        estatisticas_inicia_contagem(gestorqueries->estatisticas, "Query1");
        resultado = gestor_query1_executa(comando, dados);
        estatisticas_termina_contagem(gestorqueries->estatisticas, "Query1");
        break;
    case 2:
        estatisticas_inicia_contagem(gestorqueries->estatisticas, "Query2");
        resultado = gestor_query2_executa(comando, dados);
        estatisticas_termina_contagem(gestorqueries->estatisticas, "Query2");
        break;
    case 3:
        estatisticas_inicia_contagem(gestorqueries->estatisticas, "Query3");
        resultado = gestor_query3_executa(comando, dados);
        estatisticas_termina_contagem(gestorqueries->estatisticas, "Query3");
        break;
    case 4:
        estatisticas_inicia_contagem(gestorqueries->estatisticas, "Query4");
        resultado = gestor_query4_executa(comando, dados);
        estatisticas_termina_contagem(gestorqueries->estatisticas, "Query4");
        break;
    case 5:
        estatisticas_inicia_contagem(gestorqueries->estatisticas, "Query5");
        resultado = gestor_query5_executa(comando, dados);
        estatisticas_termina_contagem(gestorqueries->estatisticas, "Query5");
        break;
    case 6:
        estatisticas_inicia_contagem(gestorqueries->estatisticas, "Query6");
        resultado = gestor_query6_executa(comando, dados);
        estatisticas_termina_contagem(gestorqueries->estatisticas, "Query6");
        break;
    }

    return resultado;
}

Estatisticas *gestor_queries_get_estatisticas (GestorDeQueries *gestorQueries){
    return gestorQueries->estatisticas;
}