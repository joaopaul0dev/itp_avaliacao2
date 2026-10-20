#include <ncurses.h>
#include <stdlib.h>

#define NUM_OPCOES 4

void reservarAssento()
{
    clear();
    mvprintw(2, 2, "Opcao: Reservar assento");
    mvprintw(4, 2, "Pressione qualquer tecla...");
    refresh();
    getch();
}

void visualizarAssento()
{
    clear();
    mvprintw(2, 2, "Opcao: Visualizar assentos");
    mvprintw(4, 2, "Pressione qualquer tecla...");
    refresh();
    getch();
}

void cancelarReserva()
{
    clear();
    mvprintw(2, 2, "Opcao: Cancelar reserva");
    mvprintw(4, 2, "Pressione qualquer tecla...");
    refresh();
    getch();
}

int main(void)
{
    const char *opcoes[4] = {
        "Reservar assento",
        "Visualizar assentos",
        "Cancelar reserva",
        "Sair"};

    int selecionada = 0;
    int tecla;
    int assentos[8][6];
    char sessaoTitulo[100];

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int linhas, colunas;
    getmaxyx(stdscr, linhas, colunas);

    curs_set(0);
    mvprintw(linhas / 2 - 4,
             (colunas - 24) / 2,
             "Informe o Titulo da sessão");
                              
    while (1)
    {
        clear();

        mvprintw(linhas / 2 - 4,
                 (colunas - 24) / 2,
                 "SISTEMA DE RESERVAS");

        for (int i = 0; i < 4; i++)
        {
            int y = linhas / 2 - 1 + i;
            int x = (colunas - 24) / 2;

            if (i == selecionada)
            {
                attron(A_REVERSE);
                mvprintw(y, x, " > %-21s", opcoes[i]);
                attroff(A_REVERSE);
            }
            else
            {
                mvprintw(y, x, "   %-21s", opcoes[i]);
            }
        }

        mvprintw(linhas - 2, 2,
                 "Use as setas para navegar e Enter para selecionar.");

        refresh();

        tecla = getch();

        switch (tecla)
        {
        case KEY_UP:
            selecionada--;

            if (selecionada < 0)
            {
                selecionada = NUM_OPCOES - 1;
            }
            break;

        case KEY_DOWN:
            selecionada++;

            if (selecionada >= NUM_OPCOES)
            {
                selecionada = 0;
            }
            break;

        case '\n':
        case KEY_ENTER:
            switch (selecionada)
            {
            case 0:
                reservarAssento();
                break;

            case 1:
                visualizarAssento();
                break;

            case 2:
                cancelarReserva();
                break;
            case 3:
                endwin();
                return 0;
            }
            break;
        }
    }

    endwin();
    return 0;
}
