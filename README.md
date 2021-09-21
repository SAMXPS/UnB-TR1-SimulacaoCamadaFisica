# Simulação - Camada Física


## Compilação e Execução

Para compilar o projeto, deve-se primeiro instalar as dependências:

```bash
sudo ./dependencies.sh
```

> O ambiente testado foi Ubuntu.

Depois basta executar o comando de compilação:`
```bash
sudo ./compile.sh
```

E executar o projeto:
```bash
./simulacao
```

## Uso da interface de usuário

A interface gráfica foi feita por meio da biblioteca nCurses.
Existem 3 telas, que serão explicadas a seguir.

### Tela inicial

Aqui existe um menu onde você pode escolher um dos 3 tipos de codificação disponíveis: NRZ, Manchester e Bipolar.

Você também pode sair do programa se escolher a última opção.

### Digitar mensagem

Após escolher o tipo de codificação, você deve digitar uma mensagem para ser transmitida.

### Simulação

Durante a simulação, você pode:
- Apertar a tecla _barra de espaço_ para pausar a simulação.
- Apertar _backspace_ para reiniciar a simulação.
- Apertar a teclar _F1_ para encerrar a simulação.

A simulação é composta de 3 gráficos:
1. O primeiro gráfico representa os bits que estão sendo trasmitidos.
2. O segundo gráfico representa as tensões transmititdas no meio físico.
3. O terceiro gráfico representa os bits que estão sendo recebidos.
