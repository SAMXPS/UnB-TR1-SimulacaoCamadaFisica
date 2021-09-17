#include "SimulacaoCamadaFisica.hpp"

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

    for(int i = 0; i < mensagem.size(); i++){
        quadro.push_back(mensagem[i]);
    } //fim do for

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

int [] CamadaFisicaTransmissoraCodificacaoBinaria (int quadro []) {

    //implementacao do algoritmo

}//fim do metodo CamadaFisicaTransmissoraCodificacaoBinaria

int [] CamadaFisicaTransmissoraCodificacaoManchester (int quadro []) {

    //implementacao do algoritmo

}//fim do metodo CamadaFisicaTransmissoraManchester

int [] CamadaFisicaTransmissoraCodificacaoBipolar (int quadro []) {

    //implementacao do algoritmo

}//fim do metodo CamadaFisicaTransmissoraCodificacaoBipolar

/** Este metodo simula a transmissao da informacao no meio de
 * comunicacao, passando de um ponto A (transmissor) para um
 * ponto B (receptor)
 * **/
void MeioDeComunicacao (int fluxoBrutoDeBits []){
    int fluxoBrutoDeBitsPontoA[], fluxoBrutoDeBitsPontoB[];

    fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

    while (fluxoBrutoDeBitsPontoB.lenght != fluxoBrutoDeBitsPontoA) {
        fluxoBrutoDeBitsPontoB += fluxoBrutoDeBitsPontoA;
    }//fim do while

    //chama a proxima camada
    CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}//fim do metodo MeioDeTransmissão

void CamadaFisicaReceptora (int quadro []){
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

int [] CamadaFisicaTransmissoraDecodificacaoBinaria (int quadro []) {

    //implementacao do algoritmo

}//fim do metodo CamadaFisicaTransmissoraDecodificacaoBinaria

int [] CamadaFisicaTransmissoraDecodificacaoManchester (int quadro []) {

    //implementacao do algoritmo

}//fim do metodo CamadaFisicaTransmissoraDecodificacaoManchester

int [] CamadaFisicaTransmissoraDecodificacaoBipolar (int quadro []) {

    //implementacao do algoritmo

}//fim do metodo CamadaFisicaTransmissoraDecodificacaoBipolar

void CamadaDeAplicacaoReceptora (int quadro []) {
    string mensagem = quadro [];

    //chama a proxima camada
    AplicacaoReceptora(mensagem);
}// fim do metodo CamadaDeAplicacaoReceptora

void AplicacaoReceptora (string mensagem) {
    cout << "A mensagem recebida foi: " << mensagem << endl;
}// fim do metodo AplicacaoReceptora