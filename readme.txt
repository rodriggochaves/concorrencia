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
