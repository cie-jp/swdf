#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

int main(){
  DMatrix epoch;
  TMatrix<REAL> bscat;
  
  DMatrix__fetch(epoch,"epoch"    ,"~/Desktop/ceilo_l1_20170825_v00.cdf");
  RMatrix__fetch(bscat,"back_scat","~/Desktop/ceilo_l1_20170825_v00.cdf");
  show(epoch);
  show(bscat);
  return 0;
}
