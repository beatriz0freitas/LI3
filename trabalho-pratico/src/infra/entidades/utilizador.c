#include "utilizador.h"

// "username";"email";"first_name";"last_name";"birth_date";"country";"subscription_type";"liked_songs_id"
#define COLUNA_ID 0
#define COLUNA_EMAIL 1
#define COLUNA_NOME 2
#define COLUNA_APELIDO 3
#define COLUNA_DATA_NASCIMENTO 4
#define COLUNA_PAIS 5
#define COLUNA_TIPO_SUBSCRICAO 6
#define COLUNA_MUSICAS_GOSTADAS 7

struct Utilizador {
    char *emailDoUtilizador;
    char *nomeDoUtilizador;
    char *apelidoDoUtilizador;
    char *paisDeRegisto;
    int *idMusicasGostadas;
    int idDoUtilizador;
    short idadeUtilizador;
    short quantidadeMusicasGostadas;
};

Utilizador *utilizador_novo() {
    Utilizador *utilizador = g_slice_new0(Utilizador);
    utilizador->idMusicasGostadas = NULL;
    utilizador->quantidadeMusicasGostadas = 0;
    return utilizador;
}

void utilizador_destroi(gpointer gp) {
    Utilizador *utilizador = (Utilizador *)gp;
    if (utilizador == NULL) {
        return;
    }
    g_free(utilizador->emailDoUtilizador);
    g_free(utilizador->nomeDoUtilizador);
    g_free(utilizador->apelidoDoUtilizador);
    g_free(utilizador->paisDeRegisto);
    free(utilizador->idMusicasGostadas);
    g_slice_free(Utilizador, utilizador);
}

int utilizador_get_idDoUtilizador(Utilizador *utilizador) {
    return utilizador->idDoUtilizador;
}

const char *utilizador_get_emailDoUtilizador(Utilizador *utilizador) {
    return utilizador->emailDoUtilizador;
}

const char *utilizador_get_nomeDoUtilizador(Utilizador *utilizador) {
    return utilizador->nomeDoUtilizador;
}

const char *utilizador_get_apelidoDoUtilizador(Utilizador *utilizador) {
    return utilizador->apelidoDoUtilizador;
}

short utilizador_get_idadeDoUtilizador(Utilizador *utilizador) {
    return utilizador->idadeUtilizador;
}

const char *utilizador_get_paisDeRegisto(Utilizador *utilizador) {
    return utilizador->paisDeRegisto;
}

int utilizador_get_musicasGostadasPorIndice(Utilizador *utilizador, int indice) {
    if (indice < 0 || indice >= utilizador->quantidadeMusicasGostadas) {
        return -1; // Índice inválido
    }
    return utilizador->idMusicasGostadas[indice];
}

short utilizador_get_quantidadeDeMusicasGostadas(Utilizador *utilizador) {
    return utilizador->quantidadeMusicasGostadas;
}

TipoSubscricao utilizador_tipo_de_subscricao(char *subscricao) {
    if (g_strcmp0(subscricao, "normal") == 0)
        return NORMAL;
    else if (g_strcmp0(subscricao, "premium") == 0)
        return PREMIUM;
    else
        return UTILIZADOR_INVALIDO;
}

gboolean utilizador_valida(char **coluna, GDate *dataNascimento) {
    TipoSubscricao tipoSubscricao = utilizador_tipo_de_subscricao(coluna[COLUNA_TIPO_SUBSCRICAO]);
    if (tipoSubscricao == UTILIZADOR_INVALIDO)
        return FALSE;

    if (!g_date_valid(dataNascimento))
        return FALSE;

    GDate *dataAtual = g_date_new_dmy(9, 9, 2024);
    if (g_date_compare(dataNascimento, dataAtual) > 0) {
        g_date_free(dataAtual);
        return FALSE;
    }
    g_date_free(dataAtual);

    const char *email = coluna[COLUNA_EMAIL];
    if (!utils_valida_email(email)) {
        return FALSE;
    }
    return TRUE;
}

void utilizador_processa_musicas_gostadas(Utilizador *utilizador, const char *coluna) {
    gchar *coluna_sem_brackets = g_strndup(coluna + 2, strlen(coluna) - 3);
    gchar **liked_songs_ids = g_strsplit(coluna_sem_brackets, ", ", -1);

    // Contar o número de músicas
    short num_musicas = 0;
    while (liked_songs_ids[num_musicas] != NULL) {
        num_musicas++;
    }

    // Alocar memória apenas uma vez
    utilizador->idMusicasGostadas = malloc(num_musicas * sizeof(int));
    utilizador->quantidadeMusicasGostadas = num_musicas;

    for (short i = 0; i < num_musicas; i++) {
        gchar *liked_song_id = g_strndup(liked_songs_ids[i] + 2, strlen(liked_songs_ids[i]) - 2);
        utilizador->idMusicasGostadas[i] = atoi(liked_song_id);
        g_free(liked_song_id);
    }

    g_strfreev(liked_songs_ids);
    g_free(coluna_sem_brackets);
}

Utilizador *utilizador_constroi_de_linha(char **coluna) {
    GDate dataNascimento;
    int ano, mes, dia;

    if (sscanf(coluna[COLUNA_DATA_NASCIMENTO], "%d/%d/%d", &ano, &mes, &dia) != 3) {
        return NULL;
    }
    
    if(g_date_valid_dmy ((GDateDay)dia, (GDateMonth)mes, (GDateYear)ano) == FALSE){
        return NULL;
    }
    
    g_date_set_dmy(&dataNascimento, (GDateDay)dia, (GDateMonth)mes, (GDateYear)ano);

    if (!utilizador_valida(coluna, &dataNascimento)) {
        return NULL;
    }

    Utilizador *utilizador = utilizador_novo();

    utilizador->idDoUtilizador = atoi(coluna[COLUNA_ID] + 1); // Converter ID do utilizador
    utilizador->emailDoUtilizador = strdup(coluna[COLUNA_EMAIL]);
    utilizador->nomeDoUtilizador = strdup(coluna[COLUNA_NOME]);
    utilizador->apelidoDoUtilizador = strdup(coluna[COLUNA_APELIDO]);
    utilizador->idadeUtilizador = utils_calcula_idade(&dataNascimento);
    utilizador->paisDeRegisto = g_strdup(coluna[COLUNA_PAIS]);
    utilizador_processa_musicas_gostadas(utilizador, coluna[COLUNA_MUSICAS_GOSTADAS]);

    return utilizador;
}

char *utilizador_id_para_string(int id) {
    char *resultado = (char *)malloc(9 * sizeof(char));
    sprintf(resultado, "%c%07d", 'U', id);
    return resultado;
}
