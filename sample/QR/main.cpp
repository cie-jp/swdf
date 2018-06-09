#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

//Householder変換によるQR分解(row >= colの場合)
void QR_REAL(TMatrix<REAL> &Q, //(out) [row][row]
             TMatrix<REAL> &R, //(out) [row][col]
             TMatrix<REAL> &A){//(in)  [row][col]
  INT           dim = (A.get_row() < A.get_col()) ? A.get_row() : A.get_col();
  TVector<REAL> b0(dim);
  TVector<REAL> wu(dim);
  TVector<REAL>  u(A.get_row());
  TMatrix<REAL>  P,I;
  INT            i,c;
  REAL           norm;

  R = A;
  REAL__MATRIX_QR(&b0[0],&wu[0],&R[0][0],R.get_row(),R.get_col());

  eye(I,R.get_row(),R.get_row());  
  P = I;

  for(c = 0;c < dim;c++){
    u = TVector<REAL>(R.get_row());
    for(i = c;i < R.get_row();i++){
      u[i] = R[i][c];
    }
    P = (I - (1.0 + wu[c]) * u * ~u) * P;
  }
  Q = ~P;

  for(c = 0;c < dim;c++){
    R[c][c] = b0[c];
    for(i = c + 1;i < R.get_row();i++){
      R[i][c] = 0.0;
    }
  }
  
}

void QR_COMP(TMatrix<COMP> &Q, //(out) [row][row]
             TMatrix<COMP> &R, //(out) [row][col]
             TMatrix<COMP> &A){//(in)  [row][col]
  INT           dim = (A.get_row() < A.get_col()) ? A.get_row() : A.get_col();
  TVector<REAL> b0(dim);
  TVector<COMP> wu(dim);
  TVector<COMP>  u(A.get_row());
  TMatrix<COMP>  P,I;
  INT            i,c;
  REAL           norm;

  R = A;
  COMP__MATRIX_QR(&b0[0],&wu[0],&R[0][0],R.get_row(),R.get_col());

  I = TMatrix<COMP>(R.get_row(),R.get_row());
  for(i = 0;i < R.get_row();i++){
    I[i][i] = COMP__ONE();
  }

  P = I;

  for(c = 0;c < dim;c++){
    u = TVector<COMP>(R.get_row());
    for(i = c;i < R.get_row();i++){
      u[i] = R[i][c];
    }
    P = (I - COMPLEX__ADD(COMP__ONE(),wu[c]) * u * ~u) * P;
  }
  Q = ~P;

  for(c = 0;c < dim;c++){
    R[c][c] = COMPLEX__MAKE_REAL(b0[c]);
    for(i = c + 1;i < R.get_row();i++){
      R[i][c] = COMP__ZERO();
    }
  }
  
}

int main(int argc,char *argv[]){
  /*
  TMatrix<COMP> A = TMatrix<COMP>::random(5,8);
  TMatrix<COMP> Q,R;
  
  QR_COMP(Q,R,A);

  cerr << A << endl;
  cerr << Q << endl;
  cerr << R << endl;
  cerr << Q * R << endl;
  */

  /*
  TMatrix<REAL> A = TMatrix<REAL>::random(5,5);
  TMatrix<REAL> L,U;

  lu(L,U,A);

  cerr << A << endl;
  cerr << L << endl;
  cerr << U << endl;
  cerr << L * U << endl;
  */

  /*
  TMatrix<COMP> A = TMatrix<COMP>::random(5,5);
  TMatrix<COMP> L,U;

  lu(L,U,A);

  cerr << A << endl;
  cerr << L << endl;
  cerr << U << endl;
  cerr << L * U << endl;
  */

  /*
  TMatrix<REAL> A = TMatrix<REAL>::random(5,5);
  TMatrix<REAL> B = A * ~A;
  TMatrix<REAL> L;

  choleskey(L,B);

  cerr << B << endl;
  cerr << L << endl;
  cerr << L * ~L << endl;
  */
  TMatrix<COMP> A = TMatrix<COMP>::random(5,5);
  TMatrix<COMP> B = A * ~A;
  TMatrix<COMP> L;

  choleskey(L,B);

  cerr << B << endl;
  cerr << L << endl;
  cerr << L * ~L << endl;
  
  return 0;
}
