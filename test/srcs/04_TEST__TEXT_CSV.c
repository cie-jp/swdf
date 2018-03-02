/*****************************************************************
 *
 * CSVファイルを読み込む. 
 * 
 *
 *                           Created  by Mamoru Ota (2018/01/25)
 * 
 *****************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"TEXT_CSV.h"

int main(int argc,const char *argv[]){
  TEXT_CSV csv;
  INT4     n;
  FILE    *fp;

  if((fp = fopen("./test/dat/mrr_cross_section_raindrop_beard_and_chuang.txt","r")) == NULL){
    return EXIT_FAILURE;
  }
  while(TEXT_CSV__READ_LINE(&csv,fp," ","#") == 0){
    for(n = 0;n < csv.num;n++){
      printf("%e\t",atof(TEXT_CSV__GET_DATA(&csv,n)));
    }    
    printf("\n");
  }

  printf("NUM_ROWS = %ld\n",TEXT_CSV__GET_NUM_ROWS(fp,"#"));

  fclose(fp);

  return EXIT_SUCCESS;
}
