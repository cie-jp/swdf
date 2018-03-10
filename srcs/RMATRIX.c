/***************************************************************** 
 *
 * 行列計算
 *
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/

#include"MATRIX.h"
#include"MEMORY.h"
#include"RANDOM.h"
#include"FFT.h"

void  RMATRIX__INITIALIZE(RMATRIX *mat,INT row,INT col){
  MEMORY__NEW        (mat->dat,REAL,row * col,"none");
  mat->row = row;
  mat->col = col;
  RMATRIX__ZEROFILL  (mat);
}

void  RMATRIX__CLONE     (RMATRIX *mat,RMATRIX *dst){
  RMATRIX__INITIALIZE(dst,mat->row,mat->col);
  RMATRIX__DATACOPY  (dst,mat);
}

void  RMATRIX__FINALIZE  (RMATRIX *mat){
  MEMORY__DEL        (mat->dat);
}

void  RMATRIX__RESIZE    (RMATRIX *mat,INT row,INT col){
  RMATRIX__FINALIZE  (mat);
  RMATRIX__INITIALIZE(mat,row,col);
}


REAL *RMATRIX__GET_DATA  (RMATRIX *mat){
  return mat->dat;
}

INT   RMATRIX__GET_ROW   (RMATRIX *mat){
  return mat->row;
}

INT   RMATRIX__GET_COL   (RMATRIX *mat){
  return mat->col;
}

void  RMATRIX__SHOW_INFO (RMATRIX *mat,FILE *fp){
  INT i,j;

  fprintf(fp,"=== (ROW : %7d | COL : %7d) ===\n",mat->row,mat->col);
  for(i = 0;i < mat->row;i++){
    fprintf(fp,"| ");
    for(j = 0;j < mat->col;j++){
      fprintf(fp,"%20g ",mat->dat[i * mat->col + j]);
    }
    fprintf(fp,"|\n");
  }
}

void  RMATRIX__ZEROFILL  (RMATRIX *mat){
  memset(mat->dat,
         0x00,
         sizeof(REAL) * mat->row * mat->col);
}

void  RMATRIX__DATACOPY  (RMATRIX *mat,RMATRIX *src){
  if((mat->row != src->row) || (mat->col != src->col)){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  memcpy(mat->dat,
         src->dat,
         sizeof(REAL) * mat->row * mat->col);
}

void  RMATRIX__SET_IDENTITY(RMATRIX *mat){
  INT n;

  RMATRIX__ZEROFILL(mat);
  for(n = 0;;n++){
    if((n >= mat->row) || (n >= mat->col)){
      break;
    }
    mat->dat[n * mat->col + n] = 1.0;
  }
}

void  RMATRIX__SET_VALUE   (RMATRIX *mat,REAL val){
  INT i,j;
  
  for(i = 0;i < mat->row;i++){
    for(j = 0;j < mat->col;j++){
      mat->dat[i * mat->col + j] = val;
    }
  }
}

void  RMATRIX__SET_RANDOM  (RMATRIX *mat){
  RANDOM rnd;
  INT    i,j;

  RANDOM__INITIALIZE(&rnd);
  for(i = 0;i < mat->row;i++){
    for(j = 0;j < mat->col;j++){
      mat->dat[i * mat->col + j] = RANDOM__NORMAL(&rnd,0.0,1.0);
    }
  }  
}

void  RMATRIX__SET_DCT     (RMATRIX *mat){
  INT i,j;
  INT dim;

  if(mat->row != mat->col){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  dim = mat->row;

  for(j = 0;j < mat->col;j++){
    mat->dat[0 * mat->col + j] = 1.0 / (REAL)dim;    
  }
  for(i = 1;i < mat->row;i++){
    for(j = 0;j < mat->col;j++){
      mat->dat[i * mat->col + j] = sqrt(2.0 / (REAL)dim) * cos(M_PI / (2.0 * dim) * (2 * j + 1) * i);
    }
  }
}

void  RMATRIX__SET_IDCT    (RMATRIX *mat){
  INT i,j;
  INT dim;

  if(mat->row != mat->col){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  dim = mat->row;
  
  for(i = 0;i < mat->row;i++){
    mat->dat[i * mat->col + 0] = 1.0 / sqrt((REAL)dim);
    for(j = 1;j < mat->col;j++){
      mat->dat[i * mat->col + j] = sqrt(2.0 / (REAL)dim) * cos(M_PI / (2.0 * dim) * (2 * i + 1) * j);      
    }
  }
}



/*
void  RMATRIX__SET_ADD(RMATRIX *C,RMATRIX *A,RMATRIX *B){
  INT i,j;

  if(!RMATRIX__IS_SAMESIZE(A,B) || !RMATRIX__IS_SAMESIZE(B,C)){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  for(i = 0;i < C->row;i++){
    for(j = 0;j < C->col;j++){
      C->dat[i * C->col + j] = A->dat[i * A->col + j] + B->dat[i * B->col + j];
    }
  }
}

void  RMATRIX__SET_SUB(RMATRIX *C,RMATRIX *A,RMATRIX *B){
  INT i,j;

  if(!RMATRIX__IS_SAMESIZE(A,B) || !RMATRIX__IS_SAMESIZE(B,C)){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  for(i = 0;i < C->row;i++){
    for(j = 0;j < C->col;j++){
      C->dat[i * C->col + j] = A->dat[i * A->col + j] - B->dat[i * B->col + j];
    }
  }  
}

void  RMATRIX__SET_MUL(RMATRIX *C,RMATRIX *A,RMATRIX *B){
  REAL tmp;
  INT  i,j,k;

  for(i = 0;i < A->row;i++){
    for(j = 0;j < B->col;j++){
      tmp = 0.0;
      for(int k = 0;k < A.W;k++){
	tmp += A->dat[i * A.W + k] * B->dat[k * B.W + j];
      }
      C->dat[i * C->col + j] = tmp;
    }
  }
}

void  RMATRIX__SET_TIMES(RMATRIX *C,RMATRIX *A,RMATRIX *B){
}
*/

RMATRIX RMATRIX__UPLUS(RMATRIX A){
  
}
