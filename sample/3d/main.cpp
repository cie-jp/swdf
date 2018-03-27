#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

#include"test.h"

int main(int argc,char *argv[]){
  SVGPLOT plt;

  SVGPLOT__INITIALIZE_002(&plt,"3d.svg");


  SVG__RECT(&plt.svg,plt.Xmin,plt.Ymin,plt.Xmax,plt.Ymax,plt.borderstyle);

  aacontour(&plt);
  //DRAW_BORDER(&plt);
  SVGPLOT__FINALIZE(&plt);
    
  return 0;
}
