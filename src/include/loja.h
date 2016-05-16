#ifndef LOJA_H
#define LOJA_H

#define LOJAS 9

struct celula;
typedef struct Celula celula;

typedef struct Loja{
  int id; // Identificador
  celula* pos; //posição do vendedor  
}loja;

#endif
