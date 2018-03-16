void    CMatrix::svd  (RMatrix &s,CMatrix &U,CMatrix &V){
  if(this->row >= this->col){
    s = RMatrix(this->col,1);
    U = CMatrix(this->row,this->col);
    V = CMatrix(this->col,this->col);
  }else{
    s = RMatrix(this->row,1);
    U = CMatrix(this->row,this->row);
    V = CMatrix(this->col,this->row);
  }
  COMP__MATRIX_SVD(s.get_dat(),U.dat,V.dat,this->dat,this->row,this->col);
}
