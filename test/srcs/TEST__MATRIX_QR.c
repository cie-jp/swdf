/*****************************************************************
 *
 * 実対称3重対角行列のQR分解
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

// *******************************************************************
// 実対称3重対角行列
//
//            | T0[0]  T1[0]     0      0  ...         0          0  |
//            | T1[0]  T0[1]  T1[1]     0  ...         .          .  |
//            |    0   T1[1]  T0[2]  T1[2] ...         .          .  |
// T        = |    0      0   T1[2]  T0[3] ...         .          .  |
//            |    .      .      .      .              0          0  |
//            |    0      0      0      0  ...  T1[n - 3]         0  | 
//            |    0      0      0      0  ...  T0[n - 2]  T1[n - 2] | 
//            |    0      0      0      0  ...  T1[n - 2]  T0[n - 1] |
//
// のQR分解(T = QR)を行う. 上三角行列Rは, 
//
//            | R0[0]  R1[0]  R2[0]     0  ...         0          0  |
//            |    0   R0[1]  R1[1]  R2[1] ...         .          .  |
//            |    0      0   R0[2]  R1[2] ...         .          .  |
// R        = |    0      0      0   R0[3] ...         .          .  |
//            |    .      .      .      .       R2[n - 4]         0  |
//            |    0      0      0      0  ...  R1[n - 3]  R2[n - 3] | 
//            |    0      0      0      0  ...  R0[n - 2]  R1[n - 2] | 
//            |    0      0      0      0  ...         0   R0[n - 1] |
//  
// となっており, 直交行列Qは,
//
// Q        = P[0]^{T}P[1]^{T}P[2]^{T}...P[n - 2]^{T}
//
// で与えられる. 
// ここで, 
//
//            |  C[0]   S[0]     0      0  ...         0          0  |
//            | -S[0]   C[0]     0      0  ...         .          .  |
//            |    0      0      1      0  ...         .          .  |
// P[0]     = |    0      0      0      1  ...         .          .  |
//            |    .      .      .      .              0          0  |
//            |    0      0      0      0  ...         0          0  | 
//            |    0      0      0      0  ...         1          0  | 
//            |    0      0      0      0  ...         0          1  |
//
//            |    1      0      0      0  ...         0          0  |
//            |         C[1]   S[1]     0  ...         .          .  |
//            |    0   -S[1]   C[1]     0  ...         .          .  |
// P[1]     = |    0      0      0      1  ...         .          .  |
//            |    .      .      .      .              0          0  |
//            |    0      0      0      0  ...         0          0  | 
//            |    0      0      0      0  ...         1          0  | 
//            |    0      0      0      0  ...         0          1  |
// ...
//
//            |    1      0      0      0  ...         0          0  |
//            |           1      0      0  ...         .          .  |
//            |    0      0      1      0  ...         .          .  |
// P[n - 2] = |    0      0      0      1  ...         .          .  |
//            |    .      .      .      .              0          0  |
//            |    0      0      0      0  ...         0          0  | 
//            |    0      0      0      0  ...   C[n - 2]   S[n - 2] | 
//            |    0      0      0      0  ...  -S[n - 2]   C[n - 2] |
//
// である. 
// 
// *******************************************************************
void REAL__MATRIX_QR_TRI(REAL C [],//(out)[n - 1] : 直交行列の情報を表すパラメータ
                         REAL S [],//(out)[n - 1] : 直交行列の情報を表すパラメータ
                         REAL R0[],//(out)[n]     : 上三角行列の対角成分
                         REAL R1[],//(out)[n - 1] : 上三角行列の非対角成分1
                         REAL R2[],//(out)[n - 2] : 上三角行列の非対角成分2 (R2の計算が不要な場合はNULLを入れる)
                         REAL T0[],//(in) [n]     : 3重対角行列の対角成分
                         REAL T1[],//(in) [n - 1] : 3重対角行列の非対角成分
                         INT  n){  //(in)         : 3重対角行列の次元数
  REAL L;
  INT  i;
  
  for(i = 0;i < n    ;i++){
    R0[i] = T0[i];
  }
  for(i = 0;i < n - 1;i++){
    R1[i] = T1[i];
  }

  for(i = 0;i < n - 2;i++){
    L         = REAL__SQRT(REAL__ADD(REAL__MUL(R0[i],R0[i]),REAL__MUL(T1[i],T1[i])));
    if(REAL__EQ(L,REAL__ZERO())){
      C[i   ] = REAL__ONE ();
      S[i   ] = REAL__ZERO();
    }else{
      C[i   ] = REAL__DIV(R0[i],L);
      S[i   ] = REAL__DIV(T1[i],L);
    }
    R0[i    ] = L;
    R0[i + 1] = REAL__ADD(REAL__MUL(REAL__NEGATIVE(S[i]),R1[i]),REAL__MUL(C[i],T0[i + 1]));
    R1[i    ] = REAL__ADD(REAL__MUL(               C[i] ,R1[i]),REAL__MUL(S[i],T0[i + 1]));
    R1[i + 1] = REAL__MUL(C[i],T1[i + 1]);
  }
    L         = REAL__SQRT(REAL__ADD(REAL__MUL(R0[i],R0[i]),REAL__MUL(T1[i],T1[i])));
    if(REAL__EQ(L,REAL__ZERO())){
      C[i   ] = REAL__ONE ();
      S[i   ] = REAL__ZERO();
    }else{
      C[i   ] = REAL__DIV(R0[i],L);
      S[i   ] = REAL__DIV(T1[i],L);
    }
    R0[i    ] = L;
    R0[i + 1] = REAL__ADD(REAL__MUL(REAL__NEGATIVE(S[i]),R1[i]),REAL__MUL(C[i],T0[i + 1]));
    R1[i    ] = REAL__ADD(REAL__MUL(               C[i] ,R1[i]),REAL__MUL(S[i],T0[i + 1]));  

  if(R2 != NULL){
    for(i = 0;i < n - 2;i++){
      R2[i] = REAL__MUL(S[i],T1[i + 1]);
    }
  }
}

// *******************************************************************
// 実対称3重対角行列
//
//            | T0[0]  T1[0]     0      0  ...         0          0  |
//            | T1[0]  T0[1]  T1[1]     0  ...         .          .  |
//            |    0   T1[1]  T0[2]  T1[2] ...         .          .  |
// T        = |    0      0   T1[2]  T0[3] ...         .          .  |
//            |    .      .      .      .              0          0  |
//            |    0      0      0      0  ...  T1[n - 3]         0  | 
//            |    0      0      0      0  ...  T0[n - 2]  T1[n - 2] | 
//            |    0      0      0      0  ...  T1[n - 2]  T0[n - 1] |
//
// のQR分解(T = QR)により得られるRとQ(REAL__MATRIX_QR_TRIにより計算可能)からRQを計算する. 
// すなわち
//            | U0[0]  U1[0]     0      0  ...         0          0  |
//            | U1[0]  U0[1]  U1[1]     0  ...         .          .  |
//            |    0   U1[1]  U0[2]  U1[2] ...         .          .  |
// RQ       = |    0      0   U1[2]  U0[3] ...         .          .  |
//            |    .      .      .      .              0          0  |
//            |    0      0      0      0  ...  U1[n - 3]         0  | 
//            |    0      0      0      0  ...  U0[n - 2]  U1[n - 2] | 
//            |    0      0      0      0  ...  U1[n - 2]  U0[n - 1] |
// を返す. 
// *******************************************************************
void REAL__MATRIX_RQ_TRI(REAL U0[],//(out)[n]     : 3重対角行列RQの対角成分
                         REAL U1[],//(out)[n - 1] : 3重対角行列RQの非対角成分
                         REAL C [],//(in) [n - 1] : QR分解の直交行列Qの情報を表すパラメータ
                         REAL S [],//(in) [n - 1] : QR分解の直交行列Qの情報を表すパラメータ
                         REAL R0[],//(in) [n]     : QR分解の上三角行列Rの対角成分
                         REAL R1[],//(in) [n - 1] : QR分解の上三角行列Rの非対角成分1
                         INT  n){  //(in)         : 行列の次元数
  INT i;
  
    U0[0    ] = C[0]            * R0[0    ] + S[0] * R1[0];
  for(i = 1;i < n - 1;i++){
    U0[i    ] = C[i] * C[i - 1] * R0[i    ] + S[i] * R1[i];
  }
    U0[n - 1] =        C[n - 2] * R0[n - 1];
  
  for(i = 0;i < n - 1;i++){
    U1[i] = S[i] * R0[i + 1];
  }
}

// *******************************************************************
// 2次実対称行列
//
// A = | a0 a1 |
//     | a1 a2 | 
// の二つの固有値emax,emin(emax > emin)を返す.  
// *******************************************************************
void REAL__MATRIX_EIGENVALUES_2D(REAL *emax,
                                 REAL *emin,
                                 REAL  a0,
                                 REAL  a1,
                                 REAL  a2){
  REAL mu;
  REAL d;
  
  mu    = REAL__MUL(REAL__ADD(a0,a2),REAL__TWO());
  d     = REAL__MUL(REAL__SQRT(REAL__ADD(REAL__NORM(REAL__SUB(a0,a2)),REAL__NORM(REAL__MUL(REAL__TWO(),a1)))),REAL__TWO());
  *emax = REAL__ADD(mu,d);
  *emin = REAL__SUB(mu,d);
}

// *******************************************************************
// 実対称3重対角行列
//
//            | T0[0]  T1[0]     0      0  ...         0          0  |
//            | T1[0]  T0[1]  T1[1]     0  ...         .          .  |
//            |    0   T1[1]  T0[2]  T1[2] ...         .          .  |
// T        = |    0      0   T1[2]  T0[3] ...         .          .  |
//            |    .      .      .      .              0          0  |
//            |    0      0      0      0  ...  T1[n - 3]         0  | 
//            |    0      0      0      0  ...  T0[n - 2]  T1[n - 2] | 
//            |    0      0      0      0  ...  T1[n - 2]  T0[n - 1] |
//
// の固有値分解T = U diag(L) U^{T}を減次付WilkinsonシフトQR法により計算する.
// ここで, Uは直交行列を表し,
// LはTの固有値からなるベクトルである. 
// また,
//            |  L[0]     0      0      0  ...         0          0  |
//            |    0    L[1]     0      0  ...         .          .  |
//            |    0      0    L[2]     0  ...         .          .  |
// diag(L)  = |    0      0      0      0  ...         .          .  |
//            |    .      .      .      .              0          0  |
//            |    0      0      0      0  ...         0          0  | 
//            |    0      0      0      0  ...   L[n - 2]         0  | 
//            |    0      0      0      0  ...         0    L[n - 1] |
// である.
// 
// 返される固有値は|L[0]| > |L[1]| > |L[2]| > ...の順に並ぶ(QR法の性質).
// また, L[k]に対応する固有ベクトルv[k]は,
//
//            | U[     0  * n + k] |
//            | U[     1  * n + k] |
//            | U[     2  * n + k] |
// v[k]     = | U[     3  * n + k] |
//            |           .        |
//            | U[(n - 2) * n + k] |
//            | U[(n - 1) * n + k] |
//
// であり, 大きさは1で規格化されており, 固有ベクトルは互いに直交している. 
//
// *******************************************************************
void REAL__MATRIX_EIGENVALUE_DECOMPOSITION_TRI(REAL U [],//(out)[n * n] : 直交行列
                                               REAL T0[],//(io) [n]     : 実対称3重対角行列の対角成分   (対角化した結果のLの  対角成分が返される. 固有値配列)
                                               REAL T1[],//(io) [n - 1] : 実対称3重対角行列の非対角成分 (対角化した結果のLの非対角成分が返される. 数値誤差がなければ全て0)
                                               INT  n){  //(in)         : 行列の次元数
  void *mem;
  REAL *C ;//[n - 1]
  REAL *S ;//[n - 1]
  REAL *R0;//[n]
  REAL *R1;//[n - 1]
  REAL *R2;//[n - 2]
  REAL  emax;
  REAL  emin;
  REAL  shift;
  REAL  tmp1,tmp2;
  INT   i,j;
  INT   m;
  REAL  eps = 1.0e-17;
  
  // ******************************************************************
  //  1. 作業変数のメモリ確保
  // ******************************************************************
  if((mem = malloc(sizeof(REAL) * (n - 1)
                 + sizeof(REAL) * (n - 1)
                 + sizeof(REAL) *  n
                 + sizeof(REAL) * (n - 1)
                 + sizeof(REAL) * (n - 2))) == NULL){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }

  // ******************************************************************
  //  2. メモリ割り当て
  // ******************************************************************
  C  = (REAL*)mem;
  S  = (REAL*)&C [n - 1];
  R0 = (REAL*)&S [n - 1];
  R1 = (REAL*)&R0[n];
  R2 = (REAL*)&R1[n - 1];

  // ******************************************************************
  //  3. Uを単位行列で初期化
  // ******************************************************************  
  for(i = 0;i < n;i++){
    for(j = 0;j < n;j++){
      U[i * n + j] = (i == j) ? REAL__ONE() : REAL__ZERO();
    }
  }

  for(m = n;m > 1;m--){
    while(1){
      // ******************************************************************
      //  4. 右下2x2対称行列の2つの固有値を取得
      // ******************************************************************  
      REAL__MATRIX_EIGENVALUES_2D(&emax,&emin,T0[m - 2],T1[m - 2],T0[m - 1]);
      // ******************************************************************
      //  5. 右下2x2対称行列の非対角成分が十分小さければ減次
      // ******************************************************************  
      if((REAL__MUL(eps,REAL__ABS(emax)) >= REAL__ABS(T1[m - 2])) &&
         (REAL__MUL(eps,REAL__ABS(emin)) >= REAL__ABS(T1[m - 2])) ){
        break;
      }         
      // ******************************************************************
      //  6. QR法のWilkinsonシフト量を固有値から計算
      // ******************************************************************        
      if(REAL__LE(REAL__NORM(REAL__SUB(emax,T0[m - 1])),REAL__NORM(REAL__SUB(emin,T0[m - 1])))){
        shift = emax;
      }else{
        shift = emin;
      }
      // ******************************************************************
      //  7. T      <= T - shift I : Tの対角成分をシフト
      // ******************************************************************              
      for(i = 0;i < m;i++){
        T0[i] = REAL__SUB(T0[i],shift);
      }
      // ******************************************************************
      //  8. (Q, R) <= T           : TのQR分解
      // ******************************************************************                    
      REAL__MATRIX_QR_TRI(C,S,R0,R1,NULL,T0,T1,m);
      // ******************************************************************
      //  9. U      <= QU          : 直交行列の更新
      // ******************************************************************                          
      for(i = 0;i < n;i++){
        for(j = 0;j < m - 1;j++){
          tmp1               = REAL__ADD(REAL__MUL(               C[j] ,U[i * n + j]),REAL__MUL(S[j],U[i * n + (j + 1)]));
          tmp2               = REAL__ADD(REAL__MUL(REAL__NEGATIVE(S[j]),U[i * n + j]),REAL__MUL(C[j],U[i * n + (j + 1)]));
          U[i * n +  j     ] = tmp1;
          U[i * n + (j + 1)] = tmp2;
        }
      }
      // ******************************************************************
      // 10. T      <= RQ          : RQ = Q^{T}TQの計算(Tの相似変換)
      // ******************************************************************                                
      REAL__MATRIX_RQ_TRI(T0,T1,C,S,R0,R1,m);
      // ******************************************************************
      // 11. T      <= T + shift I : シフトを元に戻す
      // ******************************************************************                                      
      for(i = 0;i < m;i++){
        T0[i] = REAL__ADD(T0[i],shift);
      }
    }
  }

  // ******************************************************************
  // 12. 作業変数のメモリ解放
  // ******************************************************************
  free(mem);
}


#define dim (10)

int main(void){
  REAL   A[dim][dim],P[dim][dim],T[dim][dim],R[dim][dim],TMP_R[dim][dim],Q[dim][dim],TMP_P[dim][dim],I[dim][dim],QR[dim][dim],RQ[dim][dim];
  RANDOM rnd;
  INT4   i,j,k;
  REAL   AMP,COS,SIN;
  
  RANDOM__INITIALIZE(&rnd);

  for(i = 0;i < dim;i++){
    for(j = 0;j < dim;j++){
      P[i][j] = (i == j) ? REAL__ONE() : REAL__ZERO();      
    }
  }

  for(i = 0;i < dim;i++){
    for(j = 0;j < dim;j++){
      A[i][j] = REAL__ZERO();      
    }
  }
  for(i = 0;i < dim;i++){
    A[i][i] = RANDOM__NORMAL(&rnd,0.0,1.0);    
  }
  for(i = 0;i < dim - 1;i++){
    A[i][i + 1] = RANDOM__NORMAL(&rnd,0.0,1.0);
    A[i + 1][i] = A[i][i + 1];
  }

  REAL__MATRIX_PRINT(&A[0][0],dim,dim,stderr);

  for(i = 0;i < dim;i++){
    for(j = 0;j < dim;j++){
      R[i][j] = A[i][j];
    }
  }

  for(k = 0;k < dim - 1;k++){
    for(i = 0;i < dim;i++){
      for(j = 0;j < dim;j++){
        T[i][j] = (i == j) ? REAL__ONE() : REAL__ZERO();      
      }
    }
    AMP = sqrt(R[k][k] * R[k][k] + R[k + 1][k] * R[k + 1][k]);
    COS = R[k    ][k] / AMP;
    SIN = R[k + 1][k] / AMP;
    T[k    ][k    ] =  COS;T[k    ][k + 1] = SIN;
    T[k + 1][k    ] = -SIN;T[k + 1][k + 1] = COS;
    
    REAL__MATRIX_MUL(&TMP_R[0][0],&T[0][0],dim,dim,&R[0][0],dim,dim);
    REAL__MATRIX_MUL(&TMP_P[0][0],&T[0][0],dim,dim,&P[0][0],dim,dim);

    for(i = 0;i < dim;i++){
      for(j = 0;j < dim;j++){
        R[i][j] = TMP_R[i][j];
        P[i][j] = TMP_P[i][j];
      }
    }

    REAL__MATRIX_PRINT(&R[0][0],dim,dim,stderr);
  }

  for(i = 0;i < dim;i++){
    for(j = 0;j < dim;j++){
      Q[i][j] = P[j][i];
    }
  }
  
  REAL__MATRIX_MUL(&I[0][0],&Q[0][0],dim,dim,&P[0][0],dim,dim);

  REAL__MATRIX_MUL(&QR[0][0],&Q[0][0],dim,dim,&R[0][0],dim,dim);
  REAL__MATRIX_MUL(&RQ[0][0],&R[0][0],dim,dim,&Q[0][0],dim,dim);

  REAL__MATRIX_PRINT(&I[0][0],dim,dim,stderr);

  REAL__MATRIX_PRINT(&QR[0][0],dim,dim,stderr);
  REAL__MATRIX_PRINT(&RQ[0][0],dim,dim,stderr);

  double C[dim - 1];
  double S[dim - 1];
  double A0[dim];     //A対角成分
  double A1[dim - 1]; //A非対角成分
  double R0[dim];     //R対角成分
  double R1[dim - 1]; //R非対角成分1
  double R2[dim - 2]; //R非対角成分2
  double RQ0[dim];    //QRの対角成分
  double RQ1[dim - 1];//QRの非対角成分1
  
  for(k = 0;k < dim    ;k++){
    A0[k] = A[k][k    ];
  }

  for(k = 0;k < dim - 1;k++){
    A1[k] = A[k][k + 1];
  }

  REAL__MATRIX_QR_TRI(C,S,R0,R1,R2,A0,A1,dim);
  REAL__MATRIX_RQ_TRI(RQ0,RQ1,C,S,R0,R1,dim);

  for(k = 0;k < dim - 2  ;k++){
    printf("%f %f %f\n",R0[k],R1[k],R2[k]);
  }
  printf("%f %f\n",R0[dim - 2],R1[dim - 2]);
  printf("%f\n",R0[dim - 1]);

  printf("===========");
  for(k = 0;k < dim - 1;k++){
    printf("%f %f\n",RQ0[k],RQ1[k]);
  }
  printf("%f\n",RQ0[dim - 1]);

  fprintf(stderr,"============ Orthogonal Matrix Q ==========\n");
  REAL__MATRIX_PRINT(&Q[0][0],dim,dim,stderr);

  double U[dim][dim],L[dim][dim],Ut[dim][dim],UL[dim][dim],ULUt[dim][dim],UtLU[dim][dim],LU[dim][dim];

  REAL__MATRIX_EIGENVALUE_DECOMPOSITION_TRI(&U[0][0],A0,A1,dim);
  REAL__MATRIX_PRINT(&U[0][0],dim,dim,stderr);

  for(i = 0;i < dim;i++){
    for(j = 0;j < dim;j++){
      Ut[i][j] = U[j][i];
    }
  }

  for(i = 0;i < dim;i++){
    for(j = 0;j < dim;j++){
      L[i][j] = REAL__ZERO();
    }
  }
  for(i = 0;i < dim    ;i++){
    L[i][i] = A0[i];
  }

  REAL__MATRIX_MUL(&UL[0][0],&U[0][0],dim,dim,&L[0][0],dim,dim);
  REAL__MATRIX_MUL(&LU[0][0],&L[0][0],dim,dim,&U[0][0],dim,dim);
  REAL__MATRIX_MUL(&ULUt[0][0],&UL[0][0],dim,dim,&Ut[0][0],dim,dim);

  REAL__MATRIX_MUL(&UtLU[0][0],&Ut[0][0],dim,dim,&LU[0][0],dim,dim);

  REAL__MATRIX_PRINT(&ULUt[0][0],dim,dim,stderr);
  REAL__MATRIX_PRINT(&UtLU[0][0],dim,dim,stderr);

  
  
  return 0;
}
