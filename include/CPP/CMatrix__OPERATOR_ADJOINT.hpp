// *************************************************
// 随伴演算子
// *************************************************
CMatrix  operator ~(const CMatrix &A){
  CMatrix C(A.col,A.row);
  INT     i,j;
  
  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = COMP__CONJ(A.dat[j * A.col + i]);
    }
  }
  return C;
}
