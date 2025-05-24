#include "gestor-programa-interativo.h"

#define ENTER_KEY 10
#define ESC_KEY 27

typedef enum{
    JANELA_SAIR = -1,
    JANELA_INICIAL = 0,
    JANELA_CONFIGURACOES = 1,
    JANELA_AJUDA = 2,
    JANELA_ESTATISTICAS = 3,
    JANELA_MENU = 4,
    JANELA_CONSOLA = 5
} TipoJanela;

struct GestorDeProgramaInterativo
{
    GestorDeQueries *gestorQueries;
    Estatisticas *estatisticas;
    EstadoProgramaInterativo *estado;
    Dados *dados;
};

struct EstadoProgramaInterativo
{
    WINDOW *janelaParaAnimacao;
    pthread_mutex_t mutex_carregamento;
    char *nomeUtilizador;
    TipoJanela janelaAtual;
    int linhaAtual;
    int dados_carregados;
    int tema;
};

EstadoProgramaInterativo *estado_programa_interativo_novo()
{
    EstadoProgramaInterativo *estado = g_new(EstadoProgramaInterativo, 1);

    estado->linhaAtual = 1;
    estado->dados_carregados = 0;
    pthread_mutex_init(&estado->mutex_carregamento, NULL);
    estado->janelaParaAnimacao = NULL;
    estado->janelaAtual = 0;
    estado->nomeUtilizador = malloc(128);

    return estado;
}

GestorDeProgramaInterativo *gestor_programa_interativo_novo()
{
    GestorDeProgramaInterativo *gestor = g_new(GestorDeProgramaInterativo, 1);
    Estatisticas *estatisticas = estatisticas_novo();
    gestor->gestorQueries = gestor_queries_novo(estatisticas);
    gestor->estatisticas = estatisticas;
    gestor->estado = estado_programa_interativo_novo();
    gestor->dados = dados_novo(NULL, NULL);
    return gestor;
}

void estado_programa_interativo_destroi(EstadoProgramaInterativo *estado)
{
    pthread_mutex_destroy(&estado->mutex_carregamento);
    free(estado);
}

void gestor_programa_interativo_destroi(GestorDeProgramaInterativo *gestorPrograma)
{
    gestor_queries_destroi(gestorPrograma->gestorQueries);
    estatisticas_destroi(gestorPrograma->estatisticas);
    estado_programa_interativo_destroi(gestorPrograma->estado);
    g_free(gestorPrograma);
}

GestorDeQueries *gestor_programa_interativo_get_gestor_queries(GestorDeProgramaInterativo *gestorDePrograma)
{
    return gestorDePrograma->gestorQueries;
}


//--------CONSOLA DE COMANDOS-----------

void gestor_programa_interativo_imprime_multiplas_linhas(WINDOW *janela, int linha_inicial, int coluna_inicial, const char *texto)
{

    if (!janela || !texto)
        return;

    char *texto_copia = strdup(texto);
    if (!texto_copia)
        return;

    int linha = linha_inicial;
    char *inicio_linha = texto_copia;
    char *posicao_quebra;

    while ((posicao_quebra = strchr(inicio_linha, '\n')) != NULL)
    {
        *posicao_quebra = '\0';
        mvwprintw(janela, linha, coluna_inicial, "%s", inicio_linha);
        *posicao_quebra = '\n';
        linha++;
        inicio_linha = posicao_quebra + 1;
    }

    if (*inicio_linha != '\0')
    {
        mvwprintw(janela, linha, coluna_inicial, "%s", inicio_linha);
    }

    free(texto_copia);
    wrefresh(janela);
}

void gestor_programa_interativo_consola_queries_escreve_estatisticas(GestorDeProgramaInterativo *gestor, WINDOW *janelaEstatisticas)
{
    werase(janelaEstatisticas);
    box(janelaEstatisticas, 0, 0);
    mvwprintw(janelaEstatisticas, 0, 2, "[ Estatísticas ]");
    char *estatisticasStr = estatisticas_to_string(gestor->estatisticas);
    gestor_programa_interativo_imprime_multiplas_linhas(janelaEstatisticas, 2, 2, estatisticasStr);
    wrefresh(janelaEstatisticas);
}

