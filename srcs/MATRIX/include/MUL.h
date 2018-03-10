/***************************************************************** 
 *
 * 行列の乗算
 *
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/

#include"common.h"

void T__MATRIX_MUL(TYPE  C[],  //(out) [Arow * Bcol] (Crow = Arow, Ccol = Bcol)
                   TYPE  A[],  //(in)  [Arow * Acol]
                   INT   Arow, //(in)
                   INT   Acol, //(in)
                   TYPE  B[],  //(in)  [Brow * Bcol]
                   INT   Brow, //(in)
                   INT   Bcol){//(in)                   
  INT  i,j,k;
  TYPE tmp;
  INT  Crow;
  INT  Ccol;

  if(Acol != Brow){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  
  Crow = Arow;
  Ccol = Bcol;
  
  for(i = 0;i < Crow;i++){
    for(j = 0;j < Ccol;j++){
      tmp = T__ZERO;
      for(k = 0;k < Acol;k++){
        tmp = T__FMA(A[i * Acol + k],B[k * Bcol + j],tmp);
      }
      C[i * Ccol + j] = tmp;
    }
  }
}
