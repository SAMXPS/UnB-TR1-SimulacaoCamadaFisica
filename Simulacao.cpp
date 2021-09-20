#include <ncurses.h>
#include <math.h>
#include <unistd.h>
#include <menu.h>
#include <form.h>
#include <stdlib.h>
#include <string.h>
#include "CamadaFisica.h"
#include "DrawUtils.h"

#define  OPCAO_SAIR 3

// Opcoes do menu principal.
char *choices[] = {
    "CODIFICACAO BINARIA",
    "CODIFICACAO MANCHESTER",
    "CODIFICACAO BIPOLAR",
    "Sair",
};

// Descricao das opcoes.
char *descriptions[] = {
    "Transmitir codificacao de bits em NRZ.",
    "Transmitir clock junto com os dados.",
    "Transmitir bits 1 com dois niveis +V e -V.",
    "Fechar o programa.",
};

// Ajuda do menu principal.
char *menu_inicial_help[] = {
    "Utilize as setas para cima/para baixo para alterar opcao.",
    "Pressione ENTER para selecionar opcao desejada.",
    "Pressione F1 para sair do programa."
};

char *digite_uma_mensagem = "Por favor, digite uma mensagem para ser transmitida:";

// Ajuda da simulacao.
char *simulacao_help[] = {
    "Pressione ESPACO para pausar/resumir a simulacao.",
    "Pressione BACKSPACE para reiniciar a simulacao.",
    "Pressione F1 para sair do programa."
};

int loop(contexto_simulacao* contexto, int x) {
    clear();                                                    // Limpando a tela.
    const int binary_height = 4;                                // Altura do sinal de bits.
    const int voltage_height = 11;                              // Altura do sinal de voltagens.
    int bit_len = contexto->quadro_transmitido.size();          // Quantiade de bits transmitidos.
    int voltage_len = contexto->tensoes.size();                 // Quantidade de voltagens discretas a serem transmitidas.
    double voltage_to_bit_ratio = (voltage_len*1.0D)/bit_len;   // Razao voltagens/bit.
    int bit_width = voltage_to_bit_ratio*5;                     // Largura em pixels de cada bit.
    int len = bit_len * bit_width;                              // Largura em pixels da transmissão.
    int bits_transmitidos[len];                                 // Vetor auxiliar para armazenar bits transmitidos.
    double voltages[len];                                       // Vetor auxiliar para armazenar voltagens trasmitidas.
    int bits_recebidos[len];                                    // Vetor auxiliar para armazenar bits recebidos.
    double min_voltage = 0;                                     // Variável auxiliar para armazenar menor voltagem da linha.
    double max_voltage = 0;                                     // Variável auxiliar para armazenar maior voltagem da linha.

    // Loop para expansão dos bits em bit_width caracteres.
    for (int i = 0; i < len; i++) {
        bits_transmitidos[i] = contexto->quadro_transmitido[i/bit_width];
        voltages[i] = contexto->tensoes[(i*voltage_to_bit_ratio)/bit_width];
        bits_recebidos[i] = contexto->quadro_recebido[i/bit_width];
        if (voltages[i] > max_voltage) max_voltage = voltages[i];
        if (voltages[i] < min_voltage) min_voltage = voltages[i];
    }

    int y = 0;
    mvprintw(++y, 0, "Tipo de Codificação: ");                  // Imprime na tela.
    mvprintw(y, 23, choices[contexto->tipo_de_codificacao]);    // Imprime na tela o tipo de codificação.
    mvprintw(++y, 0, "Mensagem transmitida: ");                 // Imprime na tela.
    mvprintw(y, 22, contexto->mensagem_transmitida.c_str());    // Imprime na tela a mensagem a ser transmitida.

    draw_title(y+=2, "Transmição de bits");                     // Desenha o título na tela.
    draw_binary(-1, y+=2, binary_height, x, bits_transmitidos); // Desenha o sinal de bits enviados na tela.
    draw_title(y+=binary_height+2, "Camada física");            // Desenha o título na tela.
    draw_signal(-1, y+=2, voltage_height, x,
        voltages, max_voltage, min_voltage);                    // Desenha o sinal de voltagens na tela.

    draw_title(y+=voltage_height+2, "Recepção de bits");        // Imprime na tela.
    draw_binary(-1, y+=2, binary_height, x, bits_recebidos);    // Desenha o sinal de bits recebidos na tela.

    mvprintw(y+=binary_height+2, 0, "Mensagem Recebida: ");     // Imprime na tela.
    mvprintw(y, 19, 
            contexto->mensagem_recebida.substr(
                0, (x+1)/(bit_width*8)
            ).c_str()                                           // Pega o pedaço que já foi transmitido e imprime na tela.
        );
    
    for (int j = 0; j < 3; j++) {
	    mvprintw(LINES - 4 + j, 2, simulacao_help[j]);          // Imprime instruções do menu na parte inferior da tela.
    }

    refresh();                                                  // Renderiza a janela.
    if (++x>=len) {
        x=0;
        usleep(700000);                                         // Pausa no final por alguns momentos.
    }
    usleep(70000);                                              // Tempo entre cada frame.
    return x;
}