void gestor_programa_interativa_consola(GestorDeProgramaInterativo *gestor)
{
    initscr();
    curs_set(2);
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    mousemask(0, NULL); // Desativa eventos de rato

    int altura = LINES;
    int largura = COLS;
    int margemDasJanelas = 2;

    WINDOW *janela = newwin(altura, largura, 0, 0);
    box(janela, 0, 0);
    mvwprintw(janela, 0, 2, "[ Terminal interactivo de queries (ESC para sair) ] ");
    wrefresh(janela);

    int alturaFormulario = 3;

    int larguraFormulario = largura - 4;

    int alturaJanelaQuery = 5;
    int larguraJanelaQuery = largura - margemDasJanelas * 2;
    int yJanelaQuery = margemDasJanelas;
    int xJanelaQuery = margemDasJanelas;
    WINDOW *janelaQuery = derwin(janela,
                                 alturaJanelaQuery,
                                 larguraJanelaQuery,
                                 yJanelaQuery,
                                 xJanelaQuery);
    box(janelaQuery, 0, 0);
    mvwprintw(janelaQuery, 0, 2, "[ Query (ENTER para executar) ]");
    wrefresh(janelaQuery);

    int yJanelaOutput = yJanelaQuery + alturaJanelaQuery;
    int alturaRestante = altura - (yJanelaOutput + margemDasJanelas);

    int larguraJanelaOutput = (larguraJanelaQuery / 2);
    WINDOW *janelaOutputQuery = derwin(janela,
                                       alturaRestante,
                                       larguraJanelaOutput,
                                       yJanelaOutput,
                                       xJanelaQuery);
    box(janelaOutputQuery, 0, 0);
    mvwprintw(janelaOutputQuery, 0, 2, "[ Output da Query ]");
    wrefresh(janelaOutputQuery);

    int xJanelaEstatisticas = xJanelaQuery + larguraJanelaOutput;
    int larguraJanelaEst = larguraJanelaQuery - larguraJanelaOutput;
    WINDOW *janelaEstatisticas = derwin(janela,
                                        alturaRestante,
                                        larguraJanelaEst,
                                        yJanelaOutput,
                                        xJanelaEstatisticas);
    box(janelaEstatisticas, 0, 0);
    mvwprintw(janelaEstatisticas, 0, 2, "[ Estatísticas ]");
    wrefresh(janelaEstatisticas);

    gestor_programa_interativo_consola_queries_escreve_estatisticas(gestor, janelaEstatisticas);

    FIELD *campoQuery = new_field(1, larguraFormulario - 20, 2, 18, 0, 0);

    set_field_type(campoQuery, TYPE_REGEXP, ".*"); // permitir caracteres ""
    // set_field_back(campoQuery, A_UNDERLINE); //sublinhado
    //  set_field_back(campoQuery, A_BOLD );
    set_field_back(campoQuery, A_STANDOUT);
    field_opts_off(campoQuery, O_AUTOSKIP); // não salta para proximo caampo

    FIELD *fields[2];
    fields[0] = campoQuery;
    fields[1] = NULL;

    // Cria o formulário
    FORM *form = new_form(fields);

    set_form_win(form, janelaQuery);

    WINDOW *subForm = derwin(janelaQuery,
                             alturaFormulario,
                             larguraFormulario - 2,
                             1, 1);
    set_form_sub(form, subForm);
    keypad(subForm, TRUE);

    post_form(form);
    wrefresh(janelaQuery);

    int tecla;
    while ((tecla = wgetch(subForm)) != ESC_KEY)
    {
        if (tecla == 'B')
        {
            clear();
            refresh();
            wclear(janela);
            wrefresh(janela);
            unpost_form(form);
            free_form(form);
            free_field(campoQuery);
            delwin(subForm);
            delwin(janelaQuery);
            delwin(janelaOutputQuery);
            delwin(janelaEstatisticas);
            delwin(janela);
            gestor->estado->janelaAtual = JANELA_INICIAL;
            return;
        }
        else if (tecla == ENTER_KEY)
        {
            form_driver(form, REQ_VALIDATION);
            char *query = field_buffer(campoQuery, 0);

            Comando *comando = comando_constroi_de_linha(query);
            ResultadoQuery *resultadoQuery = gestor_queries_executa(gestor->gestorQueries, comando, gestor->dados);

            werase(janelaOutputQuery);
            box(janelaOutputQuery, 0, 0);
            mvwprintw(janelaOutputQuery, 0, 2, "[ Output da Query ]");
            const char *delimitador = comando_get_separador(comando);
            char *resultadoStr = resultado_query_toString(resultadoQuery, delimitador);
            mvwprintw(janelaOutputQuery, 2, 2, "Resultados da query: %s", query);
            if (strlen(resultadoStr) == 0)
            {
                resultadoStr = strdup("A query não devolveu resultados...\n");
            }
            gestor_programa_interativo_imprime_multiplas_linhas(janelaOutputQuery, 3, 4, resultadoStr);
            set_field_buffer(campoQuery, 0, "");
            wrefresh(janelaOutputQuery);

            gestor_programa_interativo_consola_queries_escreve_estatisticas(gestor, janelaEstatisticas);
        }
        else
        {
            switch (tecla)
            {
            // Impedir que o cursor saia do campo (setas, tabs)
            case KEY_DOWN:
            case KEY_UP:
            case KEY_BTAB: // Shift+Tab
            case 9:        // Tab
                break;

            // Tratar BACKSPACE / DELETE
            case KEY_BACKSPACE:
            case 127:
            case 8:
                form_driver(form, REQ_DEL_PREV);
                break;

            case KEY_DC: // Delete
                form_driver(form, REQ_DEL_CHAR);
                break;

            default:
                // Para qualquer outra tecla, repassa ao form
                form_driver(form, tecla);
                break;
            }
        }
        wrefresh(janelaQuery);
    }


    unpost_form(form);
    free_form(form);
    free_field(campoQuery);

    delwin(subForm);
    delwin(janelaQuery);
    delwin(janelaOutputQuery);
    delwin(janelaEstatisticas);

    delwin(janela);

    clear(); // Limpa toda a tela do terminal

    endwin();
}

