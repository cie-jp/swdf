/*****************************************************************
 *
 * 複素行列の2重対角化の検証プログラム
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

#define row (8)
#define col (6) //現在はrow >= colにしか対応していない. 

int main(void){
  COMP   A[row][col];
  COMP   B[row][col];
  COMP   x[row];
  COMP   y[col];
  COMP   wu[row];
  COMP   wv[col];
  RANDOM rnd;
  INT4   i,j,l;
  COMP   U[row][row],V[col][col],R[row][col],Q[row][col],T[row][col];
  
  RANDOM__INITIALIZE(&rnd);

  for(i = 0;i < row;i++){
    for(j = 0;j < col;j++){
      A[i][j] = COMPLEX__MAKE_RE_IM(RANDOM__NORMAL(&rnd,0.0,1.0),RANDOM__NORMAL(&rnd,0.0,1.0));
      B[i][j] = A[i][j];
      T[i][j] = A[i][j];
    }
  }

  COMP__MATRIX_PRINT(&A[0][0],row,col,stderr);

  COMP__MATRIX_BIDIAGONALIZATION(&B[0][0],wu,wv,row,col);

  for(l = 0;l < 5;l++){
    
    for(i = 0;i < row;i++){
      for(j = 0;j < row;j++){
        U[i][j] = (i == j) ? COMP__ONE() : COMP__ZERO();
      }
    }
    for(i = 0;i < row;i++){
      x[i] = COMP__ZERO();
    }
    for(i = l;i < row;i++){
      x[i] = B[i][l];
    }
    for(i = 0;i < row;i++){
      for(j = 0;j < row;j++){
        U[i][j] = COMP__SUB(U[i][j],COMP__MUL(COMP__ADD(COMP__ONE(),wu[l]),COMP__MUL(x[i],COMP__CONJ(x[j]))));
      }
    }

    COMP__MATRIX_MUL(&R[0][0],&U[0][0],row,row,&T[0][0],row,col);
    COMP__MATRIX_PRINT(&R[0][0],row,col,stderr);
    
    for(i = 0;i < col;i++){
      for(j = 0;j < col;j++){
        V[i][j] = (i == j) ? COMP__ONE() : COMP__ZERO();
      }
    }
    for(j = 0;j < col;j++){
      y[j] = COMP__ZERO();
    }
    for(j = (l + 1);j < col;j++){
      y[j] = COMP__CONJ(B[l][j]);
    }
    for(i = 0;i < col;i++){
      for(j = 0;j < col;j++){
        V[i][j] = COMP__SUB(V[i][j],COMP__MUL(COMP__ADD(COMP__ONE(),wv[l]),COMP__MUL(y[i],COMP__CONJ(y[j]))));
      }
    }
    
    COMP__MATRIX_MUL(&Q[0][0],&R[0][0],row,col,&V[0][0],col,col);
    COMP__MATRIX_PRINT(&Q[0][0],row,col,stderr);
    
    for(i = 0;i < row;i++){
      for(j = 0;j < col;j++){
        T[i][j] = Q[i][j];
      }
    }

  }

  COMP__MATRIX_PRINT(&B[0][0],row,col,stderr);

  return 0;
}
