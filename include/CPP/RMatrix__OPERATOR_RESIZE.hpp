// *************************************************
// 縦結合演算子
// *************************************************
RMatrix  operator &(const RMatrix &A,const RMatrix &B){
  RMatrix C(A.row + B.row,A.col);
  INT     i,j;
  
  if(A.col != B.col){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }

  for(i = 0;i < A.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[ i          * C.col + j] = A.dat[i * A.col + j];
    }
  }

  for(i = 0;i < B.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[(i + A.row) * C.col + j] = B.dat[i * B.col + j];
    }
  }
  return C;
}

// *************************************************
// i0行を抜き出す演算子
// *************************************************
RMatrix  operator &(const RMatrix &A,const INT     i0){
  RMatrix C(1,A.col);
  INT     j;
  
  if((i0 < 0) || (A.row <= i0)){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }

  for(j = 0;j < C.col;j++){
    C.dat[j] = A.dat[i0 * A.col + j];
  }
  return C;
}

RMatrix  operator &(const INT     i0,const RMatrix &A){
  return A & i0;
}

// *************************************************
// 横結合演算子
// *************************************************
RMatrix  operator |(const RMatrix &A,const RMatrix &B){
  RMatrix C(A.row,A.col + B.col);
  INT     i,j;
  
  if(A.row != B.row){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }

  for(i = 0;i < C.row;i++){
    for(j = 0;j < A.col;j++){
      C.dat[i * C.col +  j         ] = A.dat[i * A.col + j];
    }
    for(j = 0;j < B.col;j++){
      C.dat[i * C.col + (j + A.col)] = B.dat[i * B.col + j];
    }
  }
  return C;
}

// *************************************************
// j0列を抜き出す演算子
// *************************************************
RMatrix  operator |(const RMatrix &A,const INT     j0){
  RMatrix C(A.row,1);
  INT     i;
  
  if((j0 < 0) || (A.col <= j0)){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }

  for(i = 0;i < A.row;i++){
    C.dat[i] = A.dat[i * A.col + j0];
  }
  return C;
}

RMatrix  operator |(const INT     j0,const RMatrix &A){
  return A | j0;
}
