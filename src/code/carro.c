#include "../include/carro.h"
#include "../include/loja.h"
#include "../include/shop.h"

#include <pthread.h>
#include <stdlib.h>

pthread_t carros[CARROS];

void* carro_thread(void* arg){
  carro* car = ((carro*) arg);
  car->pos = malloc(sizeof(pos_carro));
  // inicia carro na matriz
  car->pos->topo_d->linha = 1;
  //inicia_carro(car->pos);
  // movimenta carro

  // abasteça loja

  // vai embora

  pthread_exit(0);
}

void criar_carro(int id){
  carro* car = malloc(sizeof(carro));
  car->id = id;
  car->loja_id = id;
  pthread_create(&carros[id],NULL,carro_thread,(void*) (car));
}
