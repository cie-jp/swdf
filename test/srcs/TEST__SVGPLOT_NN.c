/*****************************************************************
 *
 * 3層ニューラルネットワークの描画
 * 
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<SVG/SVGPLOT.h>

#define DAT_DIR "./test/dat/"

#define UNIT_NUM1 (12)
#define UNIT_NUM2 (20)
#define UNIT_NUM3 (4)

REAL8 W12[UNIT_NUM1][UNIT_NUM2];
REAL8 W23[UNIT_NUM2][UNIT_NUM3];

void DRAW(SVGPLOT    *plt,
          const char *filename){
  SVG_STYLE style1;
  SVG_STYLE style2;
  SVG_STYLE style3;
  SVG_STYLE style12;
  SVG_STYLE style23;
  int       n1,n2,n3;
  REAL8     X1,Y1,Y1min,Y1max;
  REAL8     X2,Y2,Y2min,Y2max;
  REAL8     X3,Y3,Y3min,Y3max;
  REAL8     Xpos1 =  0.1;
  REAL8     Ypos1 =  0.6;
  REAL8     Xpos2 =  0.5;
  REAL8     Ypos2 =  0.9;
  REAL8     Xpos3 =  0.9;
  REAL8     Ypos3 =  0.3;
  REAL8     R     = 10.0;
  CHAR      stroke_width[1024];
  
  for(n1 = 0;n1 < UNIT_NUM1;n1++){
    for(n2 = 0;n2 < UNIT_NUM2;n2++){
      W12[n1][n2] = (REAL8)rand() / RAND_MAX;
    }
  }

  for(n2 = 0;n2 < UNIT_NUM2;n2++){
    for(n3 = 0;n3 < UNIT_NUM3;n3++){
      W23[n2][n3] = (REAL8)rand() / RAND_MAX;
    }
  }

  SVG_STYLE__SET_001(style1,
                     "1.0",     //opacity
                     "#51467F", //stroke
                     "1.0px",   //stroke_width
                     NULL,      //stroke_dasharray
                     NULL,      //stroke_dashoffset
                     NULL,      //stroke_linecap
                     NULL,      //stroke_linejoin
                     "#8170CB");//fill

  SVG_STYLE__SET_001(style2,
                     "1.0",     //opacity
                     "#7F303D", //stroke
                     "1.0px",   //stroke_width
                     NULL,      //stroke_dasharray
                     NULL,      //stroke_dashoffset
                     NULL,      //stroke_linecap
                     NULL,      //stroke_linejoin
                     "#F15A72");//fill

  SVG_STYLE__SET_001(style3,
                     "1.0",     //opacity
                     "#7F5A23", //stroke
                     "1.0px",   //stroke_width
                     NULL,      //stroke_dasharray
                     NULL,      //stroke_dashoffset
                     NULL,      //stroke_linecap
                     NULL,      //stroke_linejoin
                     "#FCB245");//fill

  SVGPLOT__INITIALIZE_002(plt,filename);

  X1   = plt->Xmin + Xpos1 * (plt->Xmax - plt->Xmin);
  Y1min = 0.5 * (plt->Ymin + plt->Ymax) - Ypos1 * 0.5 * (plt->Ymax - plt->Ymin);
  Y1max = 0.5 * (plt->Ymin + plt->Ymax) + Ypos1 * 0.5 * (plt->Ymax - plt->Ymin);

  X2   = plt->Xmin + Xpos2 * (plt->Xmax - plt->Xmin);
  Y2min = 0.5 * (plt->Ymin + plt->Ymax) - Ypos2 * 0.5 * (plt->Ymax - plt->Ymin);
  Y2max = 0.5 * (plt->Ymin + plt->Ymax) + Ypos2 * 0.5 * (plt->Ymax - plt->Ymin);

  X3   = plt->Xmin + Xpos3 * (plt->Xmax - plt->Xmin);
  Y3min = 0.5 * (plt->Ymin + plt->Ymax) - Ypos3 * 0.5 * (plt->Ymax - plt->Ymin);
  Y3max = 0.5 * (plt->Ymin + plt->Ymax) + Ypos3 * 0.5 * (plt->Ymax - plt->Ymin);

  for(n1 = 0;n1 < UNIT_NUM1;n1++){
    Y1 = Y1min + n1 / (double)(UNIT_NUM1 - 1) * (Y1max - Y1min);
    for(n2 = 0;n2 < UNIT_NUM2;n2++){
      Y2 = Y2min + n2 / (double)(UNIT_NUM2 - 1) * (Y2max - Y2min);
      sprintf(stroke_width,"%fpx",fabs(W12[n1][n2]));
      SVG_STYLE__SET_001(style12,
                         "1.0",     //opacity
                         "#51467F", //stroke
                         stroke_width,
                         NULL,      //stroke_dasharray
                         NULL,      //stroke_dashoffset
                         NULL,      //stroke_linecap
                         NULL,      //stroke_linejoin
                         "#8170CB");//fill
      SVG__LINE(&plt->svg,X1,Y1,X2,Y2,style12);
    }
  }

  for(n2 = 0;n2 < UNIT_NUM2;n2++){
    Y2 = Y2min + n2 / (double)(UNIT_NUM2 - 1) * (Y2max - Y2min);
    for(n3 = 0;n3 < UNIT_NUM3;n3++){
      Y3 = Y3min + n3 / (double)(UNIT_NUM3 - 1) * (Y3max - Y3min);
      sprintf(stroke_width,"%fpx",fabs(W23[n2][n3]));
      SVG_STYLE__SET_001(style23,
                         "1.0",     //opacity
                         "#7F303D", //stroke
                         stroke_width,
                         NULL,      //stroke_dasharray
                         NULL,      //stroke_dashoffset
                         NULL,      //stroke_linecap
                         NULL,      //stroke_linejoin
                         "#F15A72");//fill
      SVG__LINE(&plt->svg,X2,Y2,X3,Y3,style23);
    }
  }
  
  for(n1 = 0;n1 < UNIT_NUM1;n1++){
    Y1 = Y1min + n1 / (double)(UNIT_NUM1 - 1) * (Y1max - Y1min);
    SVG__ELLIPSE(&plt->svg,
                 X1,Y1,R,R,style1);
  }

  for(n2 = 0;n2 < UNIT_NUM2;n2++){
    Y2 = Y2min + n2 / (double)(UNIT_NUM2 - 1) * (Y2max - Y2min);
    SVG__ELLIPSE(&plt->svg,
                 X2,Y2,R,R,style2);
  }

  for(n3 = 0;n3 < UNIT_NUM3;n3++){
    Y3 = Y3min + n3 / (double)(UNIT_NUM3 - 1) * (Y3max - Y3min);
    SVG__ELLIPSE(&plt->svg,
                 X3,Y3,R,R,style3);
  }

  SVGPLOT__FINALIZE(plt);
}

int main(void){
  SVGPLOT plt;
  
  DRAW(&plt,DAT_DIR "NN.svg");

  return 0;
}
