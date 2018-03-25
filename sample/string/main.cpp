#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

int main(int argc,char *argv[]){
  string a = "hoge";
  STRING b;
  STRING c = "hogera";
  STRING d = c;
  STRING e;

  STRING A = "aaaa";
  STRING B = "bbb";
  STRING C = B;


  cout << endl;
  (A + B + "ccccc").show();
  cout << endl;
    
  return 0;
}
