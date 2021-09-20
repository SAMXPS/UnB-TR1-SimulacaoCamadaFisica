#include "CamadaFisica.h"

int tipoDeCodificacao = CODIFICACAO_BIPOLAR; // alterar de acordo com o teste
contexto_simulacao* contexto;

/**
 * Aplicação transmissora recebe um contexto de simulação e inicia a pilha de
 * protocolos de transmissão e recepção, salvando os resultados no contexto.
 */
void AplicacaoTransmissora (contexto_simulacao* novo_contexto) {
    contexto = novo_contexto; 
    tipoDeCodificacao = contexto->tipo_de_codificacao;
    CamadaDeAplicacaoTransmissora(contexto->mensagem_transmitida);
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
    contexto->quadro_transmitido = quadro; // Integração com a simulação
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

    contexto->tensoes = fluxoBrutoDeBits; // Integração com a simulação
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

    // utilizando a codificacao alternate mark inversion
    // 1 eh representado como 1 ou -1 - alternando

    int valorUltimo1 = -1;

    vector<int> fluxoBrutoDeBits;

    for(int i = 0; i < quadro.size(); i++){
        if(quadro[i] == 0){
            // 0 eh representado como 0
            fluxoBrutoDeBits.push_back(0);
        }
        
        if (quadro[i] == 1) {
            // 1 eh representado como 1 ou -1 - alternando
            valorUltimo1 = (valorUltimo1 < 0) ? 1 : -1;
            fluxoBrutoDeBits.push_back(valorUltimo1);
        }
    }

    return fluxoBrutoDeBits;

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

    contexto->quadro_recebido = fluxoBrutoDeBits; // Integração com a simulação
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

    // decodificacao do alternated mark inversion

    vector<int> fluxoBrutoDeBits;

    for(int i = 0; i < quadro.size(); i++){
        if(quadro[i] == 0){
            // 0 eh representado como 0
            fluxoBrutoDeBits.push_back(0);
        }
        
        if (quadro[i] == 1 || quadro[i] == -1) {
            // 1 eh representado como 1 ou -1
            fluxoBrutoDeBits.push_back(1);
        }
    }

    return fluxoBrutoDeBits;

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
    contexto->mensagem_recebida = mensagem; // Integração com a simulação
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