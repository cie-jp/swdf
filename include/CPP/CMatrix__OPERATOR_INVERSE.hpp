// *************************************************
// 逆元演算子
// *************************************************
CMatrix  operator !(const CMatrix &A){
  CMatrix C = A;
  
  if(A.row != A.col){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }

  if(COMP__MATRIX_INV(C.dat,C.row) == -1){
    ERROR__SHOW("#2");
    exit(EXIT_FAILURE);
  }
  return C;
}

