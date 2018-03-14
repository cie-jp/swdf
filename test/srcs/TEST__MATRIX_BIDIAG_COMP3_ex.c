/*****************************************************************
 *
 * 複素行列の2重対角化の検証プログラム(ext.)
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

#define row (12)
#define col (8) //現在はrow >= colにしか対応していない. 

#define dim ((row < col) ? row : col)

int main(void){
  COMP   A[row][col];
  COMP   B[row][col];
  REAL   b0[col];
  REAL   b1[col];
  COMP   wu[col];
  COMP   wv[col - 1];
  COMP   u [row];
  COMP   v [col];
  RANDOM rnd;
  INT4   i,j,l;
  COMP   U[row][row],V[col][col],R[row][col],Q[row][col],T[row][col];
  
  RANDOM__INITIALIZE(&rnd);

  // 1. Aをランダムに初期化
  for(i = 0;i < row;i++){
    for(j = 0;j < col;j++){
      A[i][j] = COMPLEX__MAKE_RE_IM(RANDOM__NORMAL(&rnd,0.0,1.0),RANDOM__NORMAL(&rnd,0.0,1.0));
    }
  }

  // 2. B = A
  // 3. T = A
  for(i = 0;i < row;i++){
    for(j = 0;j < col;j++){
      B[i][j] = A[i][j];
      T[i][j] = A[i][j];
    }
  }

  // 4. Aを表示する
  COMP__MATRIX_PRINT(&A[0][0],row,col,stderr);

  //5. 2重対角化を行う
  COMP__MATRIX_BIDIAG(b0,b1,wu,wv,&B[0][0],row,col);

  for(l = 0;l < col;l++){
    
    //uの初期化
    for(i = 0;i < row;i++){
      u[i] = COMP__ZERO();
    }
    for(i = l;i < row;i++){
      u[i] = B[i][l];
    }
    //U = I - (1 + wu)uu^{dag}
    for(i = 0;i < row;i++){
      for(j = 0;j < row;j++){
        U[i][j] = (i == j) ? COMP__ONE() : COMP__ZERO();
      }
    }
    for(i = 0;i < row;i++){
      for(j = 0;j < row;j++){
        U[i][j] = COMP__SUB(U[i][j],COMP__MUL(COMP__ADD(COMP__ONE(),wu[l]),COMP__MUL(u[i],COMP__CONJ(u[j]))));
      }
    }
    //R = UT
    COMP__MATRIX_MUL(&R[0][0],&U[0][0],row,row,&T[0][0],row,col);
    //Rを表示する
    COMP__MATRIX_PRINT(&R[0][0],row,col,stderr);

    //vの初期化
    for(j = 0;j < col;j++){
      v[j] = COMP__ZERO();
    }
    for(j = (l + 1);j < col;j++){
      v[j] = COMP__CONJ(B[l][j]);
    }
    //V = I - (1 + wv)vv^{dag}
    for(i = 0;i < col;i++){
      for(j = 0;j < col;j++){
        V[i][j] = (i == j) ? COMP__ONE() : COMP__ZERO();
      }
    }
    if(l != (col - 1)){
      for(i = 0;i < col;i++){
        for(j = 0;j < col;j++){
          V[i][j] = COMP__SUB(V[i][j],COMP__MUL(COMP__ADD(COMP__ONE(),wv[l]),COMP__MUL(v[i],COMP__CONJ(v[j]))));
        }
      }
    }
    //Q = RV
    COMP__MATRIX_MUL(&Q[0][0],&R[0][0],row,col,&V[0][0],col,col);
    //Qを表示する Q = UTV , UとVによる線形変換結果を表示する. 
    COMP__MATRIX_PRINT(&Q[0][0],row,col,stderr);

    //T <= Q
    for(i = 0;i < row;i++){
      for(j = 0;j < col;j++){
        T[i][j] = Q[i][j];
      }
    }

  }

  COMP__MATRIX_PRINT(&B[0][0],row,col,stderr);

  for(i = 0;i < dim - 1;i++){
    printf("%f %f\n",b0[i],b1[i]);
  }
  printf("%f\n",b0[dim - 1]);

  return 0;
}
