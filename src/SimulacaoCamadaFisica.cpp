#include "../include/SimulacaoCamadaFisica.h"

int main(void){
    AplicacaoTransmissora();
}// fim do metodo main

void AplicacaoTransmissora (void) {
    string mensagem;
    cout << "Digite uma mensagem" << endl;
    cin >> mensagem;

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
    int tipoDeCodificacao = 0; // alterar de acordo com o teste
    vector<int> fluxoBrutoDeBits; // Bits e não bytes!

    switch (tipoDeCodificacao) {
        case 0: // codificacao binaria
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
            break;
        case 1: // codificacao manchester
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
            break;
        case 2: // codificacao bipolar
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBipolar(quadro);
            break;
        default:
            break;
    }//fim do switch case

    MeioDeComunicacao(fluxoBrutoDeBits);
}// fim do metodo de CamadaFisicaTransmissora

vector<int> CamadaFisicaTransmissoraCodificacaoBinaria (vector<int> quadro) {

    //implementacao do algoritmo
    return quadro;

}//fim do metodo CamadaFisicaTransmissoraCodificacaoBinaria

vector<int> CamadaFisicaTransmissoraCodificacaoManchester (vector<int> quadro) {

    //implementacao do algoritmo
    return quadro;

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
    int tipoDeCodificacao = 0; // alterar de acordo com o teste
    vector<int> fluxoBrutoDeBits; // Bits e não bytes!

    switch (tipoDeCodificacao) {
        case 0: // codificacao binaria
            fluxoBrutoDeBits = CamadaFisicaTransmissoraDecodificacaoBinaria(quadro);
            break;
        case 1: // codificacao manchester
            fluxoBrutoDeBits = CamadaFisicaTransmissoraDecodificacaoManchester(quadro);
            break;
        case 2: // codificacao bipolar
            fluxoBrutoDeBits = CamadaFisicaTransmissoraDecodificacaoBipolar(quadro);
            break;
        default:
            break;
    }//fim do switch case

    CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
}

vector<int> CamadaFisicaTransmissoraDecodificacaoBinaria (vector<int> quadro) {

    //implementacao do algoritmo
    return quadro;

}//fim do metodo CamadaFisicaTransmissoraDecodificacaoBinaria

vector<int> CamadaFisicaTransmissoraDecodificacaoManchester (vector<int> quadro) {

    //implementacao do algoritmo
    return quadro;

}//fim do metodo CamadaFisicaTransmissoraDecodificacaoManchester

vector<int> CamadaFisicaTransmissoraDecodificacaoBipolar (vector<int> quadro) {

    //implementacao do algoritmo
    return quadro;

}//fim do metodo CamadaFisicaTransmissoraDecodificacaoBipolar

void CamadaDeAplicacaoReceptora (vector<int> quadro) {
    
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
}// fim metodo mostraMensagemEmBits