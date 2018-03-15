// *************************************************
// static private 関数群
// *************************************************

void RMatrix::initialize(RMatrix    &A,
                         const INT   row,
                         const INT   col){
  if(col <= 0 || row <= 0){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  if((A.dat = (REAL*)malloc(sizeof(REAL) * row * col)) == NULL){
    ERROR__SHOW("#2");
    exit(EXIT_FAILURE);    
  }
  A.row = row;
  A.col = col;
}

void RMatrix::finalize  (RMatrix    &A){
  free(A.dat);
}

void RMatrix::resize    (RMatrix    &A,
                         const INT   row,
                         const INT   col){
  if(col <= 0 || row <= 0){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  if((A.row * A.col) != (row * col)){
    RMatrix::finalize  (A);
    RMatrix::initialize(A,row,col);
  }
  A.row = row;
  A.col = col;  
}

void RMatrix::zerofill  (RMatrix    &A){
  memset(A.dat,0x00,sizeof(REAL) * A.row * A.col);    
}

void RMatrix::datacopy  (RMatrix    &A,
                         const REAL *dat){
  if(dat == NULL){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  memcpy(A.dat, dat,sizeof(REAL) * A.row * A.col);  
}
