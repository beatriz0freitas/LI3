
#include <sys/resource.h>
#include "gestor-de-programa.h"
#include "utils.h"

#define BUFFER_SIZE 1024 // Tamanho do buffer para leitura
#define MAX_DISCREPANCIA 1024
#define MAX_TEMP 1024

void gestor_programa_testes_prints_carregamentos(Estatisticas *estatisticas)
{
    const char *itens[] = {"CarregamentoArtistas", "CarregamentoMusicas", "CarregamentoUtilizadores", "CarregamentoAlbuns", "CarregamentoHistorico"};

    for (int i = 0; i < 5; i++)
    {
        EstatisticasItem *item = estatisticas_get_item(estatisticas, itens[i]);
        printf("Tempo total de %s: %f segundos\n", itens[i], estatisticas_item_get_tempo_de_execucao(item));
    }
}

void gestor_programa_testes_print_uso_memoria()
{
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    printf("Memória utilizada: %.2f MB\n", usage.ru_maxrss / 1024.0);
}

int gestor_programa_testes_compara_ficheiros(FILE *file1, FILE *file2, int *linha_discrepancia)
{
    char buffer1[BUFFER_SIZE];
    char buffer2[BUFFER_SIZE];
    int linha = 1;

    while (fgets(buffer1, BUFFER_SIZE, file1) != NULL && fgets(buffer2, BUFFER_SIZE, file2) != NULL)
    {
        if (strcmp(buffer1, buffer2) != 0)
        {
            *linha_discrepancia = linha;
            return 0;
        }
        linha++;
    }

    if ((fgets(buffer1, BUFFER_SIZE, file1) != NULL) || (fgets(buffer2, BUFFER_SIZE, file2) != NULL))
    {
        *linha_discrepancia = linha;
        return 0;
    }
    return 1;
}

void gestor_programa_testes_exibir_tempo_query(int numeroQuery, EstatisticasItem *estatistica)
{
    if (estatistica && estatisticas_item_get_numero_de_execucoes(estatistica) > 0)
    {
        printf("\tQuery%d: %.6f segundos (em %d execuções)\n",
               numeroQuery,
               estatisticas_item_get_tempo_de_execucao(estatistica),
               estatisticas_item_get_numero_de_execucoes(estatistica));
    }
    else
    {
        printf("Nenhuma execução da Query%d foi registrada.\n", numeroQuery);
    }
}


void gestor_programa_testes_verificar_discrepancia(FILE *file1, FILE *file2, int query_num, int *total, int *success, char *discrepancias)
{
    int linha_discrepancia = 0;
    (*total)++;
    if (gestor_programa_testes_compara_ficheiros(file1, file2, &linha_discrepancia))
    {
        (*success)++;
    }
    else
    {
        char temp[MAX_TEMP];
        sprintf(temp, "Discrepância na query %d: linha %d\n", query_num, linha_discrepancia);
        strcat(discrepancias, temp);
    }
}


int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        fprintf(stderr, "Uso: %s <pastaDados> <caminhoFicheiroInput> <pastaResultadosEsperados>\n", argv[0]);
        return EXIT_FAILURE;
    }

    clock_t inicio = clock();
    char *pastaDados = argv[1];
    char *caminhoFicheiroInput = argv[2];
    char *pastaResultadosEsperados = argv[3];

    gboolean modoEconomiaMemoria = (argc <= 4 || strcasecmp(argv[4], "normal") != 0);

    printf("Modo de execução: %s\n", modoEconomiaMemoria ? "Economia de memória" : "Normal");

    Estatisticas *estatisticas = estatisticas_novo();
    GestorDePrograma *gestorPrograma = gestor_programa_novo(estatisticas, modoEconomiaMemoria);
    gestor_programa_executa(gestorPrograma, pastaDados, caminhoFicheiroInput);

    gestor_programa_testes_prints_carregamentos(estatisticas);

    for (int i = 1; i <= 6; i++)
    {
        char nomeItem[10];
        sprintf(nomeItem, "Query%d", i);
        EstatisticasItem *item = estatisticas_get_item(estatisticas, nomeItem);
        gestor_programa_testes_exibir_tempo_query(i, item);
    }

    FILE *ficheiroDeImput = fopen(caminhoFicheiroInput, "r");
    if (!ficheiroDeImput)
    {
        perror("Erro ao abrir o ficheiro de input");
        return EXIT_FAILURE;
    }

    int total[6] = {0}, success[6] = {0};
    char discrepancias[6][MAX_DISCREPANCIA] = {{0}};

    char buffer[BUFFER_SIZE];
    int query_number;

    for (int i = 1; fgets(buffer, sizeof(buffer), ficheiroDeImput); i++)
    {
        sscanf(buffer, "%d", &query_number);

        char file1_path[256], file2_path[256];
        sprintf(file1_path, "./resultados/command%d_output.txt", i);
        sprintf(file2_path, "%s/command%d_output.txt", pastaResultadosEsperados, i);

        FILE *file1 = fopen(file1_path, "r");
        FILE *file2 = fopen(file2_path, "r");

        if (!file1 || !file2)
        {
            fprintf(stderr, "Erro ao abrir ficheiros para o comando %d\n", i);
            if (file1) fclose(file1);
            if (file2) fclose(file2);
            continue;
        }

        gestor_programa_testes_verificar_discrepancia(file1, file2, query_number, &total[query_number - 1], &success[query_number - 1], discrepancias[query_number - 1]);

        fclose(file1);
        fclose(file2);
    }
    fclose(ficheiroDeImput);

    for (int i = 0; i < 6; i++)
    {
        printf("Q%d: %d de %d testes ok!\n%s", i + 1, success[i], total[i], discrepancias[i]);
    }

    clock_t fim = clock();
    printf("Tempo decorrido: %.6f segundos\n", (float)(fim - inicio) / CLOCKS_PER_SEC);
    gestor_programa_testes_print_uso_memoria();

    gestor_programa_destroi(gestorPrograma);

    return 0;
}
