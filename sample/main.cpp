#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

int main(void){
  RMatrix A = RMatrix::random(7,3);

  cerr << A << endl;
  cerr << A.diag() << endl;
  cerr << A.diag().diag() << endl;
  cerr << diag(A) << endl;
  cerr << diag(diag(A)) << endl;
  return 0;
}
