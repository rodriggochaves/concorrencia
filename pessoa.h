#ifndef PESSOA_H
#define PESSOA_H

struct celula;
typedef struct Celula celula;

typedef struct Pessoa{
  int id;
  celula* cel;
  float  dinheiro;
}pessoa;

#endif