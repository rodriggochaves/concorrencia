#ifndef SHOP_H
#define SHOP_H

typedef struct Celula{
  int linha;
  int coluna;
}celula;

void mover(celula*,celula*);

void cria_shop(void);

void imprime_shop(void);

void inicia_pessoa(celula*);

void inicia_caminhao(celula* cels[]);

#endif