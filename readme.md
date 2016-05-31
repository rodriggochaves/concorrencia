#Centro comercial

Autor: Vítor Passos Pontes
Matrícula: 13/0137421
Disciplina: 116297
Turma: E

##Introdução

Esse projeto foi realizado como trabalho para a disciplina "Tópicos avançados em computadores" na turma de Programação concorrente.
O objetivo central do trabalho é criar uma simulação simplificada de um centro
comercial utilizando as técnicas de controle de concorrência aprendidas.

##Descrição

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

O andamento do programa começa com as pessoas. A cada uma é designada uma loja aleatória, então a pessoa começa a se movimentar em direção a loja. Quando o cliente se aproxima da loja ele verifica se há espaço na fila, caso não haja ele vai embora. 
Ao entrar na fila e chegar sua vez a pessoa é atendida, realiza sua compra e vai embora. No momento que o estoque da loja acaba ela para de vender e requisita um reabastecimento aos Carros.
Os carros, quando requisitados, se dirigem a loja reabastecendo o estoque da loja a sua capacidade máxima.

##Concorrência

O programa possui 4 tipos de threads: As lojas, pessoas, carros e a de impressão.
O controle de concorrência entre essas threads é feita utilizando semáforos, locks e variáveis de condição. As situações que são utilizadas são:

- Semáforos:
    + Capacidade das filas das lojas
    + Atendimento dos clientes
- Locks:
    + Acesso aos estoques das lojas
    + Alteração do mapa 
    + Ocupação das celulas do mapa ex: Quando uma entidade ocupa uma celula ela possui o lock daquela célula.
- Variáveis de condição:
    + Controle do reabastecimento do estoque das lojas

##Representação

- O "V" branco de vendedor representa a posição das lojas
- O "P" amarelo representa as pessoas
- Os carros são representados por 2 "C"s para parte de trás e 2 "c"s para parte dianteira
- Os "." verdes representam onde as pessoas podem se movimentar e o "*" as ruas para os carros
- Os outros símbolos são apenas divisórias

##Estrutura de pastas

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

##Compilando e executando

Para compilar o projeto utilize o comando "make" e "make run" para executá-lo.