/*****************************************************************
 *
 * 複素行列の特異値分解の検証プログラム
 * 
 *
 *                           Created  by Mamoru Ota (2018/03/05)
 * 
 *****************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"MATRIX.h"
#include"RANDOM.h"

#define row (5)
#define col (5)

#define dim ((row < col) ? row : col)

int main(void){
  REAL   A[row][col];
  REAL   s[dim];
  REAL   U[row][dim];
  REAL   V[col][dim];
  REAL   S[dim][dim];
  RANDOM rnd;
  INT4   i,j;
  REAL   Ua  [dim][row];
  REAL   Va  [dim][col];
  REAL   US  [row][dim];
  REAL   USVa[row][col];
  REAL   UaU [dim][dim];
  REAL   VaV [dim][dim];
  
  RANDOM__INITIALIZE(&rnd);

  for(i = 0;i < row;i++){
    for(j = 0;j < col;j++){      
      A[i][j] = RANDOM__NORMAL(&rnd,0.0,1.0);
    }
  }

  REAL__MATRIX_SVD(s,&U[0][0],&V[0][0],&A[0][0],row,col);
  
  for(i = 0;i < dim;i++){
    for(j = 0;j < dim;j++){
      S[i][j] = REAL__ZERO();
    }
  }
  for(i = 0;i < dim;i++){
    S[i][i] = REAL__MAKE(s[i]);
  }

  for(i = 0;i < dim;i++){
    for(j = 0;j < col;j++){
      Va[i][j] = REAL__CONJ(V[j][i]);
    }
  }

  for(i = 0;i < dim;i++){
    for(j = 0;j < row;j++){
      Ua[i][j] = REAL__CONJ(U[j][i]);
    }
  }

  REAL__MATRIX_MUL(&US  [0][0],&U [0][0],row,dim,&S [0][0],dim,dim);
  REAL__MATRIX_MUL(&USVa[0][0],&US[0][0],row,dim,&Va[0][0],dim,col);
  
  REAL__MATRIX_PRINT(&A   [0][0],row,col,stderr);
  REAL__MATRIX_PRINT(&USVa[0][0],row,col,stderr);

  fprintf(stderr,"============ U^{dag}U ============\n");
  REAL__MATRIX_MUL(&UaU[0][0],&Ua[0][0],dim,row,&U[0][0],row,dim);
  REAL__MATRIX_PRINT(&UaU[0][0],dim,dim,stderr);

  fprintf(stderr,"============ V^{dag}V ============\n");
  REAL__MATRIX_MUL(&VaV[0][0],&Va[0][0],dim,col,&V[0][0],col,dim);
  REAL__MATRIX_PRINT(&VaV[0][0],dim,dim,stderr);

  fprintf(stderr,"============ U ============\n");
  REAL__MATRIX_PRINT(&U[0][0],row,dim,stderr);
  fprintf(stderr,"============ V ============\n");
  REAL__MATRIX_PRINT(&V[0][0],col,dim,stderr);

  for(i = 0;i < dim;i++){
    printf("%f\n",s[i]);
  }
  
  return 0;
}
