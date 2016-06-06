# Centro comercial

Autor: Vítor Passos Pontes  
Matrícula: 13/0137421  
Disciplina: 116297  
Turma: E  

## Introdução

Esse projeto foi realizado como trabalho para a disciplina "Tópicos avançados em computadores" na turma de Programação concorrente na Universidade de Brasilia: UnB no primeiro semestre de 2016.  
O objetivo central do trabalho é criar uma simulação simplificada de um centro
comercial utilizando as técnicas de controle de concorrência aprendidas para solucionar os problemas de condição de corrida.

## Formalização do Problema

Nesse programa todos os agentes são threads e devem ser capazes de alterar e acessar os recursos compartilhados concorrentemente. A simulação deve controlar concorrentemente as threads de pessoas, Lojas e carros para garantir que as pessoas consigam alcançar as lojas, realizar uma compra e no fim do estoque a loja deve chamar os carros que irão trazer mais produtos. Simultaneamente uma thread irá imprimir o mapa e estoque atual das lojas.

As principais entidades presentes no trabalho são:

- Pessoas
- Lojas
- Carros

As principais atividades realizadas pelo projeto são:

- Compra de produtos pelas pessoas
- Venda de produtos pela lojas
- Controle e impressão do mapa
- Controle da movimentação das entidades no mapa
- Reabastecimento do estoque das lojas pelos carros

## Concorrência

O programa possui 4 tipos de threads: As lojas, pessoas, carros e a de impressão.
O controle de concorrência entre essas threads é feita utilizando semáforos, locks e variáveis de condição. As situações que são utilizadas são:

- Semáforos
    + Capacidade das filas das lojas
    + Atendimento dos clientes
- Locks
    + Acesso aos estoques das lojas
    + Alteração do mapa 
    + Ocupação das celulas do mapa
- Variáveis de condição
    + Controle do reabastecimento do estoque das lojas

## Algoritmo

O primeiro problema de concorrência abordado foi o controle do mapa. Para isso criou-se uma matriz de locks de mesmo tamanho da matriz do mapa. Quando uma thread pega um lock ela fica com esse lock até se movimentar para indicar que está ocupando aquela posição. Para movimentação as threads pegam o proximo lock, realizam a alteração do mapa e liberam o lock anterior.

O proximo problema foi o controle das filas e atendimento das lojas. No caso da fila foi utilizado um semáforo. As pessoas tentam entrar na fila e caso não haja permissões o suficiente elas vão embora. Apôs entrar na fila e chegar a vez da pessoa ser atendida ela informa o vendedor e espera ser avisada do término do atendimento para ir embora. Essa comunicação é feita através de semáforos assemelhando-se ao estudo dirigido do barbeiro.

Por último foi feito o controle do estoque. O estoque possui um lock de acesso que é usado pelas lojas e carros para realizar alterações e pela thread de impressão para verificar o estoque das lojas antes de imprimir. Após toda venda o vendedor verifica o estoque e, caso não haja mais produtos, sinaliza o carro responsável através de uma variável de condição. Por sua vez o carro se dirige a loja e enche o estoque, enquanto o vendedor interrompe as vendas esperando o carro finalizar.

O programa se encerra quando todas as pessoas tiverem deixado o centro comercial.


## Representação

- O "V" branco de vendedor representa a posição das lojas
- O "P" amarelo representa as pessoas
- Os carros são representados por 2 "C"s para parte de trás e 2 "c"s para parte da frente
- Os "." verdes representam onde as pessoas podem se movimentar e o "*" as ruas para os carros
- Os outros símbolos são apenas divisórias e a movimentação neles é proibida

## Estrutura de pastas

- /docs
    + Armazena documentação do projeto
    + Maiores informações sobre os módulos e suas atribuições do projeto no arquivo Docs/modulos.txt
- /build
    + Diretório onde é compilado e executado o programa
- /src
    + Armazena diretórios principais do projeto
- /src/code
    + Armazena arquivos ".c" do projeto
- /src/include
    + Armazena arquivos ".h" do projeto
- /src/files
    + Armazena arquivos utilizados pelo programa

## Compilando e executando

Para compilar o projeto é utilizado um makefile. Na pasta raiz do projeto onde se encontra o makefile utilize o comando `make` e `make run` para executá-lo.

O modelo de comando utilizado para compilar o objeto dos módulos é:
`gcc src/code/NomeModulo.c -Wall -Wstrict-prototypes  -c -o build/NomeModulo.o`

O comando utilizado para compilar o executável é exatamente:
`gcc -Wall -Wstrict-prototypes  -pthread -o build/comercial build/carro.o build/loja.o build/main.o build/pessoa.o build/shop.o`
