// gcc -std=c11 -Wall -Wextra -pedantic main.c -o reserva -lncurses
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_FILAS 6
#define ASSENTOS_POR_FILA 8
#define TAM_TITULO 100

void lerTexto(const char *mensagem, char *texto, int tamanho) {
    mvprintw(LINES - 3, 2, "%s", mensagem);
    clrtoeol();

    echo();
    curs_set(1);
    getnstr(texto, tamanho - 1);
    noecho();
    curs_set(0);
}

int lerInteiro(const char *mensagem, int minimo, int maximo) {
    char entrada[100];
    char *fim;
    long valor;

    while (1) {
        lerTexto(mensagem, entrada, sizeof(entrada));

        valor = strtol(entrada, &fim, 10);

        while (isspace((unsigned char)*fim)) {
            fim++;
        }

        if (fim == entrada || *fim != '\0') {
            mvprintw(LINES - 2, 2, "Digite um numero inteiro.");
            getch();
            continue;
        }

        if (valor < minimo || valor > maximo) {
            mvprintw(LINES - 2, 2,
                     "Informe um valor entre %d e %d.",
                     minimo, maximo);
            getch();
            continue;
        }

        return (int)valor;
    }
}

void lerTitulo(char titulo[TAM_TITULO]) {
    while (1) {
        lerTexto("Titulo da sessao: ", titulo, TAM_TITULO);

        int valido = 0;

        for (int i = 0; titulo[i] != '\0'; i++) {
            if (!isspace((unsigned char)titulo[i])) {
                valido = 1;
                break;
            }
        }

        if (valido) {
            return;
        }

        mvprintw(LINES - 2, 2, "O titulo nao pode ficar vazio.");
        getch();
    }
}

void inicializarAssentos(
    int assentos[MAX_FILAS][ASSENTOS_POR_FILA]
) {
    for (int i = 0; i < MAX_FILAS; i++) {
        for (int j = 0; j < ASSENTOS_POR_FILA; j++) {
            assentos[i][j] = 0;
        }
    }
}

void exibirMapa(
    int assentos[MAX_FILAS][ASSENTOS_POR_FILA],
    int quantidadeFilas,
    const char *titulo
) {
    clear();

    mvprintw(1, 2, "MAPA DE ASSENTOS");
    mvprintw(2, 2, "Sessao: %s", titulo);
    mvprintw(4, 2, "TELA DO CINEMA");

    mvhline(5, 2, ACS_HLINE, 43);

    mvprintw(7, 2, "       ");

    for (int j = 0; j < ASSENTOS_POR_FILA; j++) {
        mvprintw(7, 10 + j * 4, "%d", j + 1);
    }

    for (int i = 0; i < quantidadeFilas; i++) {
        mvprintw(9 + i * 2, 2, "Fila %d", i + 1);

        for (int j = 0; j < ASSENTOS_POR_FILA; j++) {
            int linha = 9 + i * 2;
            int coluna = 10 + j * 4;

            if (assentos[i][j] == 0) {
                if (has_colors()) {
                    attron(COLOR_PAIR(1));
                }

                mvprintw(linha, coluna, "[L]");

                if (has_colors()) {
                    attroff(COLOR_PAIR(1));
                }
            } else {
                if (has_colors()) {
                    attron(COLOR_PAIR(2));
                }

                mvprintw(linha, coluna, "[R]");

                if (has_colors()) {
                    attroff(COLOR_PAIR(2));
                }
            }
        }
    }

    mvprintw(23, 2, "L = Livre | R = Reservado");
    mvprintw(25, 2, "Pressione qualquer tecla para voltar.");

    refresh();
    getch();
}

void reservarAssento(
    int assentos[MAX_FILAS][ASSENTOS_POR_FILA],
    int quantidadeFilas
) {
    clear();
    mvprintw(1, 2, "RESERVAR ASSENTO");

    int fila = lerInteiro(
        "Informe a fila: ", 1, quantidadeFilas
    );

    int numeroAssento = lerInteiro(
        "Informe o assento: ", 1, ASSENTOS_POR_FILA
    );

    int linha = fila - 1;
    int coluna = numeroAssento - 1;

    clear();

    if (assentos[linha][coluna] == 1) {
        mvprintw(3, 2, "Esse assento ja esta reservado.");
    } else {
        assentos[linha][coluna] = 1;
        mvprintw(3, 2, "Reserva realizada com sucesso!");
    }

    mvprintw(5, 2, "Pressione qualquer tecla para continuar.");
    refresh();
    getch();
}

void cancelarReserva(
    int assentos[MAX_FILAS][ASSENTOS_POR_FILA],
    int quantidadeFilas
) {
    clear();
    mvprintw(1, 2, "CANCELAR RESERVA");

    int fila = lerInteiro(
        "Informe a fila: ", 1, quantidadeFilas
    );

    int numeroAssento = lerInteiro(
        "Informe o assento: ", 1, ASSENTOS_POR_FILA
    );

    int linha = fila - 1;
    int coluna = numeroAssento - 1;

    clear();

    if (assentos[linha][coluna] == 0) {
        mvprintw(3, 2, "Esse assento ja esta livre.");
    } else {
        assentos[linha][coluna] = 0;
        mvprintw(3, 2, "Reserva cancelada com sucesso!");
    }

    mvprintw(5, 2, "Pressione qualquer tecla para continuar.");
    refresh();
    getch();
}

