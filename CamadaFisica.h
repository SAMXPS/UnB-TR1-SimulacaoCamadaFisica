#ifndef INCLUDE_SIMULACAO_CAMADA_FISICA_H_
#define INCLUDE_SIMULACAO_CAMADA_FISICA_H_

#include <iostream>
#include <vector>
#include "stdio.h"

#define CODIFICACAO_BINARIA 0
#define CODIFICACAO_MANCHESTER 1
#define CODIFICACAO_BIPOLAR 2

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::getline;

// Variáveis para integração com interface de usuário
typedef struct  {
    std::string mensagem_transmitida;
    vector<int> quadro_transmitido;
    vector<int> tensoes;
    vector<int> quadro_recebido;
    std::string mensagem_recebida;
    int tipo_de_codificacao;
} contexto_simulacao;

void AplicacaoTransmissora (contexto_simulacao* contexto);
void CamadaDeAplicacaoTransmissora(string mensagem);
void CamadaFisicaTransmissora(vector<int> quadro);
vector<int> CamadaFisicaTransmissoraCodificacaoBinaria (vector<int> quadro);
vector<int> CamadaFisicaTransmissoraCodificacaoManchester (vector<int> quadro);
vector<int> CamadaFisicaTransmissoraCodificacaoBipolar (vector<int> quadro);
void MeioDeComunicacao (vector<int> fluxoBrutoDeBits);
void CamadaFisicaReceptora (vector<int> quadro);
vector<int> CamadaFisicaTransmissoraDecodificacaoBinaria (vector<int> quadro);
vector<int> CamadaFisicaTransmissoraDecodificacaoManchester (vector<int> quadro);
vector<int> CamadaFisicaTransmissoraDecodificacaoBipolar (vector<int> quadro);
void CamadaDeAplicacaoReceptora (vector<int> quadro);
void AplicacaoReceptora (string mensagem);

void mostraMensagemEmBits (vector<int> quadro);

#endif  // INCLUDE_SIMULACAO_CAMADA_FISICA_H_