int menu_selecionar_codifcacao() {
    WINDOW *my_menu_win;                                        // Janela nCurses.
	MENU *my_menu;                                              // Menu nCurses.
	ITEM **my_items;                                            // Opções do menu.
	ITEM *cur_item;                                             // Opção selecionada.
	int c;			                                            // Usado para ler input do teclado.
	int n_choices, i;                                           // Variáveis auxiliares.
	
	initscr();                                                  // Iniciando janela nCurses.
	cbreak();                                                   // Desabilitando line-buffer.
	noecho();                                                   // Desabilitando echo.
	keypad(stdscr, TRUE);                                       // Habilitando leitura de teclas-chave.
	init_pair(1, COLOR_RED, COLOR_BLACK);                       // Cores utilizadas no menu.
	
	n_choices = 4;                                              // Quantidade de opções do menu.
	my_items = (ITEM **) calloc(n_choices + 1, sizeof(ITEM *)); // Alocando memória para as opções do menu.

	for(i = 0; i < n_choices; ++i) {
	    my_items[i] = new_item(choices[i], descriptions[i]);    // Criando itens do menu nCurses.
    }

	my_items[n_choices] = (ITEM *)NULL;                         // Sinal de parada, assim como null terminated string.
	my_menu = new_menu((ITEM **)my_items);                      // Criando menu nCurses.

    int menu_width = 72;                                        // Largura, em caracteres, do menu.
    int menu_lines = n_choices;                                 // Altura, em linhas, do menu.
    my_menu_win = newwin(menu_lines+4, menu_width, 4, 4);       // Cria uma nova janela
    keypad(my_menu_win, TRUE);                                  // Habilitando input na nova janela.
    set_menu_win(my_menu, my_menu_win);                         // Configurando menu na nova janela.
    set_menu_sub(my_menu, 
        derwin(my_menu_win, 4, menu_width-2, 3, 1)              // Sub-janela nCurses.
    );
    set_menu_mark(my_menu, " * ");                              // Caractere seletor de opções.
    box(my_menu_win, 0, 0);                                     // Borda ao redor do menu.

	print_in_middle(
        my_menu_win, 1, 0, menu_width, 
        "Simulacao Camada Fisica", COLOR_PAIR(1)                // Escrevendo título do menu.
    );

	mvwaddch(my_menu_win, 2, 0, ACS_LTEE);                      // T lateral esquerdo. Conecta linha horizontal e vertical.
	mvwhline(my_menu_win, 2, 1, ACS_HLINE, menu_width-2);       // Linha entre título e opções.
	mvwaddch(my_menu_win, 2, menu_width-1, ACS_RTEE);           // T lateral direito. Conecta linha horizontal e vertical.

    for (int j = 0; j < 3; j++) {
	    mvprintw(LINES - 4 + j, 2, menu_inicial_help[j]);       // Imprime instruções do menu na parte inferior da tela.
    }

	refresh();                                                  // Atualiza a janela.
	post_menu(my_menu);                                         // Renderiza o menu na janela.
	wrefresh(my_menu_win);                                      // Renderiza a janela.
	refresh();                                                  // Atualiza a janela.

	while((c = getch()) != KEY_F(1)) {   
        int exit = 0;
        switch(c) {
            case KEY_DOWN:                                      // Tecla para baixo.
		        menu_driver(my_menu, REQ_DOWN_ITEM);            // Move para próxima opção.
				break;
			case KEY_UP:                                        // Tecla para cima.
				menu_driver(my_menu, REQ_UP_ITEM);              // Move para opção anterior.
				break;
            case 10:                                            // Tecla nova linha (ENTER).
                exit = 1;                                       // Escolhe a opção e termina o loop while.
                break; 
		}
        refresh();                                              // Atualiza a janela.
	    post_menu(my_menu);                                     // Renderiza o menu na janela.
        wrefresh(my_menu_win);                                  // Renderiza a janela.
        refresh();                                              // Atualiza a janela.
        if (exit) break;
	}	

    ITEM *cur;                                                  
    cur = current_item(my_menu);                                // Recupera item selecionado.
    short index = cur->index;                                   // Recupera indice do item.

    unpost_menu(my_menu);                                       // Liberação de memória.
    free_menu(my_menu);                                         // Liberação de memória.
    for(i = 0; i < n_choices; ++i)
        free_item(my_items[i]);                                 // Liberação de memória.
	endwin();                                                   // Terminando janela.

    return index;                                               // Retorna o índice da opção selecionada.
}

