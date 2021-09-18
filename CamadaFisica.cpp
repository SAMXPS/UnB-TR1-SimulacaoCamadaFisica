#include "CamadaFisica.h"

#define CODIFICACAO_BINARIA 0
#define CODIFICACAO_MANCHESTER 1
#define CODIFICACAO_BIPOLAR 2

int tipoDeCodificacao = CODIFICACAO_BINARIA; // alterar de acordo com o teste

void AplicacaoTransmissora (void) {
    string mensagem;
    cout << "Digite uma mensagem" << endl;
    getline(cin, mensagem);

    //chama a proxima camada
    CamadaDeAplicacaoTransmissora(mensagem); //exmplo realistico: SEND do SOCKET
}// fim do metodo AplicacaoTransmissora

void CamadaDeAplicacaoTransmissora(string mensagem) {
    vector<int> quadro; // trabalhar com bits

    // converte a mensagem de um vetor de chars para
    // um vetor de bits
    for(int i = 0; i < mensagem.size(); i++){
        for(int j = 7; j >= 0; j--){
            int bitAtual = ((mensagem[i] >> j) & 1);
            quadro.push_back(bitAtual);
        }
    } //fim do for

    //mostraMensagemEmBits(quadro);

    //chama a proxima camada
    CamadaFisicaTransmissora(quadro);
}// fim do metodo de CamadaDeAplicacaoTransmissora

void CamadaFisicaTransmissora(vector<int> quadro) {
    vector<int> fluxoBrutoDeBits; // Bits e não bytes!

    switch (tipoDeCodificacao) {
        case CODIFICACAO_BINARIA: // codificacao binaria
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
            break;
        case CODIFICACAO_MANCHESTER: // codificacao manchester
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
            break;
        case CODIFICACAO_BIPOLAR: // codificacao bipolar
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBipolar(quadro);
            break;
        default:
            break;
    }//fim do switch case

    MeioDeComunicacao(fluxoBrutoDeBits);
}// fim do metodo de CamadaFisicaTransmissora

vector<int> CamadaFisicaTransmissoraCodificacaoBinaria (vector<int> quadro) {

    // codificacao binaria escolhida foi a Bipolar NTZ(L)
    // (Non return to zero - level)
    // algoritmo seguindo o padrao  RS-232

    vector<int> fluxoBrutoDeBits;

    for(int i = 0; i < quadro.size(); i++){
        if (quadro[i] == 1) {
            // 1 eh representado por uma voltagem positiva - nonosso caso 5 v
            fluxoBrutoDeBits.push_back(5);
        }
        if (quadro[i] == 0) {
            // 0 eh representado por uma voltagem negativa - nonosso caso -5 v
            fluxoBrutoDeBits.push_back(-5);
        }
    }

    return fluxoBrutoDeBits;

}//fim do metodo CamadaFisicaTransmissoraCodificacaoBinaria

vector<int> CamadaFisicaTransmissoraCodificacaoManchester (vector<int> quadro) {

    vector<int> fluxoBrutoDeBits;

    for(int i = 0; i < quadro.size(); i++){
        // implementa um "xor" com o clock - 010101...
        // seguindo a convencao IEEE 802.3
        fluxoBrutoDeBits.push_back((quadro[i] ^ 0));
        fluxoBrutoDeBits.push_back((quadro[i] ^ 1));
    }

    return fluxoBrutoDeBits;

}//fim do metodo CamadaFisicaTransmissoraManchester

vector<int> CamadaFisicaTransmissoraCodificacaoBipolar (vector<int> quadro) {

    //implementacao do algoritmo
    return quadro;

}//fim do metodo CamadaFisicaTransmissoraCodificacaoBipolar

/** Este metodo simula a transmissao da informacao no meio de
 * comunicacao, passando de um ponto A (transmissor) para um
 * ponto B (receptor)
 * **/
