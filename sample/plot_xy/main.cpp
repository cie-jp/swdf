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
  void contour(RMatrix &variable,RVector &depend_0,RVector &depend_1){
    SVGPLOT__XYZ_CONTOUR(&plt,
                         &depend_0[0],depend_0.get_dim(),
                         &depend_1[0],depend_1.get_dim(),
                         &variable[0][0],
                         -1.0,-1.0,0);
    SVGPLOT__XY_AUX(&plt,
                    1,1,1,1,
                    1,1,1,1,
                    1,0,1,0,
                    1);
    SVGPLOT__COLORBAR(&plt,
                      1,1,
                      2,2,
                      2,0,
                      1);
  }
  void contour(RMatrix &variable,EVector &depend_0,RVector &depend_1){
    SVGPLOT__TYZ_CONTOUR(&plt,
                         &depend_0[0],depend_0.get_dim(),
                         &depend_1[0],depend_1.get_dim(),
                         &variable[0][0],
                         -1.0,-1.0,0);
    SVGPLOT__TY_AUX(&plt,
                    1,1,1,1,
                    1,1,1,1,
                    1,0,1,0,
                    1);
    SVGPLOT__COLORBAR(&plt,
                      1,1,
                      2,2,
                      2,0,
                      1);
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
  void lplot(EVector &x,RVector &y){
    if(x.get_dim() != y.get_dim()){
      ERROR__SHOW("x.dim != y.dim");
      exit(EXIT_FAILURE);
    }
    SVGPLOT__TY_LPLOT(&plt,
                      x.get_dat(),
                      y.get_dat(),
                      x.get_dim(),
                      -1.0,-1.0,0,
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

  void pplot(EVector &x,RVector &y){    
    if(x.get_dim() != y.get_dim()){
      ERROR__SHOW("x.dim != y.dim");
      exit(EXIT_FAILURE);
    }
    SVGPLOT__TY_PPLOT(&plt,
                      x.get_dat(),y.get_dat(),x.get_dim(),
                      2.0,
                      0,
                      "1.0","#000000","0.5px",NULL,NULL,"round","round","#FF0000");
  }

  void auxx(){
    SVGPLOT__XY_AUX(&plt,
                    1,1,1,1,
                    3,3,3,3,
                    1,2,1,2,
                    1);
  }
  void auxt(){
    SVGPLOT__TY_AUX(&plt,
                    1,1,1,1,
                    3,3,3,3,
                    1,2,1,2,
                    1);
  }

  ~plot(){
    SVGPLOT__FINALIZE(&plt);
  }
};

void test(){
  EVector t = linspace("2017-01-01","2017-02-01",TIME_TT2000__HOUR);
  RVector x = linspace(0.0,10.0,t.get_dim());
  RVector y = linspace(3.0, 5.0, 100);
  RMatrix z = x * ~y;
  plot    p;

  p.contour(z,t,y);  
}

int main(int argc,char *argv[]){
  /*RMatrix A = RMatrix::random(4,1);
  RVector a = A;
  RVector b = RMatrix::random(4,1);
  RVector c = A + A;
  RVector d;
  cerr << c << endl;
  cerr << d << endl;
  cerr << c << endl;
  c = A + A;
  cerr << c << endl;
  c = d;*/
  //RMatrix A(5,2);
  RMatrix A = RMatrix::random(7,2);

  cerr << A << endl;
  RVector b;
  b = A;
  cerr << b << endl;
  b = ~b;
  cerr << b << endl;
  
  //cerr << A << endl;
  //RMatrix B = RMatrix::random(4,1);
  //B = A + A;
  //test();
  /*  RVector x = linspace(1.0,3.0,1000);
  RVector y = RVector::random(1000);
  RMatrix z = x;
  plot p;

  p.lplot(x,y);
  p.pplot(x,y);  
  p.auxx();
  
  cerr << (x | y) << endl;
  cerr << linspace("2017-01-01","2017-02-01",TIME_TT2000__DAY) << endl;

  RVector q = RVector::random(10000);
  hist(q,-3.0,3.0,100,"a.svg");

  EVector t = linspace("2017-01-01","2017-02-01",TIME_TT2000__DAY);
  RVector u = RVector::random(t.get_dim());

  p.lplot(t,u);
  p.pplot(t,u);
  p.auxt();*/
  return 0;
}
