/***************************************************************** 
 *
 * 特異値分解
 *
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/

#include"common.h"

// **********************************************************
// row行col列の実・複素行列Aに対して特異値分解を行う.
//
// A       = U diag(s) V^{dag} 
//
// A[i][j] = sum _k s[k]U[i][k]conj(V[j][k]) (成分表示)
//
// U^{dag} U = I_{dim}, V^{dag} V = I_{dim} 
//
// dim = min(row,col)
//
// s[0] > s[1] > ... s[dim - 1] > 0
//
// (注) row >= colの場合のみに適用可能
//
// **********************************************************
void T__MATRIX_SVD_BASE(REAL s[], //(out)[col]       : 特異値配列
                        TYPE U[], //(out)[row * col] : 左特異ベクトル群
                        TYPE V[], //(out)[col * col] : 右特異ベクトル群
                        TYPE A[], //(in) [row * col] : 特異値分解の対象とする行列
                        INT  row, //(in)             : 行列の行数
                        INT  col){//(in)             : 行列の列数
  void *mem;
  TYPE *P;  //[row * col]
  REAL *b0; //[col]
  REAL *b1; //[col - 1]
  TYPE *wu; //[col]
  TYPE *wv; //[col - 1]
  REAL *U0; //[col * col]
  REAL *V0; //[col * col]
  TYPE *x;  //[row]
  TYPE *y;  //[col]
  TYPE  tmp;
  INT   i,j,l;

  if(row < col){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  
  // ******************************************************************
  //  1. 作業変数のメモリ確保
  // ******************************************************************
  if((mem = malloc(sizeof(TYPE) *  row * col
                 + sizeof(REAL) *  col
                 + sizeof(REAL) * (col - 1)
                 + sizeof(TYPE) *  col
                 + sizeof(TYPE) * (col - 1)                   
                 + sizeof(REAL) *  col * col
                 + sizeof(REAL) *  col * col
                 + sizeof(TYPE) *  row
                 + sizeof(TYPE) *  col)) == NULL){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }

  // ******************************************************************
  //  2. メモリ割り当て
  // ******************************************************************
  P  = (TYPE*)mem;
  b0 = (REAL*)&P [row * col];
  b1 = (REAL*)&b0[col];
  wu = (TYPE*)&b1[col - 1];
  wv = (TYPE*)&wu[col];
  U0 = (REAL*)&wv[col - 1];
  V0 = (REAL*)&U0[col * col];
  x  = (TYPE*)&V0[col * col];
  y  = (TYPE*)&x [row];

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
  T__MATRIX_BIDIAG(b0,b1,wu,wv,P,row,col);

  // ******************************************************************
  //  5. 2重対角行列の特異値分解
  // ******************************************************************
  REAL__MATRIX_SVD_BI(s,U0,V0,b0,b1,col);

  // ******************************************************************
  //  6. 左特異ベクトルの計算
  // ******************************************************************
  for(j = 0;j < col;j++){
    for(i =   0;i < col;i++){
      U[i * col + j] = T__MAKE(U0[i * col + j]);
    }
    for(i = col;i < row;i++){
      U[i * col + j] = T__ZERO(); 
    }
  }  
  for(l = col - 1;l >= 0;l--){
    for(i = 0;i <   l;i++){
      x[i] = T__ZERO();
    }
    for(i = l;i < row;i++){
      x[i] = P[i * col + l];
    }
    for(j = 0;j < col;j++){
      tmp = T__ZERO();
      for(i = 0;i < row;i++){
        tmp = T__FMA(T__CONJ(x[i]),U[i * col + j],tmp);
      }
      tmp = T__MUL(T__ADD(T__ONE(),T__CONJ(wu[l])),tmp);
      for(i = 0;i < row;i++){
        U[i * col + j] = T__SUB(U[i * col + j],T__MUL(tmp,x[i]));
      }
    }
  }  

  // ******************************************************************
  //  7. 右特異ベクトルの計算
  // ******************************************************************
  for(j = 0;j < col;j++){
    for(i = 0;i < col;i++){
      V[i * col + j] = T__MAKE(V0[i * col + j]);
    }
  }
  for(l = col - 2;l >= 0;l--){
    for(j =      0 ;j < (l + 1);j++){
      y[j] = T__ZERO();
    }
    for(j = (l + 1);j <    col ;j++){
      y[j] = T__CONJ(P[l * col + j]);
    }
    for(j = 0;j < col;j++){
      tmp = T__ZERO();
      for(i = 0;i < col;i++){
        tmp = T__FMA(T__CONJ(y[i]),V[i * col + j],tmp);
      }
      tmp = T__MUL(T__ADD(T__ONE(),wv[l]),tmp);
      for(i = 0;i < col;i++){
        V[i * col + j] = T__SUB(V[i * col + j],T__MUL(tmp,y[i]));
      }
    }
  }
  
  // ******************************************************************
  //  6. 作業変数のメモリ解放
  // ******************************************************************
  free(mem);
}

// **********************************************************
// row行col列の実・複素行列Aに対して特異値分解を行う.
//
// A       = U diag(s) V^{dag} 
//
// A[i][j] = sum _k s[k]U[i][k]conj(V[j][k]) (成分表示)
//
// U^{dag} U = I_{dim}, V^{dag} V = I_{dim} 
//
// dim = min(row,col)
//
// s[0] > s[1] > ... s[dim - 1] > 0
// **********************************************************
void T__MATRIX_SVD(REAL s[], //(out)[dim]       : 特異値配列
                   TYPE U[], //(out)[row * dim] : 左特異ベクトル群
                   TYPE V[], //(out)[col * dim] : 右特異ベクトル群
                   TYPE A[], //(in) [row * col] : 特異値分解の対象とする行列
                   INT  row, //(in)             : 行列の行数
                   INT  col){//(in)             : 行列の列数
  void *mem;
  TYPE *tA; //[col * row]
  INT   i,j;
  
  if(row >= col){
    T__MATRIX_SVD_BASE(s,U,V,A,row,col);
    return;
  }

  // ******************************************************************
  //  1. 作業変数のメモリ確保
  // ******************************************************************
  if((mem = malloc(sizeof(TYPE) * col * row)) == NULL){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }

  // ******************************************************************
  //  2. メモリ割り当て
  // ******************************************************************
  tA = (TYPE*)mem;

  // ******************************************************************
  //  3. 随伴行列の計算
  // ******************************************************************
  for(i = 0;i < col;i++){
    for(j = 0;j < row;j++){
      tA[i * row + j] = T__CONJ(A[j * col + i]);
    }
  }

  // ******************************************************************
  //  4. 特異値分解
  // ******************************************************************
  T__MATRIX_SVD_BASE(s,V,U,tA,col,row);
  
  // ******************************************************************
  //  5. 作業変数のメモリ解放
  // ******************************************************************
  free(mem);
}