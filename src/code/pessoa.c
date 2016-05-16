#include "../include/pessoa.h"
#include "../include/shop.h"



#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

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
    // printf("coluna menor aux: %d\n",aux->coluna);
    flag = mover(ps,aux);

  } else {
    if(ps->coluna == loja->coluna){
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

// 
int meia_volta(celula* ps){
  
  celula* aux = malloc(sizeof(celula));
  aux->linha = ps->linha;
  aux->coluna = ps->coluna + 1;
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

  printf("pl: %d sl: %d\n",ps->linha,saida->linha );
  if(ps->linha == saida->linha){
    printf("entrou 1\n");
    if (ps->coluna != saida->coluna){
      aux->coluna -= 1;
      flag = mover(ps,aux);
    } else {
      // Chegou na saida
      flag = 1;
    }
  } else {
    printf("entrou 2\n");
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
  // Insere pessoa no mapa
  inicia_pessoa(ps->cel);

  saida = celula_saida_pessoa();
  //substituir por vendedor
  loja->linha = 12;
  loja->coluna = 5;

  while(!avancar_pessoa(ps->cel,loja)){
    pthread_mutex_lock(&print);
    printf("linha:%d coluna:%d\n",ps->cel->linha,ps->cel->coluna );
    imprime_shop();
    pthread_mutex_unlock(&print);
  }
  meia_volta(ps->cel);
  printf("linha:%d coluna:%d\n",ps->cel->linha,ps->cel->coluna );
  pthread_mutex_lock(&print);
  imprime_shop();
  pthread_mutex_unlock(&print); 
  while(!voltar_pessoa(ps->cel,saida)){
    pthread_mutex_lock(&print);
    printf("linha:%d coluna:%d\n",ps->cel->linha,ps->cel->coluna );
    imprime_shop();
    pthread_mutex_unlock(&print); 
  }

  pthread_mutex_lock(&print);
  remover(ps->cel,'.');
  imprime_shop();
  printf("linha:%d coluna:%d\n",ps->cel->linha,ps->cel->coluna );
  pthread_mutex_unlock(&print); 

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