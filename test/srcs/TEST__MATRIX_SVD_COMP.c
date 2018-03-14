/*****************************************************************
 *
 * 複素行列の特異値分解の検証プログラム
 * 
 *
 *                           Created  by Mamoru Ota (2018/03/05)
 * 
 *****************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"MATRIX.h"
#include"RANDOM.h"

//row >= colの場合を扱う. 
void COMP__MATRIX_SVD(REAL s[],//(out) [col]
                      COMP U[],//(out) [row * col]
                      COMP V[],//(out) [col * col]
                      COMP A[],//(in)  [row * col]
                      INT  row,
                      INT  col){
  void *mem;
  COMP *P;  //[row * col]
  REAL *b0; //[col]
  REAL *b1; //[col - 1]
  COMP *wu; //[col]
  COMP *wv; //[col - 1]
  REAL *U0; //[col * col]
  REAL *V0; //[col * col]
  COMP *x;  //[row]
  COMP *y;  //[col]
  COMP  tmp;
  INT   i,j,l;

  if(row < col){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  
  // ******************************************************************
  //  1. 作業変数のメモリ確保
  // ******************************************************************
  if((mem = malloc(sizeof(COMP) *  row * col
                 + sizeof(REAL) *  col
                 + sizeof(REAL) * (col - 1)
                 + sizeof(COMP) *  col
                 + sizeof(COMP) * (col - 1)                   
                 + sizeof(REAL) *  col * col
                 + sizeof(REAL) *  col * col
                 + sizeof(COMP) *  row
                 + sizeof(COMP) *  col)) == NULL){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }

  // ******************************************************************
  //  2. メモリ割り当て
  // ******************************************************************
  P  = (COMP*)mem;
  b0 = (REAL*)&P [row * col];
  b1 = (REAL*)&b0[col];
  wu = (COMP*)&b1[col - 1];
  wv = (COMP*)&wu[col];
  U0 = (REAL*)&wv[col - 1];
  V0 = (REAL*)&U0[col * col];
  x  = (COMP*)&V0[col * col];
  y  = (COMP*)&x [row];

  // ******************************************************************
  //  3. データコピー
  // ******************************************************************
  for(i = 0;i < row;i++){
    for(j = 0;j < col;j++){
      P[i * col + j] = A[i * col + j];
    }
  }

  // ******************************************************************
  //  4. 2重対角化
  // ******************************************************************
  COMP__MATRIX_BIDIAG(b0,b1,wu,wv,P,row,col);

  // ******************************************************************
  //  5. 2重対角行列の特異値分解
  // ******************************************************************
  REAL__MATRIX_SVD_BI(s,U0,V0,b0,b1,col);

  // ******************************************************************
  //  6. 左特異ベクトルの計算
  // ******************************************************************
  for(j = 0;j < col;j++){
    for(i =   0;i < col;i++){
      U[i * col + j] = COMP__MAKE(U0[i * col + j]);
    }
    for(i = col;i < row;i++){
      U[i * col + j] = COMP__ZERO(); 
    }
  }  
  for(l = col - 1;l >= 0;l--){
    for(i = 0;i <   l;i++){
      x[i] = COMP__ZERO();
    }
    for(i = l;i < row;i++){
      x[i] = P[i * col + l];
    }
    for(j = 0;j < col;j++){
      tmp = COMP__ZERO();
      for(i = 0;i < row;i++){
        tmp = COMP__FMA(COMP__CONJ(x[i]),U[i * col + j],tmp);
      }
      tmp = COMP__MUL(COMP__ADD(COMP__ONE(),COMP__CONJ(wu[l])),tmp);
      for(i = 0;i < row;i++){
        U[i * col + j] = COMP__SUB(U[i * col + j],COMP__MUL(tmp,x[i]));
      }
    }
  }  

  // ******************************************************************
  //  7. 右特異ベクトルの計算
  // ******************************************************************
  for(j = 0;j < col;j++){
    for(i = 0;i < col;i++){
      V[i * col + j] = COMP__MAKE(V0[i * col + j]);
    }
  }
  for(l = col - 2;l >= 0;l--){
    for(j =      0 ;j < (l + 1);j++){
      y[j] = COMP__ZERO();
    }
    for(j = (l + 1);j <    col ;j++){
      y[j] = COMP__CONJ(P[l * col + j]);
    }
    for(j = 0;j < col;j++){
      tmp = COMP__ZERO();
      for(i = 0;i < col;i++){
        tmp = COMP__FMA(COMP__CONJ(y[i]),V[i * col + j],tmp);
      }
      tmp = COMP__MUL(COMP__ADD(COMP__ONE(),wv[l]),tmp);
      for(i = 0;i < col;i++){
        V[i * col + j] = COMP__SUB(V[i * col + j],COMP__MUL(tmp,y[i]));
      }
    }
  }
  
  // ******************************************************************
  //  6. 作業変数のメモリ解放
  // ******************************************************************
  free(mem);
}



#define row (12)
#define col (6)

int main(void){
  COMP   A[row][col];
  REAL   s[col];
  COMP   U[row][col];
  COMP   V[col][col];
  COMP   S[col][col];
  RANDOM rnd;
  INT4   i,j;
  COMP   Va[col][col],US[row][col],USVa[row][col],VVa[col][col],Ua[col][row],UaU[col][col];
  
  RANDOM__INITIALIZE(&rnd);

  for(i = 0;i < row;i++){
    for(j = 0;j < col;j++){      
      A[i][j] = COMPLEX__MAKE_RE_IM(RANDOM__NORMAL(&rnd,0.0,1.0),RANDOM__NORMAL(&rnd,0.0,1.0));
      //A[i][j] = COMPLEX__MAKE_RE_IM(RANDOM__NORMAL(&rnd,0.0,1.0),0.0);
    }
  }
  //A[1][3] = COMPLEX__MAKE_RE_IM(RANDOM__NORMAL(&rnd,0.0,1.0),RANDOM__NORMAL(&rnd,0.0,1.0));
  //A[2][4] = COMPLEX__MAKE_RE_IM(RANDOM__NORMAL(&rnd,0.0,1.0),RANDOM__NORMAL(&rnd,0.0,1.0));
  //A[3][1] = COMPLEX__MAKE_RE_IM(RANDOM__NORMAL(&rnd,0.0,1.0),RANDOM__NORMAL(&rnd,0.0,1.0));

  COMP__MATRIX_SVD(s,&U[0][0],&V[0][0],&A[0][0],row,col);
  
  for(i = 0;i < col;i++){
    for(j = 0;j < col;j++){
      S[i][j] = COMP__ZERO();
    }
  }
  for(i = 0;i < col;i++){
    S[i][i] = COMP__MAKE(s[i]);
  }

  for(i = 0;i < col;i++){
    for(j = 0;j < col;j++){
      Va[i][j] = COMP__CONJ(V[j][i]);
    }
  }

  for(i = 0;i < col;i++){
    for(j = 0;j < row;j++){
      Ua[i][j] = COMP__CONJ(U[j][i]);
    }
  }

  COMP__MATRIX_MUL(&US  [0][0],&U [0][0],row,col,&S [0][0],col,col);
  COMP__MATRIX_MUL(&USVa[0][0],&US[0][0],row,col,&Va[0][0],col,col);
  
  COMP__MATRIX_PRINT(&A   [0][0],row,col,stderr);
  COMP__MATRIX_PRINT(&USVa[0][0],row,col,stderr);

  COMP__MATRIX_MUL(&VVa[0][0],&V[0][0],col,col,&Va[0][0],col,col);
  COMP__MATRIX_PRINT(&VVa[0][0],col,col,stderr);

  COMP__MATRIX_MUL(&UaU[0][0],&Ua[0][0],col,row,&U[0][0],row,col);
  COMP__MATRIX_PRINT(&UaU[0][0],col,col,stderr);

  COMP__MATRIX_PRINT(&U[0][0],row,col,stderr);
  COMP__MATRIX_PRINT(&V[0][0],col,col,stderr);

  for(i = 0;i < col;i++){
    printf("%f\n",s[i]);
  }
  
  return 0;
}
