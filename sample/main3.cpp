#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

int main(){
  DMatrix A(5,1);
  T2000   ts = T2000__MAKE_FROM_TEXT("2017-05-03 06:30");
  T2000   te = T2000__MAKE_FROM_TEXT("2018-05-03 06:30");
  
  A[0][0] = T2000__MAKE_FROM_TEXT("2017-05-03 06:30");
  A[1][0] = T2000__MAKE_FROM_TEXT("2017-05-04 06:30");

  show(A,(ts <= A));
  cerr << (ts <= A) << endl;

  A = linspace("2017-05-03 06:30","2017-05-05 04:30",5 * T2000__MIN);
  show(A);
  return 0;
}
