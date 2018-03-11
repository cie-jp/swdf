/*****************************************************************
 *
 * 実行列の2重対角化の検証プログラム
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

int main(void){
  REAL   A[5][5];
  REAL   B[5][5];
  REAL   x[5];
  REAL   y[5];
  RANDOM rnd;
  INT4   i,j;
  REAL   U[5][5],V[5][5],R[5][5],Q[5][5],T[5][5];

  RANDOM__INITIALIZE(&rnd);

  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      A[i][j] = RANDOM__NORMAL(&rnd,0.0,1.0);
      B[i][j] = A[i][j];
      T[i][j] = A[i][j];
    }
  }

  REAL__MATRIX_PRINT(&A[0][0],5,5,stderr);

  REAL__MATRIX_BIDIAGONALIZATION(&B[0][0],5,5);

  // 1-1. 
  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      U[i][j] = (i == j) ? REAL__ONE() : REAL__ZERO();
    }
  }
  for(i = 0;i < 5;i++){
    x[i] = REAL__ZERO();
  }
  for(i = 0;i < 5;i++){
    x[i] = B[i][0];
  }
  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      U[i][j] = REAL__SUB(U[i][j],REAL__MUL(REAL__TWO(),REAL__MUL(x[i],x[j])));
    }
  }

  REAL__MATRIX_MUL(&R[0][0],&U[0][0],5,5,&T[0][0],5,5);
  REAL__MATRIX_PRINT(&R[0][0],5,5,stderr);

  // 1-2. 
  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      V[i][j] = (i == j) ? REAL__ONE() : REAL__ZERO();
    }
  }
  for(j = 0;j < 5;j++){
    y[j] = REAL__ZERO();
  }
  for(j = 1;j < 5;j++){
    y[j] = B[0][j];
  }
  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      V[i][j] = REAL__SUB(V[i][j],REAL__MUL(REAL__TWO(),REAL__MUL(y[i],y[j])));
    }
  }

  REAL__MATRIX_MUL(&Q[0][0],&R[0][0],5,5,&V[0][0],5,5);
  REAL__MATRIX_PRINT(&Q[0][0],5,5,stderr);

  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      T[i][j] = Q[i][j];
    }
  }

  //2-1.
  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      U[i][j] = (i == j) ? REAL__ONE() : REAL__ZERO();
    }
  }
  for(i = 0;i < 5;i++){
    x[i] = REAL__ZERO();
  }
  for(i = 1;i < 5;i++){
    x[i] = B[i][1];
  }
  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      U[i][j] = REAL__SUB(U[i][j],REAL__MUL(REAL__TWO(),REAL__MUL(x[i],x[j])));
    }
  }

  REAL__MATRIX_MUL(&R[0][0],&U[0][0],5,5,&T[0][0],5,5);
  REAL__MATRIX_PRINT(&R[0][0],5,5,stderr);

  //2-2. 
  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      V[i][j] = (i == j) ? REAL__ONE() : REAL__ZERO();
    }
  }
  for(j = 0;j < 5;j++){
    y[j] = REAL__ZERO();
  }
  for(j = 2;j < 5;j++){
    y[j] = B[1][j];
  }
  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      V[i][j] = REAL__SUB(V[i][j],REAL__MUL(REAL__TWO(),REAL__MUL(y[i],y[j])));
    }
  }

  REAL__MATRIX_MUL(&Q[0][0],&R[0][0],5,5,&V[0][0],5,5);
  REAL__MATRIX_PRINT(&Q[0][0],5,5,stderr);

  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      T[i][j] = Q[i][j];
    }
  }

  //3-1. 
  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      U[i][j] = (i == j) ? REAL__ONE() : REAL__ZERO();
    }
  }
  for(i = 0;i < 5;i++){
    x[i] = REAL__ZERO();
  }
  for(i = 2;i < 5;i++){
    x[i] = B[i][2];
  }
  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      U[i][j] = REAL__SUB(U[i][j],REAL__MUL(REAL__TWO(),REAL__MUL(x[i],x[j])));
    }
  }

  REAL__MATRIX_MUL(&R[0][0],&U[0][0],5,5,&T[0][0],5,5);
  REAL__MATRIX_PRINT(&R[0][0],5,5,stderr);

  //3-2.
  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      V[i][j] = (i == j) ? REAL__ONE() : REAL__ZERO();
    }
  }
  for(j = 0;j < 5;j++){
    y[j] = REAL__ZERO();
  }
  for(j = 3;j < 5;j++){
    y[j] = B[2][j];
  }
  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      V[i][j] = REAL__SUB(V[i][j],REAL__MUL(REAL__TWO(),REAL__MUL(y[i],y[j])));
    }
  }

  REAL__MATRIX_MUL(&Q[0][0],&R[0][0],5,5,&V[0][0],5,5);
  REAL__MATRIX_PRINT(&Q[0][0],5,5,stderr);

  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      T[i][j] = Q[i][j];
    }
  }

  //4-1.
  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      U[i][j] = (i == j) ? REAL__ONE() : REAL__ZERO();
    }
  }
  for(i = 0;i < 5;i++){
    x[i] = REAL__ZERO();
  }
  for(i = 3;i < 5;i++){
    x[i] = B[i][3];
  }
  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      U[i][j] = REAL__SUB(U[i][j],REAL__MUL(REAL__TWO(),REAL__MUL(x[i],x[j])));
    }
  }

  REAL__MATRIX_MUL(&R[0][0],&U[0][0],5,5,&T[0][0],5,5);
  REAL__MATRIX_PRINT(&R[0][0],5,5,stderr);

  //4-2.
    for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      V[i][j] = (i == j) ? REAL__ONE() : REAL__ZERO();
    }
  }
  for(j = 0;j < 5;j++){
    y[j] = REAL__ZERO();
  }
  for(j = 4;j < 5;j++){
    y[j] = B[3][j];
  }
  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      V[i][j] = REAL__SUB(V[i][j],REAL__MUL(REAL__TWO(),REAL__MUL(y[i],y[j])));
    }
  }

  REAL__MATRIX_MUL(&Q[0][0],&R[0][0],5,5,&V[0][0],5,5);
  REAL__MATRIX_PRINT(&Q[0][0],5,5,stderr);

  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      T[i][j] = Q[i][j];
    }
  }

  
  REAL__MATRIX_PRINT(&B[0][0],5,5,stderr);

  return 0;
}
