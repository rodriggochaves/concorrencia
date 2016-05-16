#ifndef LOJA_H
#define LOJA_H

#define LOJAS 9
#define LOJA_INIT_CHAR 'V'

struct celula;
typedef struct Celula celula;

typedef struct Loja{
  int id;       // Identificador
  char sim;     // Simbolo de representação da loja
  celula* pos;  // Posição do vendedor
}loja;

void criar_loja(int);

void destruir_loja(int);

int total_lojas(void);

#endif
