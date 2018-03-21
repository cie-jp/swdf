#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

typedef struct{
  INT2  YYYY;
  INT1    MM;
  INT1    DD;
  INT1    hh;
  INT1    mm;
  INT1    ss;
  INT2  msec;
  INT2  usec;
  INT2  nsec;
}EPOCH;

void  EPOCH__PRINT    (EPOCH epoch,FILE *fp){
  fprintf(fp,"%04d-%02d-%02d %02d:%02d:%02d.%03d%03d%03d",
          epoch.YYYY,
          epoch.MM,
          epoch.DD,
          epoch.hh,
          epoch.mm,
          epoch.ss,
          epoch.msec,
          epoch.usec,
          epoch.nsec);
}

T2000 EPOCH__GET_T2000(EPOCH epoch){
  return CDF_TT2000_from_UTC_parts((double)epoch.YYYY,
                                   (double)epoch.MM,
                                   (double)epoch.DD,
                                   (double)epoch.hh,
                                   (double)epoch.mm,
                                   (double)epoch.ss,
                                   TT2000END);
}

EPOCH T2000__GET_EPOCH(T2000 t2000){
  double YYYY;
  double MM;
  double DD;
  double hh;
  double mm;
  double ss;
  double msec;
  double usec;
  double nsec;
  EPOCH  epoch;
  
  CDF_TT2000_to_UTC_parts(t2000,
                          &YYYY,
                          &MM,
                          &DD,
                          &hh,
                          &mm,
                          &ss,
                          &msec,
                          &usec,
                          &nsec);
  epoch.YYYY = (INT2)YYYY;
  epoch.MM   = (INT1)MM;
  epoch.DD   = (INT1)DD;
  epoch.hh   = (INT1)hh;
  epoch.mm   = (INT1)mm;
  epoch.ss   = (INT1)ss;
  epoch.msec = (INT2)msec;
  epoch.usec = (INT2)usec;
  epoch.nsec = (INT2)nsec;  
  return epoch;
}

void test_epoch(){
  T2000 a;
  EPOCH b;

  EPOCH__PRINT(b,stdout);
}

void lu_check(){
  RMatrix A;
  RMatrix L,U;

  A = RMatrix::random(6,6);
  lu(L,U,A);

  cerr << A << endl;
  cerr << L << endl;
  cerr << U << endl;
  cerr << L * U << endl;
}

void tmatrix_check(){
  IMatrix A(5,7),B(5,7);

  A[2][3] = 1;
  B[0][2] = 2;
  cerr << A << endl;
  cerr << B << endl;
  cerr << (A | B) << endl;

  TMatrix<REAL> C(5,6);
  for(INT i = 0;i < 5;i++){
    for(INT j = 0;j < 6;j++){
      C[i][j] = i + j;
    }
  }
  cerr << (C > 3.0) << endl;
  cerr <<  C << endl;
  show(C);
  show(C,C < 3.0);

  RMatrix Q = RMatrix::random(100000,1);
  hist(Q,-5,5,70,"hoge.svg");
  TVector<REAL> c(5);
  TVector<REAL> d;

  c[2] = 1.0;
  c[3] = 2.0;
  cerr << c << endl;
  cerr << d << endl;

  show(c,c > 1.0);

  //hist(c,-5,5,70,"piyo.svg");
}

int main(void){
  RMatrix A(3,3);

  A[0][0] =  1.0;A[0][1] = -2.0;A[0][2] = 4.0;
  A[1][0] = -5.0;A[1][1] =  2.0;A[1][2] = 0.0;
  A[2][0] =  1.0;A[2][1] =  0.0;A[2][2] = 3.0;

  cerr <<       A  << endl;
  cerr <<   det(A) << endl;
  cerr <<   det_lu(A) << endl;

  cerr << trace(A) << endl;

  RMatrix s,U,V;
  A.svd(s,U,V);

  cerr << U * diag(s) * ~V << endl;

  cerr << s << endl;
  cerr << U << endl;
  cerr << V << endl;

  lu_check();

  tmatrix_check();
  return 0;
}
