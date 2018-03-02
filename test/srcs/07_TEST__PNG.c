/*****************************************************************
 *
 * PNGの動作検証
 * 
 *
 *                           Created  by Mamoru Ota (2018/01/25)
 * 
 *****************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"PNG.h"

#define DATDIR "./test/dat/"
#define OUTDIR "./test/out/"
#define OUTPNG OUTDIR "07_TEST__PNG.png"
#define OUTSVG OUTDIR "07_TEST__PNG.svg"

int main(void){
  int   WIDTH,HEIGHT;
  IMAGE img;
  FILE *fp;

  img = load_png(DATDIR "mrr1.png",&WIDTH,&HEIGHT);

  PNG__Output_File(img,WIDTH,HEIGHT,OUTPNG);

  fprintf(stderr,"CREATE : %s\n",OUTPNG);

  if((fp = fopen(OUTSVG,"w")) == NULL){
    return EXIT_FAILURE;
  }
  fprintf(fp,
          "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
  fprintf(fp,
          "<svg "
          "version=\"1.1\" "
          "id=\"canvas\" "
          "xmlns=\"http://www.w3.org/2000/svg\" "
          "xmlns:xlink=\"http://www.w3.org/1999/xlink\" "
          "x=\"0px\" "
          "y=\"0px\" "
          "viewBox=\"0 0 %d %d\" "
          "style=\"enable-background:new 0 0 %d %d;\" "
          "xml:space=\"preserve\">\n",
          2 * WIDTH,2 * HEIGHT,
          2 * WIDTH,2 * HEIGHT);
  fprintf(fp,"<image style=\"overflow:visible;\" width=\"%d\" height=\"%d\" xlink:href=\"data:image/png;base64,",WIDTH,HEIGHT);
  PNG__Output_BASE64(img,WIDTH,HEIGHT,fp);
  fprintf(fp,"\" transform=\"matrix(1 0 0 1 50 50)\">\n");
  fprintf(fp,"</image>\n");
  fprintf(fp,"</svg>\n");
  fclose(fp);

  free(img);

  fprintf(stderr,"CREATE : %s\n",OUTSVG);

  return EXIT_SUCCESS;
}
