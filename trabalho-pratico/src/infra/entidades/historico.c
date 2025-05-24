
#include "historico.h"
//"id";"user_id";"music_id";"timestamp";"duration";"platform"
#define COLUNA_ID 0
#define COLUNA_USER_ID 1
#define COLUNA_MUSIC_ID 2
#define COLUNA_TIMESTAMP 3
#define COLUNA_DURATION 4
#define COLUNA_PLATFORM 5


struct Historico{
    GDate *dataMusicaOuvida;
    int idRegistoHistorico;
    int idUtilizador;
    int idMusica;
    TipoPlataforma plataformaReproducao;
    short duracaoAudicaoMusicaSegundos;
    short horaOuvida;
};

Historico *historico_novo() {
    Historico *historico =g_slice_new0(Historico);
    return historico;
};

void historico_destroi(gpointer gp) {
    Historico *historico = (Historico *)gp;
    if (historico->dataMusicaOuvida != NULL) {
            g_date_free(historico->dataMusicaOuvida);  // Libera a memória alocada pelo GDate
    }
    g_slice_free(Historico,historico);
}

int historico_get_idRegistoHistorico(Historico *historico) {
    return historico->idRegistoHistorico;
}

int historico_get_idUtilizador(Historico *historico) {
    return historico->idUtilizador;
}

int historico_get_idMusica(Historico *historico) {
    return historico->idMusica;
}

GDate* historico_get_dataMusicaOuvida(Historico *historico) {
    return historico->dataMusicaOuvida; //TODO:ver encapsulamento aqui
}

short historico_get_horaMusicaOuvida (Historico *historico){
    return historico->horaOuvida;
}


short historico_get_duracaoAudicaoMusicaSegundos(Historico *historico) {
    return historico->duracaoAudicaoMusicaSegundos;
}


TipoPlataforma plataforma_tipo(char *tipo) {

    char *tipoSemAspas = utils_remove_caracteres_inicio_e_fim(tipo, 1, 2);
    
    if (strcasecmp(tipoSemAspas, "mobile") == 0) {
        g_free(tipoSemAspas);
        return MOBILE;
    } else if (strcasecmp(tipoSemAspas, "desktop") == 0) {
        g_free(tipoSemAspas);
        return DESKTOP;
    } else {
        g_free(tipoSemAspas);
        return PLATAFORMA_INVALIDA;
    }
}

gboolean historico_valida(char ** colunas)
{
    return (plataforma_tipo(colunas[COLUNA_PLATFORM]) != PLATAFORMA_INVALIDA) && 
           (utils_valida_duracao(colunas[COLUNA_DURATION]));
}

Historico *historico_constroi_de_linha(char **colunas){
    if (!historico_valida(colunas)){
        return NULL;
    }

    int dia, mes, ano, hora, minuto, segundo;
    const char *timestamp = colunas[COLUNA_TIMESTAMP];
    if (sscanf(timestamp, "%d/%d/%d %d:%d:%d", &ano, &mes, &dia, &hora, &minuto, &segundo) != 6) {
        return NULL;
    }

    Historico *historico = historico_novo();

    historico -> idRegistoHistorico = atoi(colunas[COLUNA_ID]+1);
    historico -> idUtilizador = atoi(colunas[COLUNA_USER_ID]+1);
    historico -> idMusica = atoi(colunas[COLUNA_MUSIC_ID]+1);
    historico -> duracaoAudicaoMusicaSegundos = utils_converte_duracao_para_segundos(colunas[COLUNA_DURATION]);
    historico->dataMusicaOuvida = g_date_new_dmy(dia, mes, ano);
    historico->horaOuvida = (short)hora;

    return historico;

}