//---------------------

void gestor_programa_interativo_fechar_programa(WINDOW *janela, WINDOW *barra)
{
    delwin(janela);
    delwin(barra);
    endwin();
    exit(0);
}

void gestor_programa_interativo_definir_esquemas_cores()
{
    init_pair(1, COLOR_WHITE, COLOR_BLUE);  // Tema 1: Branco no fundo azul
    init_pair(2, COLOR_BLACK, COLOR_GREEN); // Tema 2: Preto no fundo verde
    init_pair(3, COLOR_YELLOW, COLOR_RED);  // Tema 3: Amarelo no fundo vermelho
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    init_pair(5, COLOR_GREEN, COLOR_BLACK);
    init_pair(6, COLOR_RED, COLOR_BLACK);
    init_pair(7, COLOR_BLUE, COLOR_BLACK);
}

void gestor_programa_interativo_definir_tema_inverso(int pair_number)
{
    short cor_texto, cor_fundo;
    pair_content(pair_number, &cor_texto, &cor_fundo);
    int inverso_pair_number = pair_number + 100; 
    init_pair(inverso_pair_number, cor_fundo, cor_texto);  

}

void gestor_programa_interativo_aplicar_tema(WINDOW *janela, int tema)
{
    if (tema >= 1 && tema <= 7)
    {
        wbkgd(janela, COLOR_PAIR(tema));
        wrefresh(janela);
    }

}

int gestor_programa_interativo_menu_escolher_tema(WINDOW *janela)
{
    int escolha = 0;
    int tecla;
    int altura, largura;

    while (1)
    {
        wclear(janela);
        box(janela, 0, 0);
        getmaxyx(janela, altura, largura);

        gestor_programa_interativo_aplicar_tema(janela, escolha + 1); // Atualiza a prévia do tema selecionado

        mvwprintw(janela, altura / 2 - 8, (largura - 56) / 2, "--------------------------------------------------------\n");
        mvwprintw(janela, altura / 2 - 6, (largura - 56) / 2, "                     MENU INTERATIVO:                   \n");
        mvwprintw(janela, altura / 2 - 5, (largura - 56) / 2, "                Qual tema deseja exibir?                \n");
        mvwprintw(janela, altura / 2 - 3, (largura - 56) / 2, "--------------------------------------------------------\n");

        for (int i = 0; i < 6; i++)
        {
            mvwprintw(janela, altura / 2 + i, (largura - 56) / 2, "%s Tema %d", escolha == i ? "->" : "  ", i + 1);
        }

        wrefresh(janela);
        tecla = wgetch(janela);

        if (tecla == KEY_UP)
        {
            escolha = (escolha - 1 + 6) % 6; // Clique cíclico para cima
        }
        else if (tecla == KEY_DOWN)
        {
            escolha = (escolha + 1) % 6; // Clique cíclico para baixo
        }
        else if (tecla == '\n')
        {
            break; // Confirma escolha
        }
    }
    return escolha + 1; // Retorna o índice do tema escolhido
}

WINDOW *gestor_programa_inicializar_janela_principal(int altura, int largura, int starty, int startx, EstadoProgramaInterativo *estado)
{
    WINDOW *janela = newwin(altura, largura, starty, startx);
    keypad(janela, TRUE);
    box(janela, 0, 0);
    wrefresh(janela);
    estado->janelaParaAnimacao = janela;
    return janela;
}

