#include "../include/pessoa.h"
#include "../include/shop.h"



#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

pthread_t pessoas[PESSOAS];
pthread_mutex_t print = PTHREAD_MUTEX_INITIALIZER;

// Verifica para onde a pessoa deve andar
int avancar_pessoa(celula* ps,celula* loja){
  celula* aux = malloc(sizeof(celula));
  aux->linha = ps->linha;
  aux->coluna = aux->coluna;
  int flag = 0;

  if(ps->coluna < loja->coluna){
    aux->coluna = ps->coluna + 1;
    // printf("coluna menor aux: %d\n",aux->coluna);
    flag = mover(ps,aux);
  }
  else{
    if(ps->coluna == loja->coluna){
      if(ps->linha < (loja->linha - 1)){
        aux->linha = ps->linha + 1;
      }
      if( ps->linha > (loja->linha + 1)){
        aux->linha = ps->linha - 1;
      }
      // printf("coluna igual\n");
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

  // printf("nada\n");
  return 0;
}

void* cliente(void *arg){
  pessoa* ps = ((pessoa *) arg);
  celula* loja = malloc(sizeof(celula));

  inicia_pessoa(ps->cel);

  loja->linha = 7;
  loja->coluna = 10;
  while(1){
    avancar_pessoa(ps->cel,loja);
    pthread_mutex_lock(&print);
    imprime_shop();
    pthread_mutex_unlock(&print);
  }
  
    
  // for (i = 0; i < 10; ++i){
  //   if(!mover(ps->cel,prox)){
  //     ps->cel->linha = prox->linha;
  //     ps->cel->coluna = prox->coluna;
  //   }
  //   prox->coluna += 1;
  // }
  // prox->linha = ps->cel->linha ;
  // prox->coluna = ps->cel->coluna ;

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