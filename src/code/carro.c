#include "../include/carro.h"
#include "../include/loja.h"
#include "../include/shop.h"

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

pthread_t carros[CARROS];

int carro_direita(pos_carro*);

void* carro_thread(void* arg){
  carro* car = ((carro*) arg);
  car->pos = malloc(sizeof(pos_carro));
  car->pos->topo_d = malloc(sizeof(celula));
  car->pos->topo_e = malloc(sizeof(celula));
  car->pos->baixo_d = malloc(sizeof(celula));
  car->pos->baixo_e = malloc(sizeof(celula));
  
  // inicia carro na matriz
  inicia_carro(car->pos);
  // movimenta carro
  while(!carro_direita(car->pos)){
    usleep(50000);
  }
  // abastece a loja

  // vai embora

  pthread_exit(0);
}

int carro_direita(pos_carro* pos){

  if(!mover_direita(pos->topo_d)){
    mover_direita(pos->baixo_d);
    mover_direita(pos->topo_e);
    mover_direita(pos->baixo_e);
    return 0;
  } else {
    return 1;
  }
}

void criar_carro(int id){
  carro* car = malloc(sizeof(carro));
  car->id = id;
  car->loja_id = id;
  pthread_create(&carros[id],NULL,carro_thread,(void*) (car));
}