int gestor_programa_interativo_verificar_clique(int x, int y, int x_inicio, int largura, int y_pos)
{
    return (x >= x_inicio && x <= (x_inicio + largura) && y == y_pos);
}

int gestor_programa_interativo_validar_caminho_dados(const char *caminho)
{
    FILE *arquivo = fopen(caminho, "r");
    if (arquivo)
    {
        fclose(arquivo);
        return 1; 
    }
    return 0; 
}

void animacao_carregamento(EstadoProgramaInterativo *estado)
{
    const int tamanhoBarraProgresso = 60;
    int progresso = 0;

    if (!estado || !estado->janelaParaAnimacao)
    {
        fprintf(stderr, "Erro: Estado ou janela inválidos.\n");
        return;
    }

    WINDOW *janela = estado->janelaParaAnimacao;

    while (progresso <= 100)
    { 
        pthread_mutex_lock(&estado->mutex_carregamento);
        if (estado->dados_carregados)
        {
            pthread_mutex_unlock(&estado->mutex_carregamento);
            break;
        }
        pthread_mutex_unlock(&estado->mutex_carregamento);

        wclear(janela);
        box(janela, 0, 0);
        mvwprintw(janela, 10, 5, "Carregamento de dados em progresso...");
        mvwprintw(janela, 11, 5, "[");

        for (int i = 0; i < tamanhoBarraProgresso; ++i)
        {
            if (i < (progresso * tamanhoBarraProgresso / 100))
            { // Calcula o preenchimento proporcional ao progresso
                waddch(janela, '|');
            }
            else
            {
                waddch(janela, ' ');
            }
        }
        wprintw(janela, "]");
        mvwprintw(janela, 12, 5, "%d%%", progresso);
        wrefresh(janela);

        progresso++;    // Incrementa o progresso em 1%
        usleep(140000); // Aumenta o tempo de espera para desacelerar a animação
    }

    wclear(janela);
    box(janela, 0, 0);
    mvwprintw(janela, 10, 5, "Carregamento concluído!");
    wrefresh(janela);
}

void gestor_programa_interativo_carregar_dados(GestorDeProgramaInterativo *gestor, WINDOW *janela)
{
    box(janela, 0, 0);
    char pastaDados[256] = {0};
    mvwprintw(janela, 2, 5, "Introduza o caminho dos ficheiros de dados:");
    echo();
    wgetnstr(janela, pastaDados, sizeof(pastaDados) - 1);
    noecho();

    if (!gestor_programa_interativo_validar_caminho_dados(pastaDados))
    {
        mvwprintw(janela, 4, 5, "Caminho de ficheiros de dados inválido!");
        mvwprintw(janela, 5, 5, "O caminho utilizado será: dataset/com_erros");
        strncpy(pastaDados, "dataset/com_erros", sizeof(pastaDados) - 1);
        wgetch(janela);
    }

    wclear(janela);
    box(janela, 0, 0);
    wrefresh(janela);
    pthread_t animacao_thread;

    EstadoProgramaInterativo *estado = gestor->estado;

    // Cria a thread para a animação
    pthread_create(&animacao_thread, NULL, (void *)animacao_carregamento, (void *)estado);

    dados_carregar(gestor->estatisticas, pastaDados, gestor->dados);

    // Atualiza o estado para indicar que o carregamento foi concluído
    pthread_mutex_lock(&estado->mutex_carregamento);
    estado->dados_carregados = 1;
    pthread_mutex_unlock(&estado->mutex_carregamento);

    // Aguarda a animação terminar
    pthread_join(animacao_thread, NULL);
}

Comando *gestor_programa_interativo_cria_comando(GestorDeProgramaInterativo *gestor, int query, char *tituloQuery, int numeroDeArgumentos, char **nomeDosArgumentos)
{

    int altura = 20, largura = 80, starty = (LINES - altura) / 2, startx = (COLS - largura) / 2;
    WINDOW *janela = newwin(altura, largura, starty, startx);
    gestor_programa_interativo_aplicar_tema(janela, gestor->estado->tema);
    box(janela, 0, 0);
    wrefresh(janela);

    mvwprintw(janela, 2, 5, "Query %d: %s", query, tituloQuery);

    Comando *comando = comando_novo();
    comando_set_numero_query(comando, query);

    char **argumentos = malloc(numeroDeArgumentos * sizeof(char));

    for (int i = 0; i < numeroDeArgumentos; ++i)
    {
        size_t length = 0;
        argumentos[i] = malloc(256);

        mvwprintw(janela, 4 + i, 5, "%s", nomeDosArgumentos[i]);
        echo();
        wgetnstr(janela, argumentos[i], 255);
        noecho();

        comando_adiciona_argumento(comando, argumentos[i]);
    }

    // Atualizar e fechar a janela
    wclear(janela);
    box(janela, 0, 0);
    mvwprintw(janela, 10, 5, "Comando criado com sucesso! Pressione qualquer tecla para continuar.");
    wrefresh(janela);
    wgetch(janela);

    for (int i = 0; i < numeroDeArgumentos; ++i)
    {
        free(argumentos[i]);
    }
    free(argumentos);

    delwin(janela);

    return comando;
}

