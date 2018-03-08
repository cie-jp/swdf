/*****************************************************************
 *
 * HIST検証プログラム
 * 
 *
 *                           Created  by Mamoru Ota (2018/03/05)
 * 
 *****************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<SVG/SVGPLOT.h>

#define DAT_DIR "./test/dat/"

#define NUM     (9000)

int main(void){
  double x[NUM];
  int    n;

  for(n = 0;n < NUM;n++){
    x[n] = sin(0.001 * n);
  }
  
  SVGPLOT__HISTOGRAM(x,NUM,
                     -2.0,2.0,
                     100,
                     "x label",
                     "y label",
                     "title",
                     DAT_DIR "hist.svg");

  return 0;
}
