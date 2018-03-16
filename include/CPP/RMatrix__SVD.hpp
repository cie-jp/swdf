void    RMatrix::svd  (RMatrix &s,RMatrix &U,RMatrix &V){
  if(this->row >= this->col){
    s = RMatrix(this->col,1);
    U = RMatrix(this->row,this->col);
    V = RMatrix(this->col,this->col);
  }else{
    s = RMatrix(this->row,1);
    U = RMatrix(this->row,this->row);
    V = RMatrix(this->col,this->row);
  }
  REAL__MATRIX_SVD(s.dat,U.dat,V.dat,this->dat,this->row,this->col);
}
