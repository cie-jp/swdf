RMatrix  RMatrix::diag (){
  RMatrix A(this->row,this->row);
  INT     i;
  
  if((this->row != this->col) && (this->col != 1)){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);    
  }

  if(this->row == this->col){
    for(i = 0;i < A.row;i++){
      A.dat[i * A.col + i] = this->dat[i * this->col + i];
    }
  }else{
    for(i = 0;i < A.row;i++){
      A.dat[i * A.col + i] = this->dat[i];
    }
  }
  return A;
}
