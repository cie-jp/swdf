#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

class plot{
private:
  SVGPLOT plt;
public:
  plot(){
    SVGPLOT__INITIALIZE_002(&plt,"SVG_TEST1.svg");
  }
  void lplot(RVector &x,RVector &y){
    if(x.get_dim() != y.get_dim()){
      ERROR__SHOW("x.dim != y.dim");
      exit(EXIT_FAILURE);
    }
    SVGPLOT__XY_LPLOT(&plt,
                      x.get_dat(),
                      y.get_dat(),
                      x.get_dim(),
                      -1.0,-1.0,-1.0,0,
                      "1.0","#000000","0.5px",NULL,NULL,"round","round");
  }
  void pplot(RVector &x,RVector &y){    
    if(x.get_dim() != y.get_dim()){
      ERROR__SHOW("x.dim != y.dim");
      exit(EXIT_FAILURE);
    }
    SVGPLOT__XY_PPLOT(&plt,
                      x.get_dat(),y.get_dat(),x.get_dim(),
                      2.0,
                      0,
                      "1.0","#000000","0.5px",NULL,NULL,"round","round","#FF0000");
  }
  void aux(){
    SVGPLOT__XY_AUX(&plt,
                    1,1,1,1,
                    3,3,3,3,
                    1,2,1,2,
                    1);
  }
  ~plot(){
    SVGPLOT__FINALIZE(&plt);
  }
};

int main(int argc,char *argv[]){
  RVector x = RVector::random(1000);
  RVector y = RVector::random(1000);
  plot p;

  //p.lplot(x,y);
  p.pplot(x,y);  
  p.aux();
  
  cerr << (x | y) << endl;
  RVector q = RVector::random(10000);
  hist(q,-3.0,3.0,100,"a.svg");
  return 0;
}
