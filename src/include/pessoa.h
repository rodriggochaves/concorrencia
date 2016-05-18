#ifndef PESSOA_H
#define PESSOA_H
#define PESSOAS 10

struct celula;
typedef struct Celula celula;

typedef struct Pessoa{
  int id;
  celula* cel;
  float  dinheiro;
}pessoa;

void criar_pessoa(int);

void destruir_pessoa(int);

#endif