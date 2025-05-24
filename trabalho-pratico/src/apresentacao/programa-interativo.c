#include "gestor-programa-interativo.h"

int main() {
    //setlocale(LC_CTYPE, "en_US.UTF-8");
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    start_color();
    curs_set(0);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

    GestorDeProgramaInterativo *gestorProgramaInterativo = gestor_programa_interativo_novo();

    gestor_programa_interativo_executa(gestorProgramaInterativo);

    gestor_programa_interativo_destroi(gestorProgramaInterativo);

    return 0;
}