void calcularAssentosLivres(
    int assentos[MAX_FILAS][ASSENTOS_POR_FILA],
    int quantidadeFilas,
    int *livresPorFila
) {
    for (int i = 0; i < quantidadeFilas; i++) {
        livresPorFila[i] = 0;

        for (int j = 0; j < ASSENTOS_POR_FILA; j++) {
            if (assentos[i][j] == 0) {
                livresPorFila[i]++;
            }
        }
    }
}

void exibirResumo(
    int assentos[MAX_FILAS][ASSENTOS_POR_FILA],
    int quantidadeFilas,
    int *livresPorFila,
    const char *titulo
) {
    calcularAssentosLivres(
        assentos, quantidadeFilas, livresPorFila
    );

    int totalAssentos = quantidadeFilas * ASSENTOS_POR_FILA;
    int totalLivres = 0;

    clear();

    mvprintw(1, 2, "RESUMO DA SESSAO");
    mvprintw(2, 2, "Titulo: %s", titulo);
    mvhline(3, 2, ACS_HLINE, 45);

    for (int i = 0; i < quantidadeFilas; i++) {
        mvprintw(5 + i, 2, "Fila %d: %d assentos livres",
                 i + 1, livresPorFila[i]);

        totalLivres += livresPorFila[i];
    }

    int totalReservados = totalAssentos - totalLivres;

    double ocupacao =
        (double)totalReservados / totalAssentos * 100.0;

    int inicio = 7 + quantidadeFilas;

    mvprintw(inicio, 2, "Total de assentos: %d", totalAssentos);
    mvprintw(inicio + 1, 2, "Assentos livres: %d", totalLivres);
    mvprintw(inicio + 2, 2, "Assentos reservados: %d",
             totalReservados);
    mvprintw(inicio + 3, 2, "Ocupacao: %.2f%%", ocupacao);

    mvprintw(inicio + 5, 2,
             "Pressione qualquer tecla para voltar.");

    refresh();
    getch();
}

int exibirMenu(const char *titulo) {
    const char *opcoes[] = {
        "Exibir mapa de assentos",
        "Reservar assento",
        "Cancelar reserva",
        "Exibir resumo",
        "Encerrar programa"
    };

    int selecionada = 0;
    int totalOpcoes = 5;
    int tecla;

    while (1) {
        clear();

        mvprintw(1, 2, "==================================");
        mvprintw(2, 2, "       RESERVA DE ASSENTOS");
        mvprintw(3, 2, "==================================");
        mvprintw(5, 2, "Sessao: %s", titulo);
        mvprintw(6, 2, "Use as setas para navegar e Enter para selecionar.");

        for (int i = 0; i < totalOpcoes; i++) {
            if (i == selecionada) {
                attron(A_REVERSE);
            }

            mvprintw(9 + i * 2, 4, "%s", opcoes[i]);

            if (i == selecionada) {
                attroff(A_REVERSE);
            }
        }

        refresh();
        tecla = getch();

        switch (tecla) {
            case KEY_UP:
                selecionada--;

                if (selecionada < 0) {
                    selecionada = totalOpcoes - 1;
                }
                break;

            case KEY_DOWN:
                selecionada++;

                if (selecionada >= totalOpcoes) {
                    selecionada = 0;
                }
                break;

            case '\n':
            case KEY_ENTER:
                return selecionada + 1;
        }
    }
}

int main(void) {
    int assentos[MAX_FILAS][ASSENTOS_POR_FILA];
    char titulo[TAM_TITULO];
    int quantidadeFilas;
    int opcao;
    
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    if (has_colors()) {
        start_color();
        use_default_colors();

        init_pair(1, COLOR_GREEN, -1);
        init_pair(2, COLOR_RED, -1);
    }

    clear();

    lerTitulo(titulo);

    quantidadeFilas = lerInteiro(
        "Quantidade de filas (1 a 6): ",
        1, MAX_FILAS
    );

    inicializarAssentos(assentos);

    int *livresPorFila = malloc(
        quantidadeFilas * sizeof(int)
    );

    if (livresPorFila == NULL) {
        endwin();
        fprintf(stderr, "Erro ao alocar memoria.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < quantidadeFilas; i++) {
        livresPorFila[i] = ASSENTOS_POR_FILA;
    }

    do {
        opcao = exibirMenu(titulo);

        switch (opcao) {
            case 1:
                exibirMapa(assentos, quantidadeFilas, titulo);
                break;

            case 2:
                reservarAssento(assentos, quantidadeFilas);
                break;

            case 3:
                cancelarReserva(assentos, quantidadeFilas);
                break;

            case 4:
                exibirResumo(
                    assentos,
                    quantidadeFilas,
                    livresPorFila,
                    titulo
                );
                break;

            case 5:
                clear();
                mvprintw(2, 2, "Encerrando o programa...");
                refresh();
                break;
        }

    } while (opcao != 5);

    free(livresPorFila);
    
    endwin();

    return EXIT_SUCCESS;
}
