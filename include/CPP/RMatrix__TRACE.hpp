namespace CLDIA{
  REAL trace(RMatrix A){
    REAL tr;
    INT  i;
    
    if(!A.is_square()){
      ERROR__SHOW("Matrix must be square.");
      exit(EXIT_FAILURE);
    }
    tr = 0.0;
    for(i = 0;i < A.get_row();i++){
      tr += A[i][i];
    }
    return tr;
  }
}

REAL RMatrix::trace(){
  return CLDIA::trace(*this);
}
