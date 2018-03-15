/*****************************************************************
 *
 * 複素行列の特異値分解(ランク落ち)の検証プログラム
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

#define row (6)
#define col (10)

#define dim ((row < col) ? row : col)

int main(void){
  COMP   A[row][col],B[row][col];
  REAL   s[dim];
  COMP   U[row][dim];
  COMP   V[col][dim];
  COMP   S[dim][dim];
  RANDOM rnd;
  INT4   i,j;
  COMP   Ua  [dim][row];
  COMP   Va  [dim][col];
  COMP   US  [row][dim];
  COMP   USVa[row][col];
  COMP   UaU [dim][dim];
  COMP   VaV [dim][dim];
  
  RANDOM__INITIALIZE(&rnd);

  for(i = 0;i < row;i++){
    for(j = 0;j < col;j++){      
      A[i][j] = COMPLEX__MAKE_RE_IM(RANDOM__NORMAL(&rnd,0.0,1.0),RANDOM__NORMAL(&rnd,0.0,1.0));
    }
  }
  
  COMP__MATRIX_SVD(s,&U[0][0],&V[0][0],&A[0][0],row,col);
  
  for(i = 0;i < dim;i++){
    for(j = 0;j < dim;j++){
      S[i][j] = COMP__ZERO();
    }
  }
  for(i = 0;i < dim;i++){
    S[i][i] = COMP__MAKE(s[i]);
  }
  //S[0][0] = COMPLEX__MAKE_RE_IM(3.0,0.0);
  S[1][1] = COMP__ZERO();
  //S[2][2] = COMPLEX__MAKE_RE_IM(3.0,0.0); 
  S[3][3] = COMP__ZERO();

  for(i = 0;i < dim;i++){
    for(j = 0;j < col;j++){
      Va[i][j] = COMP__CONJ(V[j][i]);
    }
  }

  for(i = 0;i < dim;i++){
    for(j = 0;j < row;j++){
      Ua[i][j] = COMP__CONJ(U[j][i]);
    }
  }

  // =================
  COMP__MATRIX_MUL(&US  [0][0],&U [0][0],row,dim,&S [0][0],dim,dim);
  COMP__MATRIX_MUL(&USVa[0][0],&US[0][0],row,dim,&Va[0][0],dim,col);

  for(i = 0;i < row;i++){
    for(j = 0;j < col;j++){      
      A[i][j] = USVa[i][j];
    }
  }

  COMP__MATRIX_SVD(s,&U[0][0],&V[0][0],&A[0][0],row,col);

  for(i = 0;i < dim;i++){
    for(j = 0;j < dim;j++){
      S[i][j] = COMP__ZERO();
    }
  }
  for(i = 0;i < dim;i++){
    S[i][i] = COMP__MAKE(s[i]);
  }


  for(i = 0;i < dim;i++){
    for(j = 0;j < col;j++){
      Va[i][j] = COMP__CONJ(V[j][i]);
    }
  }

  for(i = 0;i < dim;i++){
    for(j = 0;j < row;j++){
      Ua[i][j] = COMP__CONJ(U[j][i]);
    }
  }
  
  COMP__MATRIX_MUL(&US  [0][0],&U [0][0],row,dim,&S [0][0],dim,dim);
  COMP__MATRIX_MUL(&USVa[0][0],&US[0][0],row,dim,&Va[0][0],dim,col);

  fprintf(stderr,"============ A         ============\n");
  COMP__MATRIX_PRINT(&A   [0][0],row,col,stderr);
  fprintf(stderr,"============ USV^{dag} ============\n");
  COMP__MATRIX_PRINT(&USVa[0][0],row,col,stderr);

  fprintf(stderr,"============ U^{dag}U ============\n");
  COMP__MATRIX_MUL(&UaU[0][0],&Ua[0][0],dim,row,&U[0][0],row,dim);
  COMP__MATRIX_PRINT(&UaU[0][0],dim,dim,stderr);

  fprintf(stderr,"============ V^{dag}V ============\n");
  COMP__MATRIX_MUL(&VaV[0][0],&Va[0][0],dim,col,&V[0][0],col,dim);
  COMP__MATRIX_PRINT(&VaV[0][0],dim,dim,stderr);

  fprintf(stderr,"============ US ============\n");
  COMP__MATRIX_PRINT(&US[0][0],row,dim,stderr);

  fprintf(stderr,"============ V^{dag} ============\n");
  COMP__MATRIX_PRINT(&Va[0][0],dim,col,stderr);

  fprintf(stderr,"============ S ============\n");
  COMP__MATRIX_PRINT(&S[0][0],dim,dim,stderr);
  fprintf(stderr,"============ U ============\n");
  COMP__MATRIX_PRINT(&U[0][0],row,dim,stderr);
  fprintf(stderr,"============ V ============\n");
  COMP__MATRIX_PRINT(&V[0][0],col,dim,stderr);

  fprintf(stderr,"============ USV^{dag} ============\n");
  COMP__MATRIX_PRINT(&USVa[0][0],row,col,stderr);
  
  for(i = 0;i < dim;i++){
    printf("%f\n",s[i]);
  }
  
  return 0;
}
