/***************************************************************** 
 *
 * 行列の表示
 *
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/

#include"common.h"

void T__MATRIX_PRINT(TYPE  A[], //(in) [row * col]
                     INT   row, //(in)
                     INT   col, //(in)
                     FILE *fp){
  INT   i,j;

  for(i = 0;i < row;i++){
    for(j = 0;j < col;j++){
      T__PRINT(A[i * col + j],fp);
      fprintf(fp," ");
    }
    fprintf(fp,"\n");
  }
  fprintf(fp,"\n");
}
