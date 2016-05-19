#include "../include/carro.h"
#include "../include/loja.h"
#include "../include/shop.h"

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

pthread_t carros[CARROS];
pthread_cond_t cond_carros[CARROS];
pthread_mutex_t lock_carros[CARROS];

int carro_direita(pos_carro*);

int carro_baixo(pos_carro*);

void virar_carro_baixo(pos_carro*);

void virar_carro_esquerda(pos_carro*);

int carro_esquerda(pos_carro*);

void remove_carro(pos_carro*);

int verifica_entrega(celula*,int);

void* carro_thread(void* arg){
  carro* car = ((carro*) arg);
  car->pos = malloc(sizeof(pos_carro));
  car->pos->topo_d = malloc(sizeof(celula));
  car->pos->topo_e = malloc(sizeof(celula));
  car->pos->baixo_d = malloc(sizeof(celula));
  car->pos->baixo_e = malloc(sizeof(celula));
  
  while(1){
    pthread_mutex_lock(&lock_carros[car->id]);
    while(estoque_loja(car->loja_id) > 0){
      pthread_cond_wait(&cond_carros[car->id],&lock_carros[car->id]);
    }
    pthread_mutex_unlock(&lock_carros[car->id]);

    // inicia carro na matriz
    inicia_carro(car->pos);
    // movimenta carro
    while(!carro_direita(car->pos)){
      if(verifica_entrega(car->pos->baixo_e,car->loja_id)){
        sleep(2);
        abastecer_loja(car->loja_id);
      }
      usleep(50000);
    }

    virar_carro_baixo(car->pos);

    while(!carro_baixo(car->pos)){
      usleep(50000);
    }

    virar_carro_esquerda(car->pos);

    while(!carro_esquerda(car->pos)){
      if(verifica_entrega(car->pos->topo_d,car->loja_id)){
        abastecer_loja(car->loja_id);
        sleep(2);
      }
      usleep(50000);
    }
    // abastece a loja
    remove_carro(car->pos);
    // vai embora
  }
  pthread_exit(0);
}

int verifica_entrega(celula* cel,int loja_id){
  celula* lj = malloc(sizeof(celula));
  int diff;
  lj = pos_loja(loja_id);

  if(cel->coluna == lj->coluna){
    diff = lj->linha - cel->linha;
    if(diff >= -2 && diff <= 2){
      return 1;
    }
  }
  return 0;
}

void virar_carro_baixo(pos_carro* pos){
  trocar_celula(pos->topo_d,pos->baixo_e);
}

void virar_carro_esquerda(pos_carro* pos){
  trocar_celula(pos->topo_e,pos->baixo_d);
}

void remove_carro(pos_carro* pos){
  remover(pos->topo_d,'*');
  remover(pos->topo_e,'*');
  remover(pos->baixo_d,'*');
  remover(pos->baixo_e,'*');
}

void chamar_carro(int id){
  pthread_cond_signal(&cond_carros[id]);
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

int carro_baixo(pos_carro* pos){

  if(!mover_baixo(pos->baixo_d)){
    mover_baixo(pos->baixo_e);
    mover_baixo(pos->topo_d);
    mover_baixo(pos->topo_e);
    return 0;
  } else {
    return 1;
  }
}

int carro_esquerda(pos_carro* pos){

  if(!mover_esquerda(pos->topo_e)){
    mover_esquerda(pos->baixo_e);
    mover_esquerda(pos->topo_d);
    mover_esquerda(pos->baixo_d);
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
