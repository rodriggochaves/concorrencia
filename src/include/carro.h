#ifndef CARRO_H
#define CARRO_H

#define CARROS 9

struct celula;
typedef struct Celula celula;

typedef struct Pos_carro{
  celula* topo_d;
  celula* topo_e;
  celula* baixo_d;
  celula* baixo_e;
}pos_carro;

typedef struct Carro{
  int id;
  int loja_id;
  pos_carro* pos;
}carro;

void chamar_carro(int);

void criar_carro(int);

#endif
