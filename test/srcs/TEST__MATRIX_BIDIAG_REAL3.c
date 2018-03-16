/*****************************************************************
 *
 * 実行列の2重対角化の検証プログラム
 * 
 *
 *                           Created  by Mamoru Ota (2018/03/05)
 * 
 *****************************************************************/

//1-1: B[0][0]
//1-2: B[0][1]
//2-1: B[1][1]
//2-2: B[1][2]
//3-1: B[2][2]
//3-2: B[2][3]
//...

//3行3列
//1-1: B[0][0]
//1-2: B[0][1]
//2-1: B[1][1]
//2-2: B[1][2]
//3-1: B[2][2]

//4行4列
//1-1: B[0][0]
//1-2: B[0][1]
//2-1: B[1][1]
//2-2: B[1][2]
//3-1: B[2][2]
//3-2: B[2][3]
//4-1: B[3][3]

//5行3列
//1-1: B[0][0]
//1-2: B[0][1]
//2-1: B[1][1]
//2-2: B[1][2]
//3-1: B[2][2]

//3行5列
//1-1: B[0][0]
//1-2: B[0][1]
//2-1: B[1][1]
//2-2: B[1][2]
//3-1: B[2][2]
//3-2: B[2][3]

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"MATRIX.h"
#include"RANDOM.h"

#define row (8)
#define col (4) //現在はrow >= colにしか対応していない. 

int main(void){
  REAL   A[row][col];
  REAL   B[row][col];
  REAL   wu[row];
  REAL   wv[row];
  REAL   x[row];
  REAL   y[col];
  RANDOM rnd;
  INT4   i,j,l;
  REAL   U[row][row],V[col][col],R[row][col],Q[row][col],T[row][col];

  RANDOM__INITIALIZE(&rnd);

  for(i = 0;i < row;i++){
    for(j = 0;j < col;j++){
      A[i][j] = RANDOM__NORMAL(&rnd,0.0,1.0);
      B[i][j] = A[i][j];
      T[i][j] = A[i][j];
    }
  }

  REAL__MATRIX_PRINT(&A[0][0],row,col,stderr);

  REAL__MATRIX_BIDIAGONALIZATION(&B[0][0],wu,wv,row,col);

  for(l = 0;l < 3;l++){
    
    for(i = 0;i < row;i++){
      for(j = 0;j < row;j++){
        U[i][j] = (i == j) ? REAL__ONE() : REAL__ZERO();
      }
    }
    for(i = 0;i < row;i++){
      x[i] = REAL__ZERO();
    }
    for(i = l;i < row;i++){
      x[i] = B[i][l];
    }
    for(i = 0;i < row;i++){
      for(j = 0;j < row;j++){
        U[i][j] = REAL__SUB(U[i][j],REAL__MUL(REAL__TWO(),REAL__MUL(x[i],x[j])));
      }
    }

    REAL__MATRIX_MUL(&R[0][0],&U[0][0],row,row,&T[0][0],row,col);
    REAL__MATRIX_PRINT(&R[0][0],row,col,stderr);
    
    for(i = 0;i < col;i++){
      for(j = 0;j < col;j++){
        V[i][j] = (i == j) ? REAL__ONE() : REAL__ZERO();
      }
    }
    for(j = 0;j < col;j++){
      y[j] = REAL__ZERO();
    }
    for(j = (l + 1);j < col;j++){
      y[j] = B[l][j];
    }
    for(i = 0;i < col;i++){
      for(j = 0;j < col;j++){
        V[i][j] = REAL__SUB(V[i][j],REAL__MUL(REAL__TWO(),REAL__MUL(y[i],y[j])));
      }
    }
    
    REAL__MATRIX_MUL(&Q[0][0],&R[0][0],row,col,&V[0][0],col,col);
    REAL__MATRIX_PRINT(&Q[0][0],row,col,stderr);
    
    for(i = 0;i < row;i++){
      for(j = 0;j < col;j++){
        T[i][j] = Q[i][j];
      }
    }

  }

  REAL__MATRIX_PRINT(&B[0][0],row,col,stderr);

  return 0;
}
