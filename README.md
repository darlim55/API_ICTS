# API_ICTS

### Desafio Backend:

Chico é um amante de tecnologia, em sua casa nova, instalou sensores de
temperatura e de consumo de energia para o monitoramento dos dois quartos,
da sala e da cozinha, porém ainda não consegue organizar as informações
coletadas e precisa de uma ferramenta que possa visualizar todos os dados de
maneira centralizada. Diante deste cenário, Chico está pedindo sua ajuda para
desenvolver uma API REST e um MIDDLEWARE para que possa utilizar suas
funcionalidades.

Sua missão será criar uma API que retorne as seguintes informações:

- Listar todos os sensores de temperatura.
- Listar um sensor de temperatura especíﬁco.
- Listar todos sensores de consumo (kwh).
- Listar o sensor que mais consumiu energia.
- Alterar o nome de um sensor.
- Alterar a disposição de um sensor.

Criar uma aplicação tipo MIDDLEWARE (Programa utilizando a linguagem C++)
para consumir a API desenvolvida que tenha as seguintes funcionalidades:


- Listar todos os sensores de temperatura.
- Listar um sensor de temperatura especíﬁco.
- Listar todos sensores de consumo (kwh).
- Listar o sensor que mais consumiu energia.
- Alterar o nome de um sensor.
- Alterar a disposição de um senso.

## Roda API

Para rodar API localmente você deve ter o node instalado no seu computador.

Após a instalação do node, faça o clone desse repositório e dentro da pasta rode o seguinte comando para instalar as dependências :

> npm install

Para rodar o servidor localmente:

> npm run dev

Com o servidor rodando voce testar os endpoints com o POSTMAN ou THUNDER CLIENT.

**Obs: Caso de erro de porta, verifique se a porta 3000 ja esta em uso no seu computador.**


## Rodar arquivo C++

Os comando a baixo servem para linux e vscode.

Digite o seguinte comando no cmd para instalar a biblioteca do curl:
> sudo apt install curl

Digite o seguinte comando no cmd para gerar o executavel:
> c++ Api_consumo.c++ -lcurl -o get-data

Apos gerar o executável digite no cmd:
> ./get-data 

**Para rodar localmente o servidor e o código você precisara de 2 cmd's que devem estar dentro da pasta do repositório para os comandos funcionarem.**

**Obs: Lembrando que precisa-se instalar as bibliotecas do c++ no vscode e linux e estar dentro da pasta do projeto para os comandos funcionarem.**

**Respeitar os pedidos para digitar os valores inteiros, pois o tempo não foi suficiente para validar as entradas ao digitar uma string.**