//-------------- MENUS----------------

int exibir_menu(WINDOW *janela, GestorDeProgramaInterativo *gestor)
{
    int tema = gestor->estado->tema;
    gestor_programa_interativo_definir_tema_inverso(tema);
    int temaInverso = tema + 100;


    char *opcoes[] = {
        "1. Executar Query 1",
        "2. Executar Query 2",
        "3. Executar Query 3",
        "4. Executar Query 4",
        "5. Executar Query 5",
        "6. Executar Query 6",
        "E. Sair"};

    int num_opcoes = sizeof(opcoes) / sizeof(opcoes[0]);
    int opcaoSelecionada = 0;
    int tecla;

    while (1)
    {
        wclear(janela);
        box(janela, 0, 0);

        int altura, largura;
        getmaxyx(janela, altura, largura);

        mvwprintw(janela, altura / 2 - 8, (largura - 56) / 2, "--------------------------------------------------------\n");
        mvwprintw(janela, altura / 2 - 6, (largura - 56) / 2, "                     MENU INTERATIVO:                   \n");
        mvwprintw(janela, altura / 2 - 5, (largura - 56) / 2, "                Qual query deseja executar?             \n");
        mvwprintw(janela, altura / 2 - 3, (largura - 56) / 2, "--------------------------------------------------------\n");

        // Exibe o menu
        for (int i = 0; i < num_opcoes; ++i)
        {
            if (i == opcaoSelecionada)
            {
                wattron(janela, COLOR_PAIR(temaInverso)); // Cor para o item selecionado
                mvwprintw(janela, (altura / 2) + i, 5, "%s", opcoes[i]);
                wattroff(janela, COLOR_PAIR(temaInverso));
            }
            else
            {
                wattron(janela, COLOR_PAIR(tema)); // Cor para os itens não selecionados
                mvwprintw(janela, (altura / 2) + i, 5, "%s", opcoes[i]);
                wattroff(janela, COLOR_PAIR(tema));
            }
        }

        wrefresh(janela);
        tecla = wgetch(janela);

        if (tecla == KEY_UP)
        {
            opcaoSelecionada = (opcaoSelecionada - 1 + num_opcoes) % num_opcoes; // Move para cima (circular)
        }
        else if (tecla == KEY_DOWN)
        {
            opcaoSelecionada = (opcaoSelecionada + 1) % num_opcoes; // Move para baixo (circular)
        }
        else if (tecla == 10)
        { // Tecla Enter
            if (opcaoSelecionada == num_opcoes - 1)
            {
                wclear(janela);
                box(janela, 0, 0);
                mvwprintw(janela, 15, (largura - 56), "A sair do menu de queries");
                wrefresh(janela);
                wgetch(janela);
                return -1;
            }
            return opcaoSelecionada + 1;
        }
    }
}

//------------ JANELAS --------------

void gestor_programa_interativo_janela_inicial(WINDOW *janela, GestorDeProgramaInterativo *gestor)
{
    mousemask(ALL_MOUSE_EVENTS, NULL);
    wclear(janela);
    box(janela, 0, 0);

    int altura, largura;
    getmaxyx(janela, altura, largura);

    mvwprintw(janela, altura / 2 - 8, (largura - 56) / 2, "--------------------------------------------------------");
    mvwprintw(janela, altura / 2 - 6, (largura - 56) / 2, "                       Bem-vindo!!                      ");
    mvwprintw(janela, altura / 2 - 4, (largura - 56) / 2, "Resposta de Queries sobre sistema de streaming de música");
    mvwprintw(janela, altura / 2 - 2, (largura - 56) / 2, "                Grupo 73 - LI3 2024/2025                ");
    mvwprintw(janela, altura / 2 + 2, (largura - 56) / 2, "--------------------------------------------------------");
    mvwprintw(janela, altura / 2 + 4, (largura - 56) / 2, "   Clique com o mousepad no modo que pretende utilizar  ");
    mvwprintw(janela, altura / 2 + 5, (largura - 56) / 2, "       [Menu Interativo]             [Consola]          ");

    wrefresh(janela);

}