std::string menu_digitar_mensagem() {
    int y = 0;
    char* str = (char*) calloc(80, sizeof(char));                   // Alocando memória.
    initscr();                                                      // Iniciando nova janela.
    clear();                                                        // Limpando janela.
    echo();                                                         // Habilitando input do usuário.
    do {
        mvprintw(y++,0,digite_uma_mensagem);                        // Escrevendo mensagem na tela.
        move(y++,0);                                                // Movendo cursor para linha seguinte.
        getstr(str);                                                // Lendo mensagem digitada.
    } while (!strlen(str));                                         // Repete até que a mensagem seja válida.
    endwin();                                                       // Finalizando janela.
    std::string string = str;                                       // Conversao para c++.
    free(str);                                                      // Liberando memória.
    return string;                                                  // Retornando mensagem digitada.
}

int main(int argc, char *argv[]) {
    int opcao_selecionada, exit = 0, pause = 0, x = 0;
    contexto_simulacao contexto;
    opcao_selecionada = menu_selecionar_codifcacao();               // Chama menu inicial.
    if (opcao_selecionada != OPCAO_SAIR) {
        contexto.tipo_de_codificacao = opcao_selecionada;           // Configura a codificacao conforme selecao do usuário.
        contexto.mensagem_transmitida = menu_digitar_mensagem();
        initscr();                                                  // Iniciando tela do nCurses.
        noecho();                                                   // Desabilitando echo de caracteres.
        curs_set(FALSE);                                            // Desabilitando cursor.
        AplicacaoTransmissora(&contexto);                           // Faz a chamada do backend.
        while(1) {
            x = loop(&contexto, x);                                 // Desenha interface gráfica.
            nodelay(stdscr, !pause);                                // Delay apenas quando a simulação estiver pausada.
            switch(getch()) {
                case KEY_BACKSPACE:                                 // Tecla para baixo.
                    x = 0;
                    break;
                case ' ':                                           // Barra de espaço.
                    pause = !pause;                                 // Pausa / resume a simulação.
                    break;
                case KEY_F(1):                                      // Tecla nova linha (ENTER).
                    exit = 1;                                       // Escolhe a opção e termina o loop while.
                    break; 
            }
            if (exit) 
                break;
        }
        endwin();                                                   // Finaliza a janela.
    }
    return 0;
}