void MeioDeComunicacao (vector<int> fluxoBrutoDeBits) {
    vector<int> fluxoBrutoDeBitsPontoA, fluxoBrutoDeBitsPontoB;

    fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

    int i = 0;
    while (fluxoBrutoDeBitsPontoB.size() != fluxoBrutoDeBitsPontoA.size()) {
        fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA[i]); // bits sendo transferidos
        i++;
    }//fim do while

    //chama a proxima camada
    CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}//fim do metodo MeioDeTransmissão

void CamadaFisicaReceptora (vector<int> quadro) {
    vector<int> fluxoBrutoDeBits; // Bits e não bytes!

    switch (tipoDeCodificacao) {
        case CODIFICACAO_BINARIA: // codificacao binaria
            fluxoBrutoDeBits = CamadaFisicaTransmissoraDecodificacaoBinaria(quadro);
            break;
        case CODIFICACAO_MANCHESTER: // codificacao manchester
            fluxoBrutoDeBits = CamadaFisicaTransmissoraDecodificacaoManchester(quadro);
            break;
        case CODIFICACAO_BIPOLAR: // codificacao bipolar
            fluxoBrutoDeBits = CamadaFisicaTransmissoraDecodificacaoBipolar(quadro);
            break;
        default:
            break;
    }//fim do switch case

    CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
}

vector<int> CamadaFisicaTransmissoraDecodificacaoBinaria (vector<int> quadro) {

    vector<int> fluxoBrutoDeBits;

    for(int i = 0; i < quadro.size(); i++){
        if (quadro[i] >= 5 && quadro[i] <= 12) {
            // se o sinal esta entre 12 e 5 V o resultado 1 -- RS-232
            fluxoBrutoDeBits.push_back(1);
        }
        if (quadro[i] <= -5 && quadro[i] >= -12) {
            // se o sinal esta entre -12 e -5 V o resultado 0 -- RS-232
            fluxoBrutoDeBits.push_back(0);
        }
    }

    return fluxoBrutoDeBits;

}//fim do metodo CamadaFisicaTransmissoraDecodificacaoBinaria

vector<int> CamadaFisicaTransmissoraDecodificacaoManchester (vector<int> quadro) {

    vector<int> fluxoBrutoDeBits;

    for(int i = 0; i < quadro.size(); i+=2){
        // decodifica o quadro:
        if(quadro[i] == 0 && quadro[i+1] == 1){
            // "0 1" eh traduzido como 0
            fluxoBrutoDeBits.push_back(0);
        } else if (quadro[i] == 1 && quadro[i+1] == 0) {
            // "1 0" eh traduzido como 1
            fluxoBrutoDeBits.push_back(1);
        } else {
            // algum erro na transmissão ocorreu
        }
    }

    return fluxoBrutoDeBits;

}//fim do metodo CamadaFisicaTransmissoraDecodificacaoManchester

vector<int> CamadaFisicaTransmissoraDecodificacaoBipolar (vector<int> quadro) {

    //implementacao do algoritmo
    return quadro;

}//fim do metodo CamadaFisicaTransmissoraDecodificacaoBipolar

void CamadaDeAplicacaoReceptora (vector<int> quadro) {

    //mostraMensagemEmBits(quadro);
    
    string mensagem = "";

    for(int i = 0; i < quadro.size()/8; i++){
        char charAtual = 0; // 1111 1111
        for(int j = 0; j < 8; j++){
            charAtual |= (quadro[i*8 + j] << (7-j));
        }
        mensagem.push_back(charAtual);
    } //fim do for

    //chama a proxima camada
    AplicacaoReceptora(mensagem);
}// fim do metodo CamadaDeAplicacaoReceptora

void AplicacaoReceptora (string mensagem) {
    cout << "A mensagem recebida foi: " << mensagem << endl;
}// fim do metodo AplicacaoReceptora

void mostraMensagemEmBits (vector<int> quadro) {
    //mostra a mensagem convertida em bits
    for(int i = 0; i < quadro.size()/8; i++){
        for(int j = 0; j < 8; j++){
            cout << quadro[i*8 + j] << " ";
        }
        cout << endl;
    } //fim do for
    cout << endl;
}// fim metodo mostraMensagemEmBits