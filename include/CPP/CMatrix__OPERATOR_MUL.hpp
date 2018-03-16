// *************************************************
// 乗算演算子(行列 * 行列)
// *************************************************
CMatrix  operator *(const CMatrix &A,const CMatrix &B){
  CMatrix C(A.row,B.col);
  COMP    tmp;
  INT     i,j,k;
  
  if(A.col != B.row){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  
  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      tmp = COMP__ZERO();
      for(k = 0;k < A.col;k++){
        tmp = COMP__FMA(A.dat[i * A.col + k],B.dat[k * B.col + j],tmp);
      }
      C.dat[i * C.col + j] = tmp;
    }
  }
  return C;
}

// *************************************************
// 乗算演算子(  数 * 行列)
// *************************************************
CMatrix  operator *(const COMP     a,const CMatrix &B){
  CMatrix C = B;
  INT     i,j;

  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = COMP__MUL(a,C.dat[i * C.col + j]);
    }
  }
  return C;
}

// *************************************************
// 乗算演算子(行列 *   数)
// *************************************************
CMatrix  operator *(const CMatrix &A,const COMP     b){
  CMatrix C = A;
  INT     i,j;

  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = COMP__MUL(C.dat[i * C.col + j],b);
    }
  }
  return C;
}

// *************************************************
// 乗算演算子(行列 % 行列) (要素ごとの乗算)
// *************************************************
CMatrix  operator %(const CMatrix &A,const CMatrix &B){
  CMatrix C = A;
  INT     i,j;
  
  if(A.row != B.row || A.col != B.col){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  
  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = COMP__MUL(C.dat[i * C.col + j],B.dat[i * B.col + j]);
    }
  }
  return C;
}
