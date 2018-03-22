#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

int main(){
  TMatrix<DATA> epoch;
  TMatrix<DATA> bscat;
  
  Matrix__fetch(epoch,"epoch"    ,"~/Desktop/ceilo_l1_20170825_v00.cdf");
  Matrix__fetch(bscat,"back_scat","~/Desktop/ceilo_l1_20170825_v00.cdf");


  show(epoch | (bscat | 0));
  return 0;
}
