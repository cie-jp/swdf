// *************************************************
// 単項演算子(+)
// *************************************************
CMatrix  operator +(const CMatrix &A){
  return A;
}

// *************************************************
// 加算演算子(行列 + 行列)
// *************************************************
CMatrix  operator +(const CMatrix &A,const CMatrix &B){
  CMatrix C = A;
  INT     i,j;
  
  if(A.row != B.row || A.col != B.col){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  
  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = COMP__ADD(C.dat[i * C.col + j],B.dat[i * B.col + j]);
    }
  }
  return C;
}

// *************************************************
// 加算演算子(実数 + 行列)
// *************************************************
CMatrix  operator +(const COMP     a,const CMatrix &B){
  CMatrix C = B;
  INT     i,j;

  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = COMP__ADD(a,C.dat[i * C.col + j]);
    }
  }
  return C;
}

// *************************************************
// 加算演算子(行列 + 実数)
// *************************************************
CMatrix  operator +(const CMatrix &A,const COMP     b){
  CMatrix C = A;
  INT     i,j;

  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = COMP__ADD(C.dat[i * C.col + j],b);
    }
  }
  return C;
}
