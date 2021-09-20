#include <ncurses.h>
#include <math.h>
#include <unistd.h>
#include "CamadaFisica.h"
#include "DrawUtils.h"

void loop(contexto_simulacao* contexto) {
    static int x = 0;
    clear(); // Clear the screen of all

    const int binary_height = 4;
    const int voltage_height = 11;
    int bit_len = contexto->quadro_transmitido.size();
    int voltage_len = contexto->tensoes.size();
    double voltage_to_bit_ratio = (voltage_len*1.0D)/bit_len;
    int bit_width = voltage_to_bit_ratio*5;

    int len = bit_len * bit_width;

    int bits_transmitidos[len];
    double voltages[len];
    int bits_recebidos[len];

    double min_voltage = 0;
    double max_voltage = 0;

    for (int i = 0; i < len; i++) {
        bits_transmitidos[i] = contexto->quadro_transmitido[i/bit_width];
        voltages[i] = contexto->tensoes[(i*voltage_to_bit_ratio)/bit_width];
        bits_recebidos[i] = contexto->quadro_recebido[i/bit_width];
        if (voltages[i] > max_voltage) max_voltage = voltages[i];
        if (voltages[i] < min_voltage) min_voltage = voltages[i];
    }

    int y = 0;
    mvprintw(++y, 0, "Tipo de Codificação: binária");
    mvprintw(++y, 0, "Mensagem transmitida: ");
    mvprintw(y, 22, contexto->mensagem_transmitida.c_str());

    draw_title(y+=2, "Transmição de bits");
    draw_binary(-1, y+=2, binary_height, x, bits_transmitidos);
    draw_title(y+=binary_height+2, "Camada física");
    draw_signal(-1, y+=2, voltage_height, x, voltages, max_voltage, min_voltage);

    draw_title(y+=voltage_height+2, "Recepção de bits");
    draw_binary(-1, y+=2, binary_height, x, bits_recebidos);

    mvprintw(y+=binary_height+2, 0, "Mensagem Recebida:");
    mvprintw(y, 18, contexto->mensagem_recebida.substr(0, (x+1)/(bit_width*8)).c_str());

    refresh();
    //getchar();
    x++;
    if (x>=len) {
        x=0;
        usleep(700000);
    }
    usleep(70000);
}

int main(int argc, char *argv[]) {

    initscr();                  // Iniciando tela do nCurses.
    noecho();                   // Desabilitando echo de caracteres.
    curs_set(FALSE);            // Desabilitando cursor.

    contexto_simulacao contexto;
    // TODO: interação com usuário
    contexto.mensagem_transmitida = "Teste";
    contexto.tipo_de_codificacao = CODIFICACAO_BIPOLAR;
    AplicacaoTransmissora(&contexto);

    while(1) {
        loop(&contexto);        // Desenha interface gráfica.
    }

    endwin();                   // Finaliza o programa.
}