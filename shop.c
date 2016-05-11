#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define LINHAS 17
#define COLUNAS 57

char shop[LINHAS][COLUNAS];
int inicio_pessoa[2];
int inicio_carro[2];

pthread_mutex_t inips=PTHREAD_MUTEX_INITIALIZER, mlock[LINHAS][COLUNAS];

//Extrai mapa do arquivo
void cria_shop(){
  int i,j;
  char cel;
  FILE* fp;
  
  fp=fopen("./shop.txt", "r");
  
	for (i = 0; i < LINHAS; ++i){
   
		for (j = 0; j < COLUNAS; ++j){
      cel = fgetc(fp);   
      //checa se é a posição de inicio de pessoas   
      if(cel == 'p'){
        inicio_pessoa[0] = i;
        inicio_pessoa[1] = j;
        cel = '.'; 
      }
      //checa se é a posição de inicio de carros
      if(cel == 'c'){
        inicio_carro[0] = i;
        inicio_carro[1] = j;
        cel = '*';
      }       

      shop[i][j] = cel;               // atribui char a matriz
      pthread_mutex_init(&mlock[i][j]); //inicializa lock da celula
    }
  }
  fclose(fp);
}

//retorna 1 se a celula pode ser ocupada, chamador deve conter controle de acesso da celula
int valido(int linha, int coluna){
  char c = shop[linha][coluna];
  if (c != '-' && c != '|' && != '=' && c != '_' && c != 'V'){
    return 1;
  } else {
    return 0;
  }
}

// Pega lock inicial
void inicia_pessoa(){
  int linha;
  int coluna;

  coluna = inicio_pessoa[1];
  pthread_mutex_lock(&inips);
  linha = inicio_pessoa[0];
  pthread_mutex_unlock(&inips);
  
  pthread_mutex_lock(&mlock[linha][coluna]);
  
  if (valido(linha,coluna)){
    
    shop[linha][coluna] = 'P';
    pthread_mutex_lock(&inips);
    inicio_pessoa[0] +=1 
    pthread_mutex_unlock(&inips);
    
    return 0;
  } else {
    
  }
  inicio_pessoa[0] += 1;
  
  
}

// pega proximo lock
// int move_pessoa(){

// }

// int* inicio_carro(){

// }
//insere caractere que não apague os limitadores
int atualiza_shop(int linha,int coluna,char dado){
  //mutex lock
  if(valido(linha,coluna)){
    shop[linha][coluna] = dado;
    return 0;
  } else {
    return 1;
  }
  //mutex unlock
}

//printa o shop
void imprime_shop(){
  int i,j;
  for (i = 0; i < LINHAS; ++i)   {
    for (j = 0; j < COLUNAS; ++j){
      printf("%c",shop[i][j]);        
    }
  }
  printf("\n");
  fflush(stdout);
  sleep(1);
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
