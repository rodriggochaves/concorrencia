#include "../include/pessoa.h"
#include "../include/shop.h"
#include "../include/loja.h"


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


pthread_t pessoas[PESSOAS];
pthread_mutex_t print = PTHREAD_MUTEX_INITIALIZER;

// Verifica para onde a pessoa deve andar para se aproximar do vendedor
// Essa função funciona apenas para a movimentação em cruz usada no shop
int avancar_pessoa(celula* ps,celula* loja){
  
  // Se flag diferente de 0 houve uma movimentação
  int flag = 0;

  celula* aux = malloc(sizeof(celula));
  aux->linha = ps->linha;
  aux->coluna = ps->coluna;

  if(ps->coluna < loja->coluna){
    aux->coluna = ps->coluna + 1;
    flag = mover(ps,aux);

  } else {
    if(ps->coluna == loja->coluna){        
      flag = 1;
    } 
  } 
  if(!flag){
    ps->linha = aux->linha;
    ps->coluna = aux->coluna;
    return flag;
  } else {
    return flag;
  }
}

int move_vertical(celula* ps,celula* loja){
  int flag = 0;
  celula* aux = malloc(sizeof(celula));
  aux->linha = ps->linha;
  aux->coluna = ps->coluna;

  if(ps->linha < (loja->linha - 1)){
        aux->linha = ps->linha + 1;
  }
  if( ps->linha > (loja->linha + 1)){
    aux->linha = ps->linha - 1;
  }
  if( ps->linha == (loja->linha - 1) || ps->linha == (loja->linha + 1) ){
    flag = 1;
  } else {  
    flag = mover(ps,aux);
  }

  if(!flag){
    ps->linha = aux->linha;
    ps->coluna = aux->coluna;
    return flag;
  } else {
    return flag;
  }
}

// 
int meia_volta(celula* ps){
  
  celula* aux = malloc(sizeof(celula));
  aux->linha = ps->linha;
  aux->coluna = ps->coluna + 1;
  sleep(1);
  if(mover(ps,aux)){
    
    return 1;
  } else {
    
    ps->linha = aux->linha;
    ps->coluna = aux->coluna;
    return 0;
  }
}

// Lógica de movimentação até a saida
int voltar_pessoa(celula* ps,celula* saida){
  
  // Se flag diferente de 0 houve uma movimentação
  int flag = 0;
  int dif;
  celula* aux = malloc(sizeof(celula));
  aux->linha = ps->linha;
  aux->coluna = ps->coluna;

  if(ps->linha == saida->linha){
    if (ps->coluna != saida->coluna){
      aux->coluna -= 1;
      flag = mover(ps,aux);
    } else {
      // Chegou na saida
      flag = 1;
    }
  } else {
    dif = ps->linha - saida->linha;
    if(dif < 0){
      aux->linha += 1;
      flag = mover(ps,aux);
    } else {
      aux->linha -= 1;
      flag = mover(ps,aux);
    }
  }
  if(!flag){
    ps->linha = aux->linha;
    ps->coluna = aux->coluna;
    return flag;
  }
  else{
    return flag;
  }
}

void* cliente(void *arg){
  
  pessoa* ps = ((pessoa *) arg);
  
  celula* loja = malloc(sizeof(celula));
  celula* saida = malloc(sizeof(celula));
  
  int total_loja = total_lojas();
  int loja_id;
  // Insere pessoa no mapa
  inicia_pessoa(ps->cel);

  saida = celula_saida_pessoa();
  //substituir por vendedor
  
  // Define aleatoriamente a loja que a pessoa irá
  loja_id = rand()%total_loja;

  // Descobre pelo id a posição da loja
  loja = pos_loja(loja_id);

  while(!avancar_pessoa(ps->cel,loja)){
    usleep(100000);
  }
  if(checar_fila(loja_id)){
    while(!move_vertical(ps->cel,loja)){
      usleep(100000);
    }
    comprar(loja_id);    
    meia_volta(ps->cel); // realiza movimentação
    usleep(100000);
  }
  while(!voltar_pessoa(ps->cel,saida)){
    usleep(100000);
  }

  remover(ps->cel,'.');

  free(ps);
  pthread_exit(0);
}


void criar_pessoa(int id){
  pessoa* ps = malloc(sizeof(*ps));
  ps->cel = malloc(sizeof(celula));
  ps->id = id;
  pthread_create(&pessoas[id],NULL,cliente,(void *) (ps));
}

void destruir_pessoa(int id){
  pthread_join(pessoas[id],NULL);
}