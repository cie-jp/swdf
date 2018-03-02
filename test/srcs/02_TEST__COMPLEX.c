/*****************************************************************
 *
 * 複素数型のサイズ検証プログラム
 * 
 *
 *                           Created  by Mamoru Ota (2018/01/25)
 * 
 *****************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"COMPLEX.h"

int main(int argc,const char *argv[]){
  if(sizeof(COMPLEX) != 16){
    fprintf(stderr,"Data Type Validation : ERROR [%s]\n","COMPLEX");
    return EXIT_FAILURE;
  }
  fprintf(stdout,"Data Type Validation : OK\n");
  return EXIT_SUCCESS;
}
