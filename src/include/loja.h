#ifndef LOJA_H
#define LOJA_H

#define LOJAS 9
#define LOJA_INIT_CHAR 'V'
#define ESTOQUE_MAX 30
#define FILA_MAX 2

struct celula;
typedef struct Celula celula;

typedef struct Loja{
  int id;       // Identificador
  int estoque;
  celula* pos;  // Posição do vendedor
}loja;

void criar_loja(int);

void destruir_loja(int);

void comprar(int);

int total_lojas(void);

celula* pos_loja(int);

#endif
