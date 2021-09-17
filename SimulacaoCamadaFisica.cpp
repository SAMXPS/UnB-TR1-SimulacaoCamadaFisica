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
    int quadro [] = mensagem; // trabalhar com bits

    //chama a proxima camada
    CamadaFisicaTransmissora(quadro);
}// fim do metodo de CamadaDeAplicacaoTransmissora

void CamadaFisicaTransmissora(int quadro []) {
    int tipoDeCodificacao = 0; // alterar de acordo com o teste
    int fluxoBrutoDeBits []; // Bits e não bytes!

    switch (tipoDeCodificacao) {
        case 0: // codificacao binaria
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
            break;
        case 1: // codificacao manchester
            fluxoBrutoDeBits = CamadaFisicaTransmissoraManchester(quadro);
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

int [] CamadaFisicaTransmissoraManchester (int quadro []) {

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

void CamadaDeAplicacaoReceptora (int quadro []) {
    string mensagem = quadro [];

    //chama a proxima camada
    AplicacaoReceptora(mensagem);
}// fim do metodo CamadaDeAplicacaoReceptora

void AplicacaoReceptora (string mensagem) {
    cout << "A mensagem recebida foi: " << mensagem << endl;
}// fim do metodo AplicacaoReceptora