
SIMULACAO - CAMADA FÍSICA======

1. Compilação:

	Para compilar o projeto, deve-se primeiro instalar as dependências:
	$ sudo ./dependencies.sh

	Depois basta executar o comando de compilação:
	$ sudo ./compile.sh
	
	E executar o projeto:
	$ ./simulacao

	------------------------
	
2. Trocar a codificação:

	Para trocar o tipo de codificação/modulação:
	  Alterar a variável "tipoDeCodificacao",
	no arquivo "CamadaFisica.cpp".

	int tipoDeCodificacao = CODIFICACAO_BIPOLAR;
	int tipoDeCodificacao = CODIFICACAO_MANCHESTER;
	int tipoDeCodificacao = CODIFICACAO_BINARIA;
	
3. Observação:

	Ao executar o código, deixe o terminal em tela cheia,
	para que você veja a interface gráfica completamente.