void gestor_programa_principal_janela_ajuda(WINDOW *janela)
{
    wclear(janela);
    box(janela, 0, 0);

    int altura, largura;
    getmaxyx(janela, altura, largura);

    mvwprintw(janela, altura / 2 - 8, (largura - 56) / 2, "--------------------------------------------------------");
    mvwprintw(janela, altura / 2 - 6, (largura - 56) / 2, "                     AJUDA INTERATIVA:                  ");
    mvwprintw(janela, altura / 2 - 4, (largura - 56) / 2, "--------------------------------------------------------");
    mvwprintw(janela, altura / 2, (largura - 56) / 2, " [S] Configurar Menu | [H] Ajuda | [E] Estatísticas ");
    mvwprintw(janela, altura / 2 + 2, (largura - 56) / 2, "[KEY UP] subir | [KEY_DOWN] descer | [ENTER] selecionar ");
    mvwprintw(janela, altura / 2 + 4, (largura - 56) / 2, "             [B] Menu Inicial | [Esc] Sair              ");
    mvwprintw(janela, altura / 2 + 6, (largura - 56) / 2, "--------------------------------------------------------");
    wrefresh(janela);
}

void gestor_programa_principal_janela_configuracoes(WINDOW *janela, GestorDeProgramaInterativo *gestor)
{
    wclear(janela);
    box(janela, 0, 0);

    int altura, largura;
    getmaxyx(janela, altura, largura);

    mvwprintw(janela, altura / 2 - 8, (largura - 56) / 2, "--------------------------------------------------------");
    mvwprintw(janela, altura / 2 - 6, (largura - 56) / 2, "             CONFIGURACOES DO PROGRAMA:                 ");
    mvwprintw(janela, altura / 2 - 4, (largura - 56) / 2, "--------------------------------------------------------");
    mvwprintw(janela, altura / 2 + 2, (largura - 56) / 2, "             [1] Escolher tema de cores                 ");
    mvwprintw(janela, altura / 2 + 4, (largura - 56) / 2, "     Pressione 'B' para voltar à janela inicial         ");
    mvwprintw(janela, altura / 2 + 6, (largura - 56) / 2, "--------------------------------------------------------");
    wrefresh(janela);

    int tecla = wgetch(janela);

    if (tecla == '\n' || tecla == '1')
    { 
        int temaSelecionado = gestor_programa_interativo_menu_escolher_tema(janela);
        gestor_programa_interativo_aplicar_tema(janela, temaSelecionado);
        gestor->estado->tema = temaSelecionado;
    }
    else if (tecla == 'B' || tecla == 'b')
    {
        gestor->estado->janelaAtual = JANELA_INICIAL;
    }
}

void gestor_programa_principal_janela_estatisticas(WINDOW *janela, GestorDeProgramaInterativo *gestor)
{
    wclear(janela);
    box(janela, 0, 0);

    mvwprintw(janela, 0, 2, "[ Estatísticas ]");

    gestor_programa_interativo_consola_queries_escreve_estatisticas(gestor, janela);

    int altura, largura;
    getmaxyx(janela, altura, largura);
    mvwprintw(janela, altura - 2, (largura - 30) / 2, "[Pressione 'B' para voltar]");

    wrefresh(janela);

    int tecla;
    while ((tecla = wgetch(janela)) != 'B'  && tecla != 'b')
    {
       
    }
    gestor->estado->janelaAtual = JANELA_INICIAL;
}

//-------------------------------

void gestor_programa_interativo_imprime_query(ResultadoQuery *resultadoQuery, Comando *comando, WINDOW *janelaOutputQuery)
{
    werase(janelaOutputQuery);
    box(janelaOutputQuery, 0, 0);
    mvwprintw(janelaOutputQuery, 0, 2, "[ Output da Query ]");

    const char *delimitador = comando_get_separador(comando);
    char *resultadoStr = resultado_query_toString(resultadoQuery, delimitador);

    int query = comando_get_numero_query(comando);

    mvwprintw(janelaOutputQuery, 2, 2, "Resultados da query  %d:", query);

    if (strlen(resultadoStr) == 0)
    {
        resultadoStr = strdup("A query não devolveu resultados...\n");
    }

    gestor_programa_interativo_imprime_multiplas_linhas(janelaOutputQuery, 3, 4, resultadoStr);
    free(resultadoStr);

    wrefresh(janelaOutputQuery);
    wgetch(janelaOutputQuery); 
}

