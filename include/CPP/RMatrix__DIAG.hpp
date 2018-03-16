#define MIN(x,y) (((x) <= (y)) ? (x) : (y))

namespace CLDIA{
  RMatrix diag(RMatrix A){
    RMatrix C;
    INT     i;
    
    if(A.get_col() == 1){
      C = RMatrix(A.get_row(),A.get_row());
      for(i = 0;i < A.get_row();i++){
        C[i][i] = A[i][0];
      }
    }else{
      C = RMatrix(MIN(A.get_row(),A.get_col()),1);
      for(i = 0;i < C.get_row();i++){
        C[i][0] = A[i][i];
      }
    }
    return C;
  }
}

RMatrix  RMatrix::diag (){
  return CLDIA::diag(*this);
}
