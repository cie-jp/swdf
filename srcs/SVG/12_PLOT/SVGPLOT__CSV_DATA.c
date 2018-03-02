/***************************************************************** 
 *
 * SVGPLOT CSV DATA
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT.h"

void SVGPLOT__CSV_DATA(SVGPLOT    *plt,
		       FILE       *fp,
		       const CHAR *dep_entries,
		       const CHAR *var_entries,
		       const CHAR *legends,
		       INT4        mode){  
  TEXT_CSV    dep_csv;
  TEXT_CSV    var_csv;
  TEXT_CSV    leg_csv;
  INT4        dep_col;
  INT4        var_col;  
  INT4        dep_idx[TEXT_CSV__MAXNUM];
  INT4        var_idx[TEXT_CSV__MAXNUM];
  REAL8      *dep;
  REAL8      *var;
  TEXT_CSV    csv;
  INT8        pos;
  INT4        row;  
  void       *buf;
  INT4        n,k,l;
  const CHAR *lstroke;
  const CHAR *lstroke_width;
  const CHAR *lstroke_dasharray;
  REAL8       pointsize;
  INT4        pointtype;
  const CHAR *pstroke;
  const CHAR *pstroke_width;
  const CHAR *pstroke_dasharray;
  const CHAR *pfill;
  SVG_STYLE   style;
  REAL8       X1,X2,Y0;
  const CHAR *delimiters    = " \t,";
  const CHAR *comment_chars = "#@";

  TEXT_CSV__DECOMPOSITION(&leg_csv,    legends,delimiters);

  TEXT_CSV__DECOMPOSITION(&dep_csv,dep_entries,delimiters);
  dep_col = dep_csv.num;
  for(k = 0;k < dep_col;k++){
    dep_idx[k] = atoi(TEXT_CSV__GET_DATA(&dep_csv,k));
  }

  TEXT_CSV__DECOMPOSITION(&var_csv,var_entries,delimiters);
  var_col = var_csv.num;
  for(l = 0;l < var_col;l++){
    var_idx[l] = atoi(TEXT_CSV__GET_DATA(&var_csv,l));
  }
  
  row = TEXT_CSV__GET_NUM_ROWS(fp,comment_chars);

  if((buf = malloc(sizeof(REAL8) * (dep_col + var_col) * row)) == NULL){
    return;
  }

  dep = (REAL8*)buf;
  var = (REAL8*)&dep[dep_col * row];

  pos = ftell(fp);
  
  fseek(fp,0L ,SEEK_SET);

  for(n = 0;TEXT_CSV__READ_LINE(&csv,fp,delimiters,comment_chars) == 0;n++){
    for(k = 0;k < dep_col;k++){
      dep[k * row + n] = atof(TEXT_CSV__GET_DATA(&csv,dep_idx[k]));
      fprintf(stderr,"%e ",dep[k * row + n]);
    }
    for(l = 0;l < var_col;l++){
      var[l * row + n] = atof(TEXT_CSV__GET_DATA(&csv,var_idx[l]));
      fprintf(stderr,"%e ",var[l * row + n]);      
    }
    fprintf(stderr,"\n");
  }
  
  // ============================================================================
  // CSVデータをプロット
  // ============================================================================
  SVGPLOT__SET_RANGE_X_003(plt,
			   STATS__MIN(&dep[0],row,0),
			   STATS__MAX(&dep[0],row,0));

  SVGPLOT__SET_RANGE_Y_003(plt,
			   STATS__MIN(&var[0],var_col * row,0),
			   STATS__MAX(&var[0],var_col * row,0));
			   
  for(l = 0;l < var_col;l++){    
    switch(l){
    case 0:
      if(mode == 0){
	lstroke           = "#FF2800";
	lstroke_width     = "3.0px";
	lstroke_dasharray = NULL;
	pointsize         = 4.0;
	pointtype         = 0;
	pstroke           = lstroke;
	pstroke_width     = lstroke_width;
	pstroke_dasharray = NULL;      
	pfill             = pstroke;
      }else{
	lstroke           = "#000000";
	lstroke_width     = "2.0px";
	lstroke_dasharray = NULL;
	pointsize         = 6.0;
	pointtype         = 0;
	pstroke           = lstroke;
	pstroke_width     = "2.0px";
	pstroke_dasharray = NULL;      
	pfill             = "#FFFFFF";
      }
      break;
    case 1:
      if(mode == 0){
	lstroke           = "#0041FF";
	lstroke_width     = "3.0px";
	lstroke_dasharray = NULL;
	pointsize         = 4.0;
	pointtype         = 0;
	pstroke           = lstroke;
	pstroke_width     = lstroke_width;
	pstroke_dasharray = NULL;      
	pfill             = pstroke;
      }else{
	lstroke           = "#606060";
	lstroke_width     = "2.0px";
	lstroke_dasharray = "4,4";
	pointsize         = 6.0;
	pointtype         = 1;
	pstroke           = lstroke;
	pstroke_width     = "2.0px";
	pstroke_dasharray = NULL;      
	pfill             = "#FFFFFF";
      }
      break;
    case 2:
      if(mode == 0){
	lstroke           = "#35A16B";
	lstroke_width     = "3.0px";
	lstroke_dasharray = NULL;
	pointsize         = 4.0;
	pointtype         = 0;
	pstroke           = lstroke;
	pstroke_width     = lstroke_width;
	pstroke_dasharray = NULL;      
	pfill             = pstroke;
      }else{
	lstroke           = "#303030";
	lstroke_width     = "2.0px";
	lstroke_dasharray = "4,4";
	pointsize         = 6.0;
	pointtype         = 2;
	pstroke           = lstroke;
	pstroke_width     = "2.0px";
	pstroke_dasharray = NULL;      
	pfill             = "#FFFFFF";
      }
      break;
    case 3:
      lstroke           = "#FF9900";
      lstroke_width     = "3.0px";
      lstroke_dasharray = NULL;
      pointsize         = 4.0;
      pointtype         = 0;
      pstroke           = lstroke;
      pstroke_width     = lstroke_width;
      pstroke_dasharray = NULL;      
      pfill             = pstroke;
      break;
    case 4:
      lstroke           = "#66CCFF";
      lstroke_width     = "3.0px";
      lstroke_dasharray = NULL;
      pointsize         = 4.0;
      pointtype         = 0;
      pstroke           = lstroke;
      pstroke_width     = lstroke_width;
      pstroke_dasharray = NULL;      
      pfill             = pstroke;
      break;
    case 5:
      lstroke           = "#FF99A0";
      lstroke_width     = "3.0px";
      lstroke_dasharray = NULL;
      pointsize         = 4.0;
      pointtype         = 0;
      pstroke           = lstroke;
      pstroke_width     = lstroke_width;
      pstroke_dasharray = NULL;      
      pfill             = pstroke;
      break;
    case 6:
      lstroke           = "#9A0079";
      lstroke_width     = "3.0px";
      lstroke_dasharray = NULL;
      pointsize         = 4.0;
      pointtype         = 0;
      pstroke           = lstroke;
      pstroke_width     = lstroke_width;
      pstroke_dasharray = NULL;      
      pfill             = pstroke;
      break;
    case 7:
      lstroke           = "#663300";
      lstroke_width     = "3.0px";
      lstroke_dasharray = NULL;
      pointsize         = 4.0;
      pointtype         = 0;
      pstroke           = lstroke;
      pstroke_width     = lstroke_width;
      pstroke_dasharray = NULL;      
      pfill             = pstroke;
      break;
    default:
      lstroke           = "#000000";
      lstroke_width     = "3.0px";
      lstroke_dasharray = NULL;
      pointsize         = 4.0;
      pointtype         = 0;
      pstroke           = lstroke;
      pstroke_width     = lstroke_width;
      pstroke_dasharray = NULL;      
      pfill             = pstroke;
    }
    SVGPLOT__XY_LPLOT(plt,&dep[0],&var[l * row],row,-1.0,170.0,-1.0,0,
		      "1.0",lstroke,lstroke_width,lstroke_dasharray,NULL,"round","round");

    /*
    SVGPLOT__XY_IPLOT(plt,&dep[0],&var[l * row],row,
		      "1.0",lstroke,lstroke_width,lstroke_dasharray,NULL,"round","round");
    */

    /*
    SVGPLOT__XY_PPLOT(plt,&dep[0],&var[l * row],row,pointsize,pointtype,
		      "1.0",pstroke,pstroke_width,pstroke_dasharray,NULL,"butt","butt",pfill);
    */

    if(strlen(TEXT_CSV__GET_DATA(&leg_csv,l)) == 0){
      continue;
    }

    SVG_STYLE__SET_001(style,"1.0",lstroke,lstroke_width,lstroke_dasharray,NULL,"round","round","none");
    X1 = plt->Xmin + 50.0;
    X2 = X1        + 70.0;
    Y0 = plt->Ymax - plt->legendfont_size * (l + 1) * 1.5;
    SVG__LINE(&plt->svg,
	      X1,Y0,
	      X2,Y0,
	      style); 
    SVG_STYLE__SET_001(style,"1.0",pstroke,pstroke_width,pstroke_dasharray,NULL,"butt","butt",pfill);
    SVG__POINT(&plt->svg,(X1 + X2) / 2.0,Y0,pointsize,pointtype,style);
    SVG__TEXT(&plt->svg,
	      X2 + 20.0,Y0,0.0,
	      TEXT_CSV__GET_DATA(&leg_csv,l),0,plt->legendfont_family,plt->legendfont_size,plt->legendstyle,0,1);
  }

  fseek(fp,pos,SEEK_SET);

  free(buf);
  /*
  SVGPLOT__XY_AUX(plt,
                  1,1,1,1,
                  1,1,1,1,
                  1,0,1,0,
                  1);
  */
}

void SVGPLOT__CSV_FILE(SVGPLOT    *plt,
		       const CHAR *filename,
		       const CHAR *dep_entries,
		       const CHAR *var_entries,
		       const CHAR *legends,
		       INT4        mode){
  FILE *fp;

  if((fp = fopen(filename,"rb")) == NULL){
    fprintf(stderr,"NO FILE : %s\n",filename);
    return;
  }
  SVGPLOT__CSV_DATA(plt,fp,dep_entries,var_entries,legends,mode);
  fclose(fp);
}
