// *************************************************
// 除算演算子(行列 / 実数)
// *************************************************
RMatrix  operator /(const RMatrix &A,const REAL     b){
  RMatrix C = A;
  INT     i,j;

  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = C.dat[i * C.col + j] / b;
    }
  }
  return C;
}

// *************************************************
// 除算演算子(行列 / 行列) (要素ごとの除算)
// *************************************************
RMatrix  operator /(const RMatrix &A,const RMatrix &B){
  RMatrix C = A;
  INT     i,j;
  
  if(A.row != B.row || A.col != B.col){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  
  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] /= B.dat[i * B.col + j];
    }
  }
  return C;
}
