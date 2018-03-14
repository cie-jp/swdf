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

void SVD(REAL s[],
         COMP U[],//[row * row]
         COMP V[],//[col * col]
         COMP A[],//[row * col]
         INT  row,
         INT  col){
  INT   dim;//min(row,col)
  void *mem;
  COMP *P;  //[row * col]
  REAL *b0; //[dim]
  REAL *b1; //[dim - 1]
  REAL *U0; //[dim * dim]
  REAL *V0; //[dim * dim]
  INT   i,j;
  
  dim = (row < col) ? row : col;

  // ******************************************************************
  //  1. 作業変数のメモリ確保
  // ******************************************************************
  if((mem = malloc(sizeof(COMP) *  row * col
                 + sizeof(REAL) *  dim * dim
                 + sizeof(REAL) *  dim * dim                   
                 + sizeof(REAL) *  dim
                 + sizeof(REAL) * (dim - 1))) == NULL){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }

  // ******************************************************************
  //  2. メモリ割り当て
  // ******************************************************************
  P  = (COMP*)mem;
  b0 = (REAL*)&P [row * col];
  b1 = (REAL*)&b0[dim];
  U0 = (REAL*)&b1[dim];
  V0 = (REAL*)&U0[dim * dim];

  // ******************************************************************
  //  3. データコピー
  // ******************************************************************
  for(i = 0;i < row;i++){
    for(j = 0;j < col;j++){
      P[i * col + j] = A[i * col + j];
    }
  }

  // ******************************************************************
  //  4. 2重対角化
  // ******************************************************************
  //COMP__MATRIX_BIDIAG(b0,b1,wu,wv,P,row,col);

  // ******************************************************************
  //  5. 2重対角行列の特異値分解
  // ******************************************************************
  REAL__MATRIX_SVD_BI(s,U0,V0,b0,b1,dim);

  // ******************************************************************
  //  6. 左特異ベクトルの計算
  // ******************************************************************
  /*for(i = 0;i < row;i++){
    x[i] = COMP__ZERO();
  }
  for(i = l;i < row;i++){
    x[i] = B[i][l];
  }
  for(i = 0;i < row;i++){
    for(j = 0;j < row;j++){
      U[i][j] = COMP__SUB(U[i][j],COMP__MUL(COMP__ADD(COMP__ONE(),wu[l]),COMP__MUL(x[i],COMP__CONJ(x[j]))));
    }
    }*/

  // ******************************************************************
  //  7. 右特異ベクトルの計算
  // ******************************************************************
  /*for(j = 0;j < col;j++){
    y[j] = COMP__ZERO();
  }
  for(j = (l + 1);j < col;j++){
    y[j] = COMP__CONJ(B[l][j]);
  }
  for(i = 0;i < col;i++){
    for(j = 0;j < col;j++){
      V[i][j] = COMP__SUB(V[i][j],COMP__MUL(COMP__ADD(COMP__ONE(),wv[l]),COMP__MUL(y[i],COMP__CONJ(y[j]))));
    }
    }*/

  // ******************************************************************
  //  6. 作業変数のメモリ解放
  // ******************************************************************
  free(mem);
}



#define row (8)
#define col (6) //現在はrow >= colにしか対応していない. 
#define dim ((row < col) ? row : col)

int main(void){
  COMP   A[row][col];
  REAL   s[dim];
  COMP   U[row][dim];
  COMP   V[col][dim];
  COMP   S[dim][dim];
  RANDOM rnd;
  INT4   i,j;
  COMP   Va[dim][col],US[row][dim],USVa[row][col];
  
  RANDOM__INITIALIZE(&rnd);

  for(i = 0;i < row;i++){
    for(j = 0;j < col;j++){
      A[i][j] = COMPLEX__MAKE_RE_IM(RANDOM__NORMAL(&rnd,0.0,1.0),RANDOM__NORMAL(&rnd,0.0,1.0));
    }
  }

  //SVD(s,&U[0][0],&V[0][0],&A[0][0],row,col);
  
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
      Va[i][j] = V[j][i];
    }
  }

  COMP__MATRIX_MUL(&US  [0][0],&U [0][0],row,dim,&S [0][0],dim,dim);
  COMP__MATRIX_MUL(&USVa[0][0],&US[0][0],row,dim,&Va[0][0],dim,col);
  
  COMP__MATRIX_PRINT(&A   [0][0],row,col,stderr);
  COMP__MATRIX_PRINT(&USVa[0][0],row,col,stderr);

  return 0;
}
