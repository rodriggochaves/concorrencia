#include "../include/shop.h"
#include "../include/pessoa.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


#define LINHAS 17
#define COLUNAS 57

char shop[LINHAS][COLUNAS];
int inicio_pessoa[2];
int saida_pessoa[2];
int inicio_carro[2];

pthread_mutex_t mlock[LINHAS][COLUNAS];

//Extrai mapa do arquivo e carrega dados em memória
void cria_shop(){
  int i,j;
  char cel;
  FILE* fp;
  
  fp=fopen("./src/files/shop.txt", "r");
  
	for (i = 0; i < LINHAS; ++i){
   
		for (j = 0; j < COLUNAS; ++j){
      cel = fgetc(fp);   
      //checa se é a posição de inicio de pessoas   
      if(cel == 'p'){
        inicio_pessoa[0] = i;
        inicio_pessoa[1] = j;
        cel = '.'; 
      }
      //checa se é a posição de saida das pessoas
      if(cel == 's'){
        saida_pessoa[0] = i;
        saida_pessoa[1] = j;
        cel = '.';
      }  
      //checa se é a posição de inicio de carros
      if(cel == 'c'){
        inicio_carro[0] = i;
        inicio_carro[1] = j;
        cel = '*';
      }       
      shop[i][j] = cel;                 // atribui char a matriz
      pthread_mutex_init(&mlock[i][j],NULL); //inicializa lock da celula
    }
  }
  fclose(fp);
}

//retorna 1 se a celula pode ser ocupada e 0 caso contrário
int valido(int linha, int coluna){
  char c = shop[linha][coluna];
  if (c != '-' && c != '|' && c != '=' && c != '_' && c != 'V'){
    return 1;
  } else {
    return 0;
  }
}

// Pega lock inicial
void inicia_pessoa(celula* cel){
  
  int linha = inicio_pessoa[0];
  int coluna = inicio_pessoa[1];

  pthread_mutex_lock(&mlock[linha][coluna]); // Pega lock da celula
  shop[linha][coluna] = 'P';
  
  cel->coluna = coluna;
  cel->linha = linha;
}


// Move caractere da celula ini para celula prox, caso a movimentação seja valida
int mover(celula* ini,celula* prox){
  
  int linha,coluna;
  int nlinha,ncoluna;
  char charini,charprox;

  linha = ini->linha;
  coluna = ini->coluna;

  nlinha = prox->linha;
  ncoluna = prox->coluna;

  if (valido(nlinha,ncoluna)){
    // printf("esperando: %d %d\n",nlinha,ncoluna);    
    pthread_mutex_lock(&mlock[nlinha][ncoluna]);
    pthread_mutex_unlock(&mlock[linha][coluna]);
    
    charini = shop[linha][coluna];
    charprox = shop[nlinha][ncoluna];
    if(charini == '.'){
      printf("OPA,opa\n");
    }
    // Faz troca dos char das duas celulas
    shop[linha][coluna] = charprox;
    shop[nlinha][ncoluna] = charini;

    // printf("movido para %d %d\n",nlinha,ncoluna );
  
    return 0;
  
  } else {
  
    return 1;
  }
}

//printa o shop
void imprime_shop(){
  // pthread_create(,NULL,thread_imprime,NULL);
  int i,j;
  for (i = 0; i < LINHAS; ++i)   {
    for (j = 0; j < COLUNAS; ++j){
      printf("%c",shop[i][j]);        
    }
  }
  printf("\n");
  fflush(stdout);
  usleep(50000);
}

/*
========================================================
c******************************************************|
*******************************************************|
========#==========#===========#=========#=======******|
|....|..V.......|..V.........|.V......|..V......|******|
|....|..........|............|........|.........|******|
|....|___....___|____....____|__....__|___...___|******|
p...............................................|******|
................................................|******|
................................................|******|
|---...---|---...---|---...---|---...---|--...--|******|
|.........|.........|.........|.........|.......|******|
|....V....|....V....|....V....|....V....|...V...|******|
=====#=========#=========#=========#========#====******|
*******************************************************|
*******************************************************|
========================================================
*/
