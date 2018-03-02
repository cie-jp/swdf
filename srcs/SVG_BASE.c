/***************************************************************** 
 *
 * SVG BASE
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include<math.h>
#include"SVG_BASE.h"

void SVG_STYLE__SET_001(SVG_STYLE   style,
			const CHAR *opacity,          
			const CHAR *stroke,           
			const CHAR *stroke_width,			    
			const CHAR *stroke_dasharray,
			const CHAR *stroke_dashoffset,
			const CHAR *stroke_linecap,   
			const CHAR *stroke_linejoin,  
			const CHAR *fill){
  style[0] = '\0';
  sprintf(style,"%s" "opacity"          ":%s;",style,(opacity      != NULL) ? opacity      : "1.0"    );
  sprintf(style,"%s" "stroke"           ":%s;",style,(stroke       != NULL) ? stroke       : "#000000");
  sprintf(style,"%s" "stroke-width"     ":%s;",style,(stroke_width != NULL) ? stroke_width : "1.0px"  );
  if(stroke_dasharray  != NULL){sprintf(style,"%s" "stroke-dasharray"  ":%s;",style,stroke_dasharray );}
  if(stroke_dashoffset != NULL){sprintf(style,"%s" "stroke-dashoffset" ":%s;",style,stroke_dashoffset);}
  if(stroke_linecap    != NULL){sprintf(style,"%s" "stroke-linecap"    ":%s;",style,stroke_linecap   );}
  if(stroke_linejoin   != NULL){sprintf(style,"%s" "stroke-linejoin"   ":%s;",style,stroke_linejoin  );}
  sprintf(style,"%s" "fill"             ":%s;",style,(fill         != NULL) ? fill         : "#000000");
}

void SVG__HEADER (SVG        *svg){
  fprintf(svg->fp,
          "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
  fprintf(svg->fp,
          "<svg "
          "version=\"1.1\" "
          "xmlns=\"http://www.w3.org/2000/svg\" "
          "xmlns:xlink=\"http://www.w3.org/1999/xlink\" "
          "x=\"0px\" "
          "y=\"0px\" "
          "viewBox=\"0 0 %lf %lf\" "
          "style=\"enable-background:new 0 0 %lf %lf;\" "
          "xml:space=\"preserve\">\n",
          svg->width,svg->height,
          svg->width,svg->height);
}

void SVG__FOOTER (SVG        *svg){
  fprintf(svg->fp,
	  "</svg>\n");
}

void SVG__LINE   (SVG        *svg,
		  REAL8       X1,
		  REAL8       Y1,
		  REAL8       X2,
		  REAL8       Y2,
		  SVG__STYLE  style){
  fprintf(svg->fp,
          "<line "
          "style=\"%s\" "
          "x1=\"%lf\" "
          "y1=\"%lf\" "
          "x2=\"%lf\" "
          "y2=\"%lf\"/>\n",
          style,
          X1,svg->height - Y1,
          X2,svg->height - Y2);
}

void SVG__RECT   (SVG        *svg,
		  REAL8       X1,
		  REAL8       Y1,
		  REAL8       X2,
		  REAL8       Y2,
		  SVG__STYLE  style){
  REAL8 Xl,Xr,rectwidth ;
  REAL8 Yb,Yt,rectheight;
  
  if(X1 <= X2){
    Xl = X1;
    Xr = X2;
  }else{
    Xl = X2;
    Xr = X1;
  }
  if(Y1 <= Y2){
    Yb = Y1;
    Yt = Y2;
  }else{
    Yb = Y2;
    Yt = Y1;
  }
  
  rectwidth  = Xr - Xl;
  rectheight = Yt - Yb;
  
  fprintf(svg->fp,
          "<rect "
          "style=\"%s\" "
          "x=\"%lf\" "
          "y=\"%lf\" "
          "width=\"%lf\" "
          "height=\"%lf\"/>\n",
          style,
          Xl       ,svg->height - Yt,
          rectwidth, rectheight);
}

void SVG__ELLIPSE(SVG        *svg,
		  REAL8       X0,
		  REAL8       Y0,
		  REAL8       RX,
		  REAL8       RY,
		  SVG__STYLE  style){
  fprintf(svg->fp,
          "<ellipse "
          "style=\"%s\" "
          "cx=\"%lf\" "
          "cy=\"%lf\" "
          "rx=\"%lf\" "
          "ry=\"%lf\"/>\n",
          style,
          X0,svg->height - Y0,
	  RX,RY);
}

void SVG__POINT  (SVG        *svg,
		  REAL8       X0,
		  REAL8       Y0,
		  REAL8       pointsize,
		  INT4        pointtype,
		  SVG__STYLE  style){
  switch(pointtype){
  case 0:
    SVG__ELLIPSE(svg,X0,Y0,pointsize / 2.0,pointsize / 2.0,style);
    break;
  case 1:
    fprintf(svg->fp,
	    "<polygon style=\"%s\" points=\"%lf %lf,%lf %lf,%lf %lf\"/>",
	    style,
	    X0 - pointsize / 2.0 * 1.3,svg->height - (Y0 - pointsize * sqrt(3.0) / 4.0 * 1.3),
	    X0                        ,svg->height - (Y0 + pointsize * sqrt(3.0) / 4.0 * 1.3),
	    X0 + pointsize / 2.0 * 1.3,svg->height - (Y0 - pointsize * sqrt(3.0) / 4.0 * 1.3));
    break;
  case 2:
    SVG__RECT(svg,
	      X0 - pointsize / 2.0,Y0 - pointsize / 2.0,
	      X0 + pointsize / 2.0,Y0 + pointsize / 2.0,style);
    break;
  case 3:
    SVG__LINE(svg,
	      X0 - pointsize / 2.0,Y0 + pointsize / 2.0,
	      X0 + pointsize / 2.0,Y0 - pointsize / 2.0,
	      style);
    SVG__LINE(svg,
	      X0 - pointsize / 2.0,Y0 - pointsize / 2.0,
	      X0 + pointsize / 2.0,Y0 + pointsize / 2.0,
	      style);
    break;
  case 4:
    SVG__LINE(svg,
	      X0,Y0 + pointsize / 2.0,
	      X0,Y0 - pointsize / 2.0,
	      style);
    SVG__LINE(svg,
	      X0 - pointsize / 2.0,Y0,
	      X0 + pointsize / 2.0,Y0,
	      style);
    break;
  }
}

void SVG__FPUT   (CHAR        ch,
		  FILE       *fp,
		  REAL8       font_size,
		  INT4        texttype){
  if(texttype == 1){
    if(ch == 'x'){
      fprintf(fp,"<tspan font-size=\"%lfpx\"> × </tspan>",0.8 * font_size);
      return;
    }
    if(ch == '-'){
      fprintf(fp,"−");
      return;
    }
  }
  fputc(ch,fp);
}

void SVG__TEXT   (SVG        *svg,
		  REAL8       X0,
		  REAL8       Y0,
		  REAL8       angle,
		  const CHAR *text,
		  INT4        texttype,
		  const CHAR *font_family,
		  REAL8       font_size,
		  SVG_STYLE   style,
		  INT4        halign,
		  INT4        valign){
  REAL8      R11,R12;
  REAL8      R21,R22;
  REAL8      dy;
  SVG__STYLE style_ext;
  INT4       state;
  INT4       n;

  R11 =  cos(angle * M_PI / 180.0);
  R12 = -sin(angle * M_PI / 180.0);
  R21 =  sin(angle * M_PI / 180.0);
  R22 =  cos(angle * M_PI / 180.0);

  if(font_size < 1.0){
     font_size = 1.0;
  }
  sprintf(style_ext,
	  "%s" 
	  "font-family" ":'%s';"                                 "font-size"   ":%lfpx;",
	  style,
	  (font_family != NULL) ? font_family : "Times New Roman",font_size);
  switch(halign){
  case  0:sprintf(style_ext,"%s" "text-anchor" ":%s;",style_ext,"start" );break;
  case  1:sprintf(style_ext,"%s" "text-anchor" ":%s;",style_ext,"middle");break;
  case  2:sprintf(style_ext,"%s" "text-anchor" ":%s;",style_ext,"end"   );break;
  }
  switch(valign){
  case  0:dy = 0.00 * font_size;break;
  case  1:dy = 0.33 * font_size;break;
  case  2:dy = 0.73 * font_size;break;
  default:dy = 0.00 * font_size;
  }

  fprintf(svg->fp,
	  "<text "
	  "style=\"%s\" "
	  "dy=\"%lfpx\" "
	  "transform=\"matrix(%lf %lf %lf %lf %lf %lf)\">\n",
	  style_ext,
	  dy,
	  R11,R12,
	  R21,R22,
	  X0,svg->height - Y0);

  state = 0;
  for(n = 0;text[n] != '\0';n++){
    switch(state){
    case 0:
      if(text[n] == '^'){
	state = 1;
      }else 
      if(text[n] == '_'){
	state = 3;
      }else{
	SVG__FPUT(text[n],svg->fp,font_size,texttype);
      }
      break;
    case 1:
      if(text[n] == '{'){
	state = 2;
	fprintf(svg->fp,"<tspan baseline-shift=\"%lfpx\" font-size=\"%lfpx\">", 0.48 * font_size,0.585 * font_size);
      }else{
	state = 0;
	SVG__FPUT('^'    ,svg->fp,font_size,texttype);
	SVG__FPUT(text[n],svg->fp,font_size,texttype);
      }
      break;
    case 2:
      if(text[n] == '}'){
	state = 0;
	fprintf(svg->fp,"</tspan>");
      }else{
	SVG__FPUT(text[n],svg->fp,font_size,texttype);
      }
      break;
    case 3:
      if(text[n] == '{'){
	state = 4;
	fprintf(svg->fp,"<tspan baseline-shift=\"%lfpx\" font-size=\"%lfpx\">",-0.13 * font_size,0.585 * font_size);
      }else{
	state = 0;
	SVG__FPUT('_'    ,svg->fp,font_size,texttype);
	SVG__FPUT(text[n],svg->fp,font_size,texttype);
      }
      break;
    case 4:
      if(text[n] == '}'){
	state = 0;
	fprintf(svg->fp,"</tspan>");
      }else{
	SVG__FPUT(text[n],svg->fp,font_size,texttype);
      }
      break;
    }
  } 
  fprintf(svg->fp,
	  "</text>\n");
}

void SVG__IMAGE1 (SVG        *svg,
		  IMAGE       img,
		  INT4        imgwidth,
		  INT4        imgheight,
		  REAL8       X0,
		  REAL8       Y0,
		  INT4        alignment){
  REAL8 Xl;
  REAL8 Yb,Yt;

  switch(alignment){
  case 0:
    Xl = X0;
    Yb = Y0;
    break;
  case 1:
    Xl = X0 - imgwidth  * 0.5;
    Yb = Y0 - imgheight * 0.5;
    break;
  case 2:
    Xl = X0 - imgwidth ;
    Yb = Y0 - imgheight;
    break;
  default:
    Xl = X0;
    Yb = Y0;
  }
  Yt = Yb + imgheight;

  fprintf(svg->fp,
	  "<image style=\"overflow:visible;\" width=\"%d\" height=\"%d\" xlink:href=\"data:image/png;base64,",
	  imgwidth,imgheight);
  PNG__Output_BASE64(img,imgwidth,imgheight,svg->fp);
  fprintf(svg->fp,
	  "\" transform=\"matrix(%lf 0 0 %lf %lf %lf)\">\n",
	  1.0,
	  1.0,
	  Xl,svg->height - Yt);
  fprintf(svg->fp,
	  "</image>\n");
}

void SVG__IMAGE2 (SVG        *svg,
		  IMAGE       img,
		  INT4        imgwidth,
		  INT4        imgheight,
		  REAL8       X1,
		  REAL8       Y1,
		  REAL8       X2,
		  REAL8       Y2){
  REAL8 Xl,Xr,rectwidth ;
  REAL8 Yb,Yt,rectheight;

  if(X1 <= X2){
    Xl = X1;
    Xr = X2;
  }else{
    Xl = X2;
    Xr = X1;
  }
  if(Y1 <= Y2){
    Yb = Y1;
    Yt = Y2;
  }else{
    Yb = Y2;
    Yt = Y1;
  }
  rectwidth  = Xr - Xl;
  rectheight = Yt - Yb;

  fprintf(svg->fp,
	  "<image style=\"overflow:visible;\" width=\"%d\" height=\"%d\" xlink:href=\"data:image/png;base64,",
	  imgwidth,imgheight);
  PNG__Output_BASE64(img,imgwidth,imgheight,svg->fp);
  fprintf(svg->fp,
	  "\" transform=\"matrix(%lf 0 0 %lf %lf %lf)\">\n",
	  rectwidth  / imgwidth ,
	  rectheight / imgheight,
	  Xl,svg->height - Yt);
  fprintf(svg->fp,
	  "</image>\n");
}
