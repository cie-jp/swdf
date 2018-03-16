namespace CLDIA{
  // row行col列の単位行列(対角成分に1, 非対角成分に0をもつ行列)を返す.
  RMatrix eye (INT row,INT col){
    RMatrix E(row,col);
    INT     dim;
    INT     i;
    
    dim = (row <= col) ? row : col;
    for(i = 0;i < dim;i++){
      E[i][i] = 1.0;
    }
    return E;    
  }
  // dim次の単位行列を返す.
  RMatrix eye (INT dim){
    return eye(dim,dim);
  }
  // dim次のヒルベルト行列を返す. 
  RMatrix hilb(INT dim){
    RMatrix H(dim,dim);
    INT     i,j;
    
    for(i = 0;i < dim;i++){
      for(j = 0;j < dim;j++){
        H[i][j] = 1.0 / (i + j + 1.0);
      }
    }
    return H;
  }

  REAL cond(RMatrix A){
    RMatrix s;
    RMatrix U;
    RMatrix V;

    A.svd(s,U,V);
    return s[0][0] / s[s.get_row() - 1][0];
  }

  REAL det (RMatrix A){
    RMatrix s;
    RMatrix U;
    RMatrix V;
    REAL    d;
    INT     i;

    A.svd(s,U,V);
    d = 1.0;
    for(i = 0;i < s.get_row();i++){
      d *= s[i][0];
    }
    return d;
  }
}

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
