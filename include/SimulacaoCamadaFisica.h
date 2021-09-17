#ifndef INCLUDE_SIMULACAO_CAMADA_FISICA_H_
#define INCLUDE_SIMULACAO_CAMADA_FISICA_H_

#include <iostream>
#include <vector>
#include "stdio.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

void AplicacaoTransmissora (void);
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