#include <ncurses.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <limits>
#include <math.h>
#include <string.h>

std::string voltageToString(double voltage) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << voltage << "V";
    return ss.str();
}

void draw_line(int x0, int y0, int x1, int y1, char line_char) {
    int dx = x1-x0;                                 // Diferença horizontal.
    int dy = y1-y0;                                 // Diferença vertical.

    if (dx < 0) {                                   // Queremos sempre x1 > x0, então
        int x = x1;                                 // trocamos a posição de P0 e P1
        int y = y1;                                 // quando x0 > x1.
        x1 = x0;
        y1 = y0;
        x0 = x;
        x1 = y;
        dx = x1-x0;
    }

    int incy = 1;                                   // incy representará o incremento em y.
    if (dy < 0) {
        dy = -dy;
        incy = -1;
    }

    if (dy > dx) {                                  // Caso onde dy > dx.
        int D = 2*dx-dy;                            // Variável do algoritmo de Bresenham.
        mvaddch(y0,x0, line_char);                  // Desenha um ponto em x0,y0
        int x = x0;
        for (int y = y0+incy; y != y1; y+=incy) {
            if (D > 0) {
                x = x + 1;                          // Incrementa-se x conforme o valor de D.
                D = D + (2*dx-2*dy);                
            } else {
                D = D + (2*dx);
            }
            mvaddch(y,x, line_char);                // Desenha um ponto em x, y
            if (y == y1) break; 
        }
    } else {                                        // Caso onde dx >= dy.
        int D = 2*dy-dx;                            // Variável do algoritmo de Bresenham.
        mvaddch(y0,x0, line_char);
        int y = y0;
        for (int x = x0+1; x <= x1; x++) {
            if (D > 0) {
                y = y + incy;                       // Incrementa-se y conforme o valor de D.
                D = D + (2*dy-2*dx);
            } else {
                D = D + (2*dy);
            }
            mvaddch(y,x, line_char);                // Desenha um ponto em x, y
        }
    }
}

void draw_title(int y, std::string title) {
    int max_y = 0, max_x = 0;
    getmaxyx(stdscr, max_y, max_x);                         // Recebendo tamanho da tela.

    for (int x = 0; x < max_x; x++) {
        mvaddch(y,x, '=');                                  // Preenchendo espaçadores "=".
    }

    int strlen = title.length();                            // Calculando tamanho (em caracteres) do título.

    if (strlen > 0) {                                       // Só escrevemos texto se ele não for nulo.
        int x_start = std::max(0, (max_x/2) - (strlen/2));  // Calculando posição do centro da tela.
        mvprintw(y, x_start, title.c_str());                // Escrevendo o título no centro da tela.
        mvprintw(y, x_start - 1, " ");                      // Espaçamento antecessor ao título.
        mvprintw(y, x_start + strlen , " ");                // Espaçamento sucessor ao título.
    }
}

void draw_binary(int x_slide, int y_start, int height, int len, int* voltages) {
    // Mostrando eixo vertical com valores de tensão.
    mvprintw(y_start, 0, "1");
    mvprintw(y_start+height, 0, "0");

    int max_y = 0, max_x = 0;
    getmaxyx(stdscr, max_y, max_x); // Calculando tamanho da tela.

    int x_start = 10;               // Espaçamento horizontal.
    max_x -= x_start;               // Variável auxiliar.

    if (x_slide == -1) {
        x_slide = std::max(0, len-max_x);
    }

    for (int x = x_slide+1; x < max_x+x_slide && x < len; x++) {
        draw_line( 
            x_start+x-1-x_slide,                // x0.
            y_start+(!voltages[x-1])*height,    // y0.
            x_start+x-x_slide,                  // x1.
            y_start+(!voltages[x])*height,      // y1.
            '*'                                 // Desenhar asteríscos no gráfico.
        );
    }
}

void draw_signal(int x_slide, int y_start, int height, int len, double* voltages, double max_voltage, double min_voltage) {
    // Mostrando eixo vertical com valores de tensão.
    for (int y = 0; y < height; y++) {
        double voltage = (min_voltage - max_voltage)*(y*1.0/(height-1)) + max_voltage;
        mvprintw(y_start+y, 0, voltageToString(voltage).c_str());
    }

    int max_y = 0, max_x = 0;
    getmaxyx(stdscr, max_y, max_x); // Calculando tamanho da tela.

    int x_start = 10;               // Espaçamento horizontal.
    max_x -= x_start;               // Variável auxiliar.

    if (x_slide == -1) {
        x_slide = std::max(0, len-max_x);
    }

    int ys[len];                    // Vetor de inteiros montados a partir dos reais voltages.
    for (int x = 0; x < len; x++) { 
        // Esse trecho de código faz a passagem dos reais para inteiros,
        // de forma utilizar os níveis de tensão pré-determinados no eixo vertical.
        ys[x] = round(((max_voltage-voltages[x])/(max_voltage - min_voltage))*(height-1));
    }
    for (int x = x_slide+1; x < max_x+x_slide && x < len; x++) {
        draw_line( 
            x_start+x-1-x_slide,    // x0.
            y_start+ys[x-1],        // y0.
            x_start+x-x_slide,      // x1.
            y_start+ys[x],          // y1.
            '*'                     // Desenhar asteríscos no gráfico.
        );
    }
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color) {
	int length, x, y;                       // Variáveis auxiliares
	float temp;

	if(win == NULL)
		win = stdscr;                       // Janela padrão nCurses.
	getyx(win, y, x);                       // Tanho da tela.
	if(startx != 0)
		x = startx;                         // Inicialização da posição x.
	if(starty != 0)
		y = starty;                         // Inicialização da posição y.
	if(width == 0)
		width = 80;                         // Largura padrão.

	length = strlen(string);                // Tamanho da string.
	temp = (width - length)/ 2;             // Achando o centro.
	x = startx + (int)temp;                 // Somando startx.
	wattron(win, color);                    // Ligando coloração.
	mvwprintw(win, y, x, "%s", string);     // Escrevendo na tela a mensagem.
	wattroff(win, color);                   // Desligando coloração.
	refresh();                              // Atualizando tela.
}