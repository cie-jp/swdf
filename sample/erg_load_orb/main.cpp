#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

int main(int argc,char *argv[]){
  //system("curl -L -o test2.cdf http://ergsc.isee.nagoya-u.ac.jp/data/ergsc/satellite/erg/orb/def/2017/erg_orb_l2_20170116_v01.cdf");
  //fprintf(stderr,"FINISH!\n");
  STRING a = "hoge";
  REAL8 b;
  INT4 c;
  a = "piyo";
  a = STRING("%04d",30) + "hoge";
  a += STRING("asd");
  a  = STRING("asdfhhogehoege %d %s\n",130,"hoge");
  //a  = "asd%c\n";
  a  = 30.0;
  b = a;
  a.show();
  c = a;
  cerr << b << endl;
  cerr << c << endl;
  a = "2017-03-01 12:30:21.001";
  TIME_TT2000 e;
  e = a;
  a.show();
  a = e;
  a.show();
  cerr << endl;
  cerr << STRING((REAL8)STRING("%d",30)) << endl;
  return 0;
}

//curl -L -o test2.cdf http://ergsc.isee.nagoya-u.ac.jp/data/ergsc/satellite/erg/orb/def/2017/erg_orb_l2_20170116_v[01-99].cdf
//curl -I http://ergsc.isee.nagoya-u.ac.jp/data/ergsc/satellite/erg/orb/def/2017/erg_orb_l2_20170116_v[01-99].cdf

//curl -L http://ergsc.isee.nagoya-u.ac.jp/data/ergsc/satellite/erg/orb/def/2017/
