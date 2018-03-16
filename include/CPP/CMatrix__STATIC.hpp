CMatrix CMatrix::identity(const INT row,const INT col){
  CMatrix A(row,col);
  INT     dim;
  INT     i;

  dim = (row <= col) ? row : col;
  for(i = 0;i < dim;i++){
    A.dat[i * A.col + i] = COMP__ONE();
  }
  return A;
}

CMatrix CMatrix::random  (const INT row,const INT col){
  CMatrix A(row,col);
  RANDOM  rnd;
  INT     i,j;

  RANDOM__INITIALIZE(&rnd);
  
  for(i = 0;i < A.row;i++){
    for(j = 0;j < A.col;j++){
      A.dat[i * A.col + j] = COMPLEX__MAKE_RE_IM(RANDOM__NORMAL(&rnd,0.0,1.0),RANDOM__NORMAL(&rnd,0.0,1.0));
    }
  }
  return A;
}
