/***************************************************************** 
 *
 * 2重対角化
 *
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/

#include"common.h"

void T__MATRIX_BIDIAGONALIZATION(TYPE A[],
                                 TYPE wu[],//[row]
                                 TYPE wv[],//[col]
                                 INT  row,
                                 INT  col){
  void *mem;
  TYPE *B;//[row * col]
  TYPE *u;//[row *   1]
  TYPE *v;//[1   * col]
  TYPE  w;
  TYPE  y0;
  REAL  len;
  TYPE  tmp;
  int   i,j,c;
  
  if((mem = malloc(sizeof(TYPE) * row * col + sizeof(TYPE) * row * 1 + sizeof(TYPE) * 1 * col)) == NULL){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);    
  }

  B = (TYPE*)mem;  
  u = (TYPE*)&B[row * col];
  v = (TYPE*)&u[row *   1];

  for(i = 0;i < row;i++){
    for(j = 0;j < col;j++){
      B[i * col + j] = T__ZERO();
    }
  }

  for(i = 0;i < row;i++){
    u[i] = T__ZERO();
  }

  for(j = 0;j < col;j++){
    v[j] = T__ZERO();
  }
  
  for(c = 0;c < col;c++){
    // ****************************************************************
    // 対象となる列ベクトルuの取得
    // ****************************************************************
    for(i = c;i < row;i++){
      u[i] = A[i * col + c];
    }
    // ****************************************************************
    // ノルムの計算
    // ****************************************************************
    len = REAL__ZERO();
    for(i = c;i < row;i++){
      len = REAL__ADD(len,T__NORM(u[i]));
    }
    if(REAL__NEQ(len,REAL__ZERO())){
      len = REAL__SQRT(len);
      if(REAL__GE(T__REAL(u[c]),REAL__ZERO())){
        y0 = T__NEGATIVE(T__MAKE(len));
      }else{
        y0 = T__POSITIVE(T__MAKE(len));
      }
      w   = T__DIV(T__CONJ(T__SUB(y0,u[c])),T__SUB(y0,u[c]));
      tmp = T__MAKE(REAL__SQRT(REAL__DIV(REAL__ONE(),REAL__MUL(REAL__TWO(),T__REAL(T__MUL(T__CONJ(y0),T__SUB(y0,u[c])))))));
      B[c * col + c] =             y0 ;
      u[c]           = T__SUB(u[c],y0);
      wu[c] = w;
      // ****************************************************************
      // 規格化処理
      // ****************************************************************
      for(i = c;i < row;i++){
        u[i] = T__MUL(u[i],tmp);
      }
      // ****************************************************************
      // v = A'uの計算
      // ****************************************************************
      for(j = c + 1;j < col;j++){
        tmp = T__ZERO();
        for(i = c;i < row;i++){
          tmp = T__FMA(T__CONJ(A[i * col + j]),u[i],tmp);
        }
        v[j] = tmp;
      }
      // ****************************************************************
      // A = A - (1 + w)uv'
      // ****************************************************************
      for(i = c;i < row;i++){
        for(j = c + 1;j < col;j++){
          A[i * col + j] = T__FMA(T__MUL(T__NEGATIVE(T__ADD(T__ONE(),w)),u[i]),T__CONJ(v[j]),A[i * col + j]);
        }
      }
      // ****************************************************************
      // uの代入
      // ****************************************************************
      for(i = c;i < row;i++){
        A[i * col + c] = u[i];
      }
    }
    if((c + 1) >= col){
      break;
    }

    // ****************************************************************
    // 対象となる行ベクトルvの取得
    // ****************************************************************
    for(j = c + 1;j < col;j++){
      v[j] = T__CONJ(A[c * col + j]);
    }
    // ****************************************************************
    // ノルムの計算
    // ****************************************************************
    len = 0.0;
    for(j = c + 1;j < col;j++){
      len = REAL__ADD(len,T__NORM(v[j]));
    }
    if(REAL__EQ(len,REAL__ZERO())){
      B[c * col + (c + 1)] = T__ZERO();
    }else{
      len = REAL__SQRT(len);
      if(REAL__GE(T__REAL(v[c + 1]),REAL__ZERO())){
        y0 = T__NEGATIVE(T__MAKE(len));
      }else{
        y0 = T__POSITIVE(T__MAKE(len));
      }
      w   = T__CONJ(T__DIV(T__CONJ(T__SUB(y0,v[c + 1])),T__SUB(y0,v[c + 1])));
      tmp = T__MAKE(REAL__SQRT(REAL__DIV(REAL__ONE(),REAL__MUL(REAL__TWO(),T__REAL(T__MUL(T__CONJ(y0),T__SUB(y0,v[c + 1])))))));
      B[c * col + (c + 1)] =                 y0 ;
      v[c + 1]             = T__SUB(v[c + 1],y0);

      wv[c] = w;
      // ****************************************************************
      // 規格化処理
      // ****************************************************************
      for(j = c + 1;j < col;j++){
        v[j] = T__MUL(v[j],tmp);
      }
      // ****************************************************************
      // u = Avの計算
      // ****************************************************************
      for(i = c + 1;i < row;i++){
        tmp = T__ZERO();
        for(j = c + 1;j < col;j++){
          tmp = T__FMA(A[i * col + j],v[j],tmp);
        }
        u[i] = tmp;
      }
      // ****************************************************************
      //A = A - (1 + w)uv'
      // ****************************************************************
      for(i = c + 1;i < row;i++){
        for(j = c + 1;j < col;j++){
          A[i * col + j] = T__FMA(T__MUL(T__NEGATIVE(T__ADD(T__ONE(),w)),u[i]),T__CONJ(v[j]),A[i * col + j]);
        }
      }
      // ****************************************************************
      // vの代入
      // ****************************************************************
      for(j = c + 1;j < col;j++){
        A[c * col + j] = T__CONJ(v[j]);
      }
    }
  }
  
  free(mem);  
}
