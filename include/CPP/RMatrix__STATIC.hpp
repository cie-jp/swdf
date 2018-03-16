RMatrix RMatrix::identity(const INT row,const INT col){
  RMatrix A(row,col);
  INT     dim;
  INT     i;

  dim = (row <= col) ? row : col;
  for(i = 0;i < dim;i++){
    A.dat[i * A.col + i] = 1.0;
  }
  return A;
}

RMatrix RMatrix::random  (const INT row,const INT col){
  RMatrix A(row,col);
  RANDOM  rnd;
  INT     i,j;

  RANDOM__INITIALIZE(&rnd);
  
  for(i = 0;i < A.row;i++){
    for(j = 0;j < A.col;j++){
      A.dat[i * A.col + j] = RANDOM__NORMAL(&rnd,0.0,1.0);
    }
  }
  return A;
}
