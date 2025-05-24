#include "utils.h"

char *utils_segundos_para_string(int seg) {

    if (seg < 0)
        return NULL;
    
    int horas = seg / 3600;
    int minutos = (seg % 3600) / 60;
    int segundos = seg % 60;
    
    char *resultado = (char *)malloc(9 * sizeof(char));
    if (resultado == NULL) 
        return NULL;

    snprintf(resultado, 9, "%02d:%02d:%02d", horas, minutos, segundos);
    return resultado;
}


char *utils_remove_caracteres_inicio_e_fim(char *string, int inicio, int fim){
    gchar *stringSemCaracteres = g_strndup(string + inicio, strlen(string) - fim - 1);
    return stringSemCaracteres;
}

void utils_remove_aspas(char *coluna){
    size_t tamanho = strlen(coluna);
    if (coluna[0] == '"' && coluna[tamanho - 1] == '"') {
    
        memmove(coluna, coluna + 1, tamanho - 2); // Remove aspas iniciais
        coluna[tamanho - 2] = '\0';               // Remove aspas finais
    }
}


gboolean utils_valida_formato_horas(char* duracaoMusica){
    if (strlen (duracaoMusica) != 8)
        return FALSE;
    if (duracaoMusica[2] != ':' || duracaoMusica[5] != ':')
        return FALSE;
    if (!isdigit(duracaoMusica[0]) || !isdigit(duracaoMusica[1]) ||   // hh
        !isdigit(duracaoMusica[3]) || !isdigit(duracaoMusica[4]) ||   // mm
        !isdigit(duracaoMusica[6]) || !isdigit(duracaoMusica[7])) {   // ss
        return FALSE;
    }
    return TRUE;
}

  gboolean utils_valida_valores_horas (char* duracaoMusica) {
    int horas = (duracaoMusica[0] - '0')*10 + (duracaoMusica[1] - '0');
    int minutos = (duracaoMusica[3] - '0') * 10 + (duracaoMusica[4] - '0');
    int segundos = (duracaoMusica[6] - '0') * 10 + (duracaoMusica[7] - '0');

    if (horas < 0 || horas > 99) 
        return FALSE;
    if (minutos < 0 || minutos > 59) 
        return FALSE;
    if (segundos < 0 || segundos > 59) 
        return FALSE;
    return TRUE;
}

gboolean utils_valida_parentises( char *lista) {
    int tamanho = strlen(lista);
    if (tamanho < 2) {
        return FALSE;
    }
    return lista[0] == '[' && lista[tamanho - 1] == ']';
}


int utils_valida_char(char c) {
    return (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}

int utils_valida_LstringChar(char c) {
    return (c >= 'a' && c <= 'z');
}

int utils_valida_RstringChar(char c) {
    return (c >= 'a' && c <= 'z');
}


gboolean utils_valida_email(const char *email) {
    const char *at = strchr(email, '@');
    if (at == NULL || at == email)  {
        return FALSE; 
    }
    const char *ponto = strchr(at + 1, '.');

    if (ponto == NULL || ponto == at + 1) {
        return FALSE; 
    }

    for (const char *p = email; p < at; p++)  {
        if (!utils_valida_char(*p)) {
            return FALSE; 
        }
    }

    for (const char *p = at + 1; p < ponto; p++) {
        if (!utils_valida_LstringChar(*p))  {
            return FALSE; 
        }
    }

    int rstringLen = strlen(ponto + 1);
    if (rstringLen < 2 || rstringLen > 3) {
        return FALSE; 
    }
  
    for (const char *p = ponto + 1; *p; p++) {
        if (!utils_valida_RstringChar(*p))   {
            return FALSE; 
        }
    }
    return TRUE;
}

char* utils_obtem_nome_ficheiro( char* caminho) {
    char* ultima_barra = strrchr(caminho, '/'); 
    if (ultima_barra) {
        ultima_barra++; 
    } else {
        ultima_barra = caminho; 
    }

    size_t comprimento = strlen(ultima_barra) - 4; 
    char* nomeFicheiro = (char*)malloc(comprimento + 1); 

    if (nomeFicheiro) {
        strncpy(nomeFicheiro, ultima_barra, comprimento);
        nomeFicheiro[comprimento] = '\0'; 
    }

    return nomeFicheiro;
}

gboolean utils_valida_duracao(char* duracaoMusica) {
    if (!utils_valida_formato_horas(duracaoMusica))
        return FALSE;
    if (!utils_valida_valores_horas(duracaoMusica))
        return FALSE;
    return TRUE;
}


short utils_converte_duracao_para_segundos( char* duracao) {

    short horas = 0;
    short minutos = 0;
    short segundos = 0;
    const char *apontador = duracao;

    //  Ler as horas
    while (*apontador && *apontador != ':') {
        if (isdigit(*apontador)) {
            horas = horas * 10 + (*apontador - '0');
        }
        apontador++;
    }

    // Avançar apontador até depois do ':'
    if (*apontador == ':') {
        apontador++;
    }

    // Ler minutos
    while (*apontador && *apontador != ':') {
        if (isdigit(*apontador)) {
            minutos = minutos * 10 + (*apontador - '0');
        }
        apontador++;
    }

    // Avança apontador  até depois do ':'
    if (*apontador == ':') {
        apontador++;
    }

    // Ler  os segundos
    while (*apontador) {
        if (isdigit(*apontador)) {
            segundos = segundos * 10 + (*apontador - '0');
        }
        apontador++;
    }
    
    return (horas * 3600) + (minutos * 60) + segundos;
}


int utils_calcular_numero_semana_juliana(GDate *data) {

    guint diasJulianos = g_date_get_julian(data);

    // Calcular o número absoluto da semana 
    int numeroSemanaJuliana = (diasJulianos) / 7; //diasJuliano +1 para ajustar o inicio da semana

    return numeroSemanaJuliana; 
}

int utils_calcula_idade(GDate *dataNascimento) {
    
    GDate *dataAtual = g_date_new();
    g_date_set_dmy(dataAtual, 9, 9, 2024);
    int idade = g_date_get_year(dataAtual) - g_date_get_year(dataNascimento);

    if (g_date_get_month(dataAtual) < g_date_get_month(dataNascimento) || 
        (g_date_get_month(dataAtual) == g_date_get_month(dataNascimento) && 
        g_date_get_day(dataAtual) < g_date_get_day(dataNascimento))) {
        idade--;
    }

    g_date_free(dataAtual);
    return idade;
}


void utils_g_slice_free_int(gpointer gp){
    g_slice_free(int, gp);
}