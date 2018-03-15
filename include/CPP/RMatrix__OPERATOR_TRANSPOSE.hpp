// *************************************************
// 転置演算子
// *************************************************
RMatrix  operator ~(const RMatrix &A){
  RMatrix C(A.col,A.row);
  INT     i,j;
  
  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = A.dat[j * A.col + i];
    }
  }
  return C;
}
