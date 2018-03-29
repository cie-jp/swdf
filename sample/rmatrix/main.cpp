#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

class SVGPlot{
private:
  SVGPLOT plt;
public:
  SVGPlot(){
    SVGPLOT__INITIALIZE_002(&plt,"plot.svg");
  }
 ~SVGPlot(){
   SVGPLOT__FINALIZE(&plt);
  }
  void add(TMatrix<TIME_TT2000> epoch,TMatrix<REAL> var,const CHAR *label){
    SVGPLOT__ADD_BY_DAT_TY(&plt,epoch.get_dat(),var.get_dat(),epoch.get_row(),2,label);    
  }
  void timespan(const CHAR *ts,const CHAR *te){
    SVGPLOT__SET_RANGE_T_003(&plt,
                             T2000__MAKE_FROM_TEXT(ts),
                             T2000__MAKE_FROM_TEXT(te));
  }
  void plot(STRING xlabel,STRING ylabel,STRING title){
    SVGPLOT__PLOT_TY(&plt);
    
    SVGPLOT__TY_AUX(&plt,
                    1,1,1,1,
                    1,1,1,1,
                    1,0,1,0,
                    1);  
    SVGPLOT__XLABEL(&plt,"Time",NULL);
    SVGPLOT__YLABEL(&plt,"Orbit",NULL);
    SVGPLOT__TITLE (&plt,"ERG衛星予測軌道");
  }
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
  char          variable_catdesc[1024];
  char          depend_0_catdesc[1024];
  char          depend_1_catdesc[1024];
  char          variable_units[1024];
  char          depend_0_units[1024];
  char          depend_1_units[1024];
  STRING        variable_label;
  STRING        depend_0_label;
  STRING        depend_1_label;
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

    CDFMETADATA__INITIALIZE_ZVAR_ATTR(&meta,id,variable_name,"CATDESC");
    strcpy(variable_catdesc,(char*)meta.buffer);
    CDFMETADATA__FINALIZE(&meta);

    CDFMETADATA__INITIALIZE_ZVAR_ATTR(&meta,id,depend_0_name,"CATDESC");
    strcpy(depend_0_catdesc,(char*)meta.buffer);
    CDFMETADATA__FINALIZE(&meta);

    CDFMETADATA__INITIALIZE_ZVAR_ATTR(&meta,id,depend_1_name,"CATDESC");
    strcpy(depend_1_catdesc,(char*)meta.buffer);
    CDFMETADATA__FINALIZE(&meta);

    CDFMETADATA__INITIALIZE_ZVAR_ATTR(&meta,id,variable_name,"UNITS");
    strcpy(variable_units,(char*)meta.buffer);
    CDFMETADATA__FINALIZE(&meta);

    /*
    CDFMETADATA__INITIALIZE_ZVAR_ATTR(&meta,id,depend_0_name,"UNITS");
    strcpy(depend_0_units,(char*)meta.buffer);
    CDFMETADATA__FINALIZE(&meta);
    */
    strcpy(depend_0_units,".");

    CDFMETADATA__INITIALIZE_ZVAR_ATTR(&meta,id,depend_1_name,"UNITS");
    strcpy(depend_1_units,(char*)meta.buffer);
    CDFMETADATA__FINALIZE(&meta);

    variable_label = STRING(variable_catdesc) + " [" + STRING(variable_units) + "] ";
    depend_0_label = STRING(depend_0_catdesc) + " [" + STRING(depend_0_units) + "] ";
    depend_1_label = STRING(depend_1_catdesc) + " [" + STRING(depend_1_units) + "] ";
    
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
		  &depend_0_label[0],//x軸(下)
		  NULL);        //x軸(上)

  //y軸ラベルの設定  
  SVGPLOT__YLABEL(&plt,
		  &depend_1_label[0],//y軸(左)
		  NULL);        //y軸(右)
  
  //z軸ラベルの設定  
  SVGPLOT__ZLABEL(&plt,
		  &variable_label[0]);//z軸

  SVGPLOT__TITLE (&plt,"CDFPLOT");
}

};

//キャスト演算子
TMatrix<TIME_TT2000> cast_time(TMatrix<DATA> A){
  TMatrix<TIME_TT2000> C(A.get_row(),A.get_col());
  INT                  i,j;
  
  for(i = 0;i < A.get_row();i++){
    for(j = 0;j < A.get_col();j++){
      C[i][j] = A[i][j].data._time_tt2000;
    }
  }
  return C;
}

//キャスト演算子
TMatrix<REAL> cast(TMatrix<DATA> A){
  TMatrix<REAL> C(A.get_row(),A.get_col());
  INT           i,j;
  
  for(i = 0;i < A.get_row();i++){
    for(j = 0;j < A.get_col();j++){
      C[i][j] = DATA__GET(&A[i][j]);
    }
  }
  return C;
}

int main(int argc,char *argv[]){
  TMatrix<REAL> C(5,6);
  RMatrix A = RMatrix::random(3,4);
  RMatrix B;
  TMatrix<REAL> D;

  B = ~A;
  cerr << A << endl;
  cerr << B << endl;
  B = C;
  cerr << B << endl;
  D = A;
  cerr << D << endl;
  TMatrix<DATA> dat_epoch,dat_pos_gsm;
  TMatrix<TIME_TT2000> epoch;
  RMatrix       gsm,gsm0,gsm1,gsm2;

  Matrix__fetch(dat_epoch,"epoch","~/Desktop/erg_orb_pre_l2_20170101_v01.cdf");

  Matrix__fetch(dat_pos_gsm,"pos_gsm","~/Desktop/erg_orb_pre_l2_20170101_v01.cdf");
  cerr << (dat_epoch | dat_pos_gsm) << endl;
  epoch = cast_time(dat_epoch);
  gsm = cast(dat_pos_gsm);
  cerr << (gsm | 0) << endl;
  gsm0 = gsm | 0;
  gsm1 = gsm | 1;
  gsm2 = gsm | 2;

  SVGPlot plt;

  //plt.timespan("2017-01-01 12","2017-01-01 16");
  /*plt.add(epoch,gsm0,"GSM0");
  plt.add(epoch,gsm1,"GSM1");
  plt.add(epoch,gsm2,"GSM2");
  plt.plot("Time","Orbit","ERG衛星予測軌道");*/
  plt.cdfplot("E_spectra_132","~/Desktop/erg_pwe_ofa_l1_prime_e_spec_65khz_132pts_20180323_v06.cdf");
  return 0;
}
