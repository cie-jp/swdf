using namespace CLDIA;

void setval(TMatrix<REAL8> &A,TMatrix<INT> M,REAL8 val){
  INT  i,j;

  for(i = 0;i < A.get_row();i++){
    for(j = 0;j < A.get_col();j++){
      if(M[i][j] == 1){
         A[i][j] =  val;
      }
    }
  }
}

TMatrix<REAL8> get_fce(TMatrix<REAL8> &mag){
  TMatrix<REAL8> fce(mag.get_row(),mag.get_col());
  INT            i,j;
  
  for(i = 0;i < fce.get_row();i++){
    for(j = 0;j < fce.get_col();j++){
      fce[i][j] = (mag[i][j] * 1.0e-9 * 1.6 * 1.0e-19) / (2.0 * M_PI * 9.1093e-31) / 1000.0;
    }
  }
  return fce;
}
TMatrix<REAL8> get_fce_half(TMatrix<REAL8> &mag){
  return RMatrix(get_fce(mag)) / 2.0;
}

class ERG_mgf{
private:
  TIME_TT2000 epoch_s;
  TIME_TT2000 epoch_e;
public:
  TMatrix<TIME_TT2000> epoch;
  TMatrix<REAL>        mag_gse;
public:
  ERG_mgf(STRING epoch_s,STRING epoch_e,STRING level,STRING version){
    DTIME         dtime_s;
    DTIME         dtime_e;
    TIME_TT2000   date;
    INT2          YYYY;
    INT1          MM;
    INT1          DD;
    STRING        filename;
    STRING        remotedir;
    STRING        remotepath;
    STRING        localdir;
    STRING        localpath;
    STRING        command;
    FILE         *fp;
    TMatrix<DATA> dat_epoch;
    TMatrix<DATA> dat_mag_gse;
    INT           isinit;

    isinit = 0;
    
    this->epoch_s = T2000__MAKE_FROM_TEXT(&epoch_s[0]);
    this->epoch_e = T2000__MAKE_FROM_TEXT(&epoch_e[0]);
    dtime_s       = DTIME__MAKE_FROM_T2000(this->epoch_s);
    dtime_e       = DTIME__MAKE_FROM_T2000(this->epoch_e);
    for(YYYY = dtime_s.YYYY;YYYY <= dtime_e.YYYY;YYYY++){
      for(MM = 1;MM <= 12;MM++){
        for(DD = 1;DD <= 31;DD++){
          date = CDF_TT2000_from_UTC_parts((double)YYYY,(double)MM,(double)DD,0.0,0.0,0.0,0.0,0.0,0.0);
          if(date == ILLEGAL_TT2000_VALUE){
            continue;
          }
          if((date < this->epoch_s) || (this->epoch_e < date)){
            continue;
          }
          filename   = STRING("erg_mgf_%s_8sec_%04d%02d%02d_v%s.00.cdf",&level[0],YYYY,MM,DD,&version[0]);
          remotedir  = "http://ergsc.isee.nagoya-u.ac.jp/data/ergsc/satellite/erg/mgf/" + level + "/" + "8sec" + "/" + STRING("%04d",YYYY) + "/";
          remotepath = remotedir + filename;
          localdir   = "./";
          localpath  =  localdir + filename;
          if((fp = fopen(&localpath[0],"rb")) == NULL){
            command = STRING("curl -L --anyauth --user erg_project:geospace -o %s %s",&localpath[0],&remotepath[0]);
            system(&command[0]);
          }else{
            fclose(fp);
          }
          Matrix__fetch(dat_epoch  ,"epoch_8sec",&localpath[0]);
          Matrix__fetch(dat_mag_gse,"mag_8sec_gse",&localpath[0]);
          if(!isinit){
            isinit = 1;
            epoch    = dat_epoch;
            mag_gse  = dat_mag_gse; 
          }else{
            epoch   &= dat_epoch;
            mag_gse &= dat_mag_gse; 
          }
        }
      }
    }
    setval(mag_gse,mag_gse < -99999.999,NAN);
  }
};
