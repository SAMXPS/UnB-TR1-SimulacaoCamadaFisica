#ifndef DRAW_UTILS_H
#define DRAW_UTILS_H

/**
 * Função que retorna a representação do número real com 2 casas decimais e 
 * sufixo de unidade Volts [V].
 */
std::string voltageToString(double voltage);

/**
 * Desenhar uma linha, conectando dois pontos P0=(x0,y0) e P1=(x1,y1) utilizando
 * o Algoritmo de Bresenham.
 */
void draw_line(int x0, int y0, int x1, int y1, char line_char);

/**
 * Rotina que escreve um título na tela.
 * Formato: ======== Título =========
 *
 * y:      posição vertical do título. 
 * title:  título a ser escrito na tela.
 */
void draw_title(int y, std::string title);

/**
 * Rotina que desenha um sinal binário na tela.
 * x_slide representa a movimentação no eixo temporal.
 * y_start representa a partir de qual pixel será desenhado o sinal.
 * height representa a altura, em pixels, do desenho.
 * voltages é um vetor contendo os bits. 
 */
void draw_binary(int x_slide, int y_start, int height, int len, int* voltages);

/**
 * Rotina que desenha um sinal de tensão na tela.
 * x_slide representa a movimentação no eixo temporal.
 * y_start representa a partir de qual pixel será desenhado o sinal.
 * height representa a altura, em pixels, do desenho.
 * voltages é um vetor contendo as tensões do sinal a ser desenhado.
 * max_voltage representa a tensão máxima a ser desenhada.
 * min_voltage representa a tensão mínima a ser desenhada. 
 */
void draw_signal(int x_slide, int y_start, int height, int len, double* voltages, double max_voltage, double min_voltage);

/**
  * Rotina que escreve mensagem no centro da tela.
  * WIN representa a janela do nCurses.
  * starty posição y inicial.
  * startx posição x inicial.
  * width largura da tela.
  * string mensagem a ser impressa.
  * color esquema de cores.
  */
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);

#endif