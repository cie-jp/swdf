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
  STRING C;// = A;

  C = A + B;
  cout << endl;
  (A + C + "ccccc").show();
  cout << endl;
  //cerr << strlen(A) << endl;
  cerr << STRING(6,"hogerahogera") << endl;
  return 0;
}