void gestor_programa_interativo_janela_menu(WINDOW *janela, GestorDeProgramaInterativo *gestorProgramaInterativo)
{
    mousemask(0, NULL);

    int opcaoSelecionada = exibir_menu(janela, gestorProgramaInterativo); 

    if (opcaoSelecionada == -1)
    { 
        gestorProgramaInterativo->estado->janelaAtual = JANELA_INICIAL;
        return;
    }

    Comando *comando = NULL;

    switch (opcaoSelecionada)
    {
    case 1:
        comando = gestor_programa_interativo_cria_comando(gestorProgramaInterativo, 1,
                                                          "Listar o resumo de um utilizador ou artista",
                                                          1, (char *[]){"Introduza um ID (Uxxxxxxx ou Axxxxxxx): "});
        break;
    case 2:
        comando = gestor_programa_interativo_cria_comando(gestorProgramaInterativo, 2,
                                                          "Top N artistas com maior discografia",
                                                          2, (char *[]){"Introduza o número de artistas a avaliar: ", "(Opcional) Introduza o país de origem: "});
        break;
    case 3:
        comando = gestor_programa_interativo_cria_comando(gestorProgramaInterativo, 3,
                                                          "Géneros de música mais populares numa faixa etária",
                                                          2, (char *[]){"Introduza a idade mínima: ", "Introduza a idade máxima: "});
        break;
    case 4:
        comando = gestor_programa_interativo_cria_comando(gestorProgramaInterativo, 4,
                                                          "Artista no top 10 mais vezes",
                                                          1, (char *[]){"Introduza o intervalo de datas a considerar (): "});
        break;
    case 5:
        comando = gestor_programa_interativo_cria_comando(gestorProgramaInterativo, 5,
                                                          "Recomendação de utilizadores com gostos parecidos",
                                                          2, (char *[]){"Introduza o ID do utilizador (Uxxxxxxx): ", "Introduza o número de utilizadores a retornar: "});
        break;
    case 6:
        comando = gestor_programa_interativo_cria_comando(gestorProgramaInterativo, 6,
                                                          "Resumo anual para um utilizador",
                                                          3, (char *[]){"Introduza o ID do utilizador (Uxxxxxxx): ", "Introduza o ano a analisar: ", "Introduza o número de artistas mais ouvidos a retornar: "});
        break;
    }

    if (comando)
    {
        ResultadoQuery *resultadoQuery = gestor_queries_executa(gestorProgramaInterativo->gestorQueries, comando, gestorProgramaInterativo->dados);
        gestor_programa_interativo_imprime_query(resultadoQuery, comando, janela);
        wrefresh(janela);
        wgetch(janela);
        comando_destroi(comando);
    }

    // Retornar ao menu principal após executar a query
    gestorProgramaInterativo->estado->janelaAtual = JANELA_MENU;
}



void gestor_programa_interativo_rodape(int alturaJanelaPrincipal, int largura, int starty, int startx)
{
    WINDOW *janelaRodape = newwin(3, largura, starty + alturaJanelaPrincipal, startx); // Rodapé sempre abaixo da janela principal
    wclear(janelaRodape);
    box(janelaRodape, 0, 0);

    mvwprintw(janelaRodape, 1, (largura - 75) / 2, " [B] Menu inicial | [S] Configurações | [H] Ajuda | [E] Estatísticas ");

    wrefresh(janelaRodape);
}

