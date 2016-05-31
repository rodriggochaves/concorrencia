#ifndef PESSOA_H
#define PESSOA_H
#define PESSOAS 100

struct celula;
typedef struct Celula celula;

typedef struct Pessoa{
  int id;
  celula* cel;
}pessoa;

void criar_pessoa(int);

void destruir_pessoa(int);

#endif