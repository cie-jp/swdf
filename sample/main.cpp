#include"CLDIA.h"
#include"CPP/RMatrix.h"

using namespace std;

int main(void){
  RMatrix A(3,3);
  RMatrix B = A;
  RMatrix C = A;
  RMatrix D(5,5);
  
  for(int i = 0;i < 5;i++){
    for(int j = 0;j < 5;j++){
      D[i][j] = rand() / (double)RAND_MAX;
    }
  }

  cerr << D << endl;
  cerr << !D << endl;
  cerr << D * !D << endl;
  
  return 0;
}