WINDOW *gestor_programa_inicializar_barra_superior(int altura, int largura, int starty, int startx, GestorDeProgramaInterativo *gestor)
{
    WINDOW *barra = newwin(altura, largura, starty - altura, startx);
    keypad(barra, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    box(barra, 0, 0);

    mvwprintw(barra, 1, 2, "Utilizador: %s", gestor->estado->nomeUtilizador);
    mvwprintw(barra, 1, largura - 8, "[Esc]"); 

    wrefresh(barra);
    return barra;
}

void capturar_input(char *mensagem, char **buffer, size_t *len, WINDOW *janela, EstadoProgramaInterativo *estado)
{
    mvwprintw(janela, estado->linhaAtual++, 5, "%s", mensagem);
    wrefresh(janela);
    *buffer = malloc(256);
    if (!(*buffer))
    {
        endwin();
        perror("Erro de alocação de memória");
        exit(EXIT_FAILURE);
    }
    echo();
    wgetnstr(janela, *buffer, 255); // Captura o input da janela
    noecho();

    // Remove o caractere de nova linha, se presente
    size_t input_len = strlen(*buffer);
    if (input_len > 0 && (*buffer)[input_len - 1] == '\n')
    {
        (*buffer)[input_len - 1] = '\0';
    }
}
void gestor_programa_interativo_nome_utilizador(GestorDeProgramaInterativo *gestor, WINDOW *janela)
{
    char *nomeUtilizador = NULL;
    size_t lengthNome = 0;

    // Captura o nome do utilizador e armazena no estado
    capturar_input("Introduza o seu nome de utilizador:", &nomeUtilizador, &lengthNome, janela, gestor->estado);

    // Atualiza o estado com o nome do utilizador
    if (gestor->estado->nomeUtilizador)
    {
        free(gestor->estado->nomeUtilizador);
    }
    gestor->estado->nomeUtilizador = strdup(nomeUtilizador);

    free(nomeUtilizador);
}

void gestor_programa_interativo_executa(GestorDeProgramaInterativo *gestorProgramaInterativo)
{

    gestor_programa_interativo_definir_esquemas_cores();

    EstadoProgramaInterativo *estado = gestorProgramaInterativo->estado;

    // Cria a janela principal
    int altura = 20, largura = 80;
    int starty = (LINES - altura) / 2, startx = (COLS - largura) / 2;

    WINDOW *janela = gestor_programa_inicializar_janela_principal(altura, largura, starty, startx, estado);

    gestor_programa_interativo_nome_utilizador(gestorProgramaInterativo, janela);
    gestor_programa_interativo_carregar_dados(gestorProgramaInterativo, janela);
    WINDOW *barra = gestor_programa_inicializar_barra_superior(3, largura, starty, startx, gestorProgramaInterativo);


    do
    {
        wclear(janela);
        WINDOW *barra = gestor_programa_inicializar_barra_superior(3, largura, starty, startx, gestorProgramaInterativo);
        gestor_programa_interativo_rodape(altura, largura, starty, startx);
        gestor_programa_interativo_aplicar_tema(janela, gestorProgramaInterativo->estado->tema);

        switch (estado->janelaAtual)
        {
        case JANELA_INICIAL:
            gestor_programa_interativo_janela_inicial(janela, gestorProgramaInterativo);
            break;

        case JANELA_CONFIGURACOES:
            gestor_programa_principal_janela_configuracoes(janela, gestorProgramaInterativo);
            break;

        case JANELA_AJUDA:
            gestor_programa_principal_janela_ajuda(janela);
            break;

        case JANELA_ESTATISTICAS:
            gestor_programa_principal_janela_estatisticas(janela, gestorProgramaInterativo);
            break;
        case JANELA_MENU:
            gestor_programa_interativo_janela_menu(janela, gestorProgramaInterativo);
            break;
        case JANELA_CONSOLA:
            gestor_programa_interativa_consola(gestorProgramaInterativo);
            break;
        case JANELA_SAIR:
            gestor_programa_interativo_fechar_programa(janela, barra);
        }

        wrefresh(janela);

        // Captura a tecla ou clique no final do loop
        int tecla = wgetch(janela);

        int continuar_y = starty + altura / 2 + 5;
        int continuar_x = startx + (largura - 56) / 2 + 9;
        int sair_x = continuar_x + 30;

        if (tecla == KEY_MOUSE)
        {
            MEVENT evento;
            if (getmouse(&evento) == OK)
            {      
                if (gestor_programa_interativo_verificar_clique(evento.x, evento.y, continuar_x, 9, continuar_y))
                {
                    estado->janelaAtual = JANELA_MENU;
                }
                else if (gestor_programa_interativo_verificar_clique(evento.x, evento.y, sair_x, 5, continuar_y))
                {
                    estado->janelaAtual = JANELA_CONSOLA;
                }
            }
            }
            else
                {
                    // Tratamento das teclas de navegação
                    switch (tecla)
                    {
                    case 'S' : 
                    case 's' :
                        estado->janelaAtual = JANELA_CONFIGURACOES;
                        break;

                    case 'H' :
                    case 'h' :
                        estado->janelaAtual = JANELA_AJUDA;
                        break;

                    case 'E' :
                    case 'e' :
                        estado->janelaAtual = JANELA_ESTATISTICAS;
                        break;

                    case 'B' :
                    case 'b' :
                        estado->janelaAtual = JANELA_INICIAL;
                        break;
                        
                    case ESC_KEY:
                        estado->janelaAtual = JANELA_SAIR;
                        break;
                    }
                }
        
    }while (estado->janelaAtual != JANELA_SAIR);

    gestor_programa_interativo_fechar_programa(janela, barra);
}