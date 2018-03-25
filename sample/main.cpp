#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

//CDFstatus CDFgetzVarRangeRecordsByVarID(CDFid id,long varNum,long startRec,long stopRec,void *buffer);
//

void cdfplot(const CHAR *zvarname,
             const CHAR *filename){
  TMatrix<DATA> variable;
  TMatrix<DATA> depend_0;
  TMatrix<DATA> depend_1;
  TMatrix<REAL8>       variable_real8;
  TMatrix<TIME_TT2000> depend_0_time_tt2000;
  TMatrix<REAL8>       depend_1_real8;
  long          variable_id;
  long          depend_0_id;
  long          depend_1_id;
  char          variable_name[CDF_VAR_NAME_LEN256 + 1];
  char          depend_0_name[CDF_VAR_NAME_LEN256 + 1];
  char          depend_1_name[CDF_VAR_NAME_LEN256 + 1];
  // *******************************************************************************
  {
    CDFid       id;
    CDFstatus   status;
    long        recNum;
    CDFMETADATA meta;
    INT4        i,j;
    
    recNum = CDF__Open(&id,filename);
    if(recNum < -1){
      return;
    }

    variable_id = CDFgetVarNum(id,(char*)zvarname);
    
    CDFMETADATA__INITIALIZE_ZVAR_ATTR(&meta,id,zvarname,"DEPEND_0");
    depend_0_id = CDFgetVarNum(id,(char*)meta.buffer);
    CDFMETADATA__FINALIZE(&meta);
    
    CDFMETADATA__INITIALIZE_ZVAR_ATTR(&meta,id,zvarname,"DEPEND_1");
    depend_1_id = CDFgetVarNum(id,(char*)meta.buffer);
    CDFMETADATA__FINALIZE(&meta);

    status = CDFgetzVarName(id,variable_id,variable_name);
    if(status != CDF_OK){
      CDF__Status_Handler(status);
    }

    status = CDFgetzVarName(id,depend_0_id,depend_0_name);
    if(status != CDF_OK){
      CDF__Status_Handler(status);
    }
    
    status = CDFgetzVarName(id,depend_1_id,depend_1_name);
    if(status != CDF_OK){
      CDF__Status_Handler(status);
    }
    
    CDF__Close(&id);

    Matrix__fetch(variable,variable_name,filename);
    Matrix__fetch(depend_0,depend_0_name,filename);
    Matrix__fetch(depend_1,depend_1_name,filename);

    variable_real8       = TMatrix<REAL8>      (variable.get_row(),variable.get_col());
    depend_0_time_tt2000 = TMatrix<TIME_TT2000>(depend_0.get_row(),1);
    depend_1_real8       = TMatrix<REAL8>      (1,depend_1.get_col());

    for(i = 0;i < variable.get_row();i++){
      for(j = 0;j < variable.get_col();j++){
        variable_real8[i][j] = DATA__GET(&variable[i][j]);
      }
    }
    for(i = 0;i < variable.get_row();i++){
      depend_0_time_tt2000[i][0] = depend_0[i][0].data._time_tt2000;
    }
    for(j = 0;j < variable.get_col();j++){
      depend_1_real8[0][j] = DATA__GET(&depend_1[0][j]);
    }    
  }
  // *******************************************************************************

  SVGPLOT plt;
  
  SVGPLOT__INITIALIZE_002(&plt,"cdfplot.svg");
    
  SVGPLOT_PALETTE__Create10(&plt.pal);
  /*
  zmin = fmin(STATS__MIN(fxy_north,x_num * y_num,0),
              STATS__MIN(fxy_south,x_num * y_num,0));
  zmax = fmax(STATS__MAX(fxy_north,x_num * y_num,0),
              STATS__MAX(fxy_south,x_num * y_num,0));
  */
  //y軸のスケールタイプを設定
  SVGPLOT__SET_SCALETYPE_Y(&plt,
			   0);//0: 線形軸, 1: 対数軸

  SVGPLOT__SET_SCALETYPE_Y(&plt,
                           1);//0: 線形軸, 1: 対数軸

  SVGPLOT__SET_SCALETYPE_Z(&plt,
                           1);//0: 線形軸, 1: 対数軸
  //SVGPLOT__SET_RANGE_Z_003(&plt,1.0e-10,1.0);  
  
  SVGPLOT__TYZ_CONTOUR(&plt,
                       depend_0_time_tt2000.get_dat(),depend_0_time_tt2000.get_row(),
                       depend_1_real8      .get_dat(),depend_1_real8      .get_col(),
                       variable_real8      .get_dat(),
                       -1.0,//tgap
                       -1.0,//ygap
                       0);  //mode

  //グラフの目盛, 枠線を描画
  SVGPLOT__TY_AUX(&plt,
		  1,1,1,1,//グリッドの有無  (横軸大目盛,横軸小目盛,縦軸大目盛,縦軸小目盛)
		  1,1,1,1,//目盛(線)  の有無
		  1,0,1,0,//目盛(数値)の有無
		  1);     //枠線の有無
  
  SVGPLOT__COLORBAR(&plt,
                    1,1,
                    2,2,
                    2,0,
                    1);  

  //x軸ラベルの設定
  SVGPLOT__XLABEL(&plt,
		  depend_0_name,//x軸(下)
		  NULL);        //x軸(上)

  //y軸ラベルの設定  
  SVGPLOT__YLABEL(&plt,
		  depend_1_name,//y軸(左)
		  NULL);        //y軸(右)
  
  //z軸ラベルの設定  
  SVGPLOT__ZLABEL(&plt,
		  variable_name);//z軸

  SVGPLOT__TITLE (&plt,"CDFPLOT");
  
  SVGPLOT__FINALIZE(&plt);
}

/*
int main(int argc,char *argv[]){
  CDFid     id;
  CDFstatus status;
  long      recNum;

  if(argc <= 1){
    return 0;
  }
  recNum = CDF__Open(&id,argv[1]);
  if(recNum < -1){
    return -1;
  }
  CDF__SHOW_GATTRIBUTES(id,stderr);
  CDF__SHOW_RATTRIBUTES(id,stderr);
  CDF__SHOW_ZATTRIBUTES(id,stderr);

  CDFMETADATA meta;

  CDFMETADATA__INITIALIZE_ZVAR_ATTR(&meta,id,"Dv_histgram","DEPEND_0");
  CDFMETADATA__SHOW(&meta,stderr);
  CDFMETADATA__FINALIZE(&meta);

  CDFMETADATA__INITIALIZE_ZVAR_ATTR(&meta,id,"Dv_histgram","DEPEND_1");
  CDFMETADATA__SHOW(&meta,stderr);
  CDFMETADATA__FINALIZE(&meta);

  CDF__Close(&id);


  return 0;
}
*/

int main(int argc,char *argv[]){
  if(argc <= 1){
    return 0;
  }
  cdfplot("E_spectra_132",argv[1]);

  return 0;
}

/*
int main(){
  TMatrix<DATA> epoch;
  TMatrix<DATA> bscat;
  TMatrix<DATA> H;
  
  Matrix__fetch(epoch,"epoch"    ,"~/Desktop/ceilo_l1_20170825_v00.cdf");
  Matrix__fetch(bscat,"back_scat","~/Desktop/ceilo_l1_20170825_v00.cdf");
  Matrix__fetch(H    ,"H"        ,"~/Desktop/ceilo_l1_20170825_v00.cdf");


  show(epoch | (bscat | 0));
  show(H);
  return 0;
}
*/
