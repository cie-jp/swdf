#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

int main(){
  TMatrix<DATA> epoch;
  TMatrix<DATA> bscat;
  TMatrix<DATA> H;
  
  Matrix__fetch(epoch,"epoch"    ,"~/Desktop/ceilo_l1_20170825_v00.cdf");
  Matrix__fetch(bscat,"back_scat","~/Desktop/ceilo_l1_20170825_v00.cdf");
  Matrix__fetch(H    ,"H"        ,"~/Desktop/ceilo_l1_20170825_v00.cdf");


  show(epoch | (bscat | 0));
  show(H);
  return 0;
}
