// *************************************************
// static private 関数群
// *************************************************

void CMatrix::initialize(CMatrix    &A,
                         const INT   row,
                         const INT   col){
  if(col <= 0 || row <= 0){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  if((A.dat = (COMP*)malloc(sizeof(COMP) * row * col)) == NULL){
    ERROR__SHOW("#2");
    exit(EXIT_FAILURE);    
  }
  A.row = row;
  A.col = col;
}

void CMatrix::finalize  (CMatrix    &A){
  free(A.dat);
}

void CMatrix::resize    (CMatrix    &A,
                         const INT   row,
                         const INT   col){
  if(col <= 0 || row <= 0){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  if((A.row * A.col) != (row * col)){
    CMatrix::finalize  (A);
    CMatrix::initialize(A,row,col);
  }
  A.row = row;
  A.col = col;  
}

void CMatrix::zerofill  (CMatrix    &A){
  memset(A.dat,0x00,sizeof(COMP) * A.row * A.col);    
}

void CMatrix::datacopy  (CMatrix    &A,
                         const COMP *dat){
  if(dat == NULL){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  memcpy(A.dat, dat,sizeof(COMP) * A.row * A.col);  
}
