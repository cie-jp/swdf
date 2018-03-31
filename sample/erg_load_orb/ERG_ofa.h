using namespace CLDIA;

class ERG_ofa{
private:
  TIME_TT2000 epoch_s;
  TIME_TT2000 epoch_e;
public:
  TMatrix<TIME_TT2000> epoch;
  TMatrix<REAL>        E_spectra;
  TMatrix<REAL>        freq;
public:
  ERG_ofa(STRING epoch_s,STRING epoch_e,STRING level,STRING version){
    STRING        datatype = "spec";
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
    TMatrix<DATA> dat_E_spectra;
    TMatrix<DATA> dat_freq;
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
          filename   = STRING("erg_pwe_ofa_%s_%s_%04d%02d%02d_v%s_01.cdf",&level[0],&datatype[0],YYYY,MM,DD,&version[0]);
          remotedir  = "http://ergsc.isee.nagoya-u.ac.jp/data/ergsc/satellite/erg/pwe/ofa/" + level + "/" + datatype + "/" + STRING("%04d",YYYY) + "/";          
          remotepath = remotedir + filename;
          localdir   = "./";
          localpath  =  localdir + filename;
          cerr << remotepath << endl;
          if((fp = fopen(&localpath[0],"rb")) == NULL){
            command = STRING("curl -L --anyauth --user erg_project:geospace -o %s %s",&localpath[0],&remotepath[0]);
            system(&command[0]);
          }else{
            fclose(fp);
          }
          Matrix__fetch(dat_epoch  ,"epoch_e132",&localpath[0]);
          Matrix__fetch(dat_E_spectra,"E_spectra_132",&localpath[0]);
          if(!isinit){
            isinit = 1;
            epoch    = dat_epoch;
            E_spectra  = dat_E_spectra;
            Matrix__fetch(dat_freq,"freq_e132",&localpath[0]);
            freq = dat_freq;
          }else{
            epoch   &= dat_epoch;
            E_spectra &= dat_E_spectra; 
          }
        }
      }
    }
    //setval(mag_gse,mag_gse < -99999.999,NAN);
  }
};
