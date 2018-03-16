// *************************************************
// 除算演算子(行列 /   数)
// *************************************************
CMatrix  operator /(const CMatrix &A,const COMP     b){
  CMatrix C = A;
  INT     i,j;

  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = COMP__DIV(C.dat[i * C.col + j],b);
    }
  }
  return C;
}

// *************************************************
// 除算演算子(行列 / 行列) (要素ごとの除算)
// *************************************************
CMatrix  operator /(const CMatrix &A,const CMatrix &B){
  CMatrix C = A;
  INT     i,j;
  
  if(A.row != B.row || A.col != B.col){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  
  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = COMP__DIV(C.dat[i * C.col + j],B.dat[i * B.col + j]);
    }
  }
  return C;
}
