class CDFData{
 public:
  TMatrix<DATA> variable;
  TMatrix<DATA> depend_0;
  TMatrix<DATA> depend_1;
  STRING        variable_name;
  STRING        depend_0_name;
  STRING        depend_1_name;
  STRING        variable_catdesc;
  STRING        depend_0_catdesc;
  STRING        depend_1_catdesc;
  STRING        variable_units;
  STRING        depend_0_units;
  STRING        depend_1_units;
  STRING        variable_label;
  STRING        depend_0_label;
  STRING        depend_1_label;
 private:
  STRING get_name(CDFid cdf_id,long var_id){
    CDFstatus status;
    char      varname[CDF_VAR_NAME_LEN256 + 1];

    status = CDFgetzVarName(cdf_id,var_id,varname);
    if(status != CDF_OK){
      cerr << "asd" << endl;
      CDF__Status_Handler(status);
    }
    return varname;
  }
  STRING get_catdesc(CDFid cdf_id,long var_id){
    CDFstatus   status;
    CDFMETADATA meta;
    STRING      varname;
    STRING      catdesc;

    varname = get_name(cdf_id,var_id);
    CDFMETADATA__INITIALIZE_ZVAR_ATTR(&meta,cdf_id,&varname[0],"CATDESC");
    catdesc = STRING(meta.numElems + 1,' ');
    memcpy(&catdesc[0],meta.buffer,meta.numElems);
    CDFMETADATA__FINALIZE(&meta);
    return catdesc;
  }
  STRING get_units(CDFid cdf_id,long var_id){
    CDFstatus   status;
    CDFMETADATA meta;
    STRING      varname;
    STRING      units;

    varname = get_name(cdf_id,var_id);
    CDFMETADATA__INITIALIZE_ZVAR_ATTR(&meta,cdf_id,&varname[0],"UNITS");
    units = STRING(meta.numElems + 1,' ');
    memcpy(&units[0],meta.buffer,meta.numElems);
    CDFMETADATA__FINALIZE(&meta);
    return units;
  }
 public:
  CDFData(STRING zvarname,
          STRING filename){
    long        variable_id;
    long        depend_0_id;
    long        depend_1_id;
    CDFid       id;
    CDFstatus   status;
    long        recNum;
    CDFMETADATA meta;
    INT4        i,j;
    
    recNum = CDF__Open(&id,&filename[0]);
    if(recNum < -1){
      return;
    }

    variable_id = CDFgetVarNum(id,(char*)&zvarname[0]);
    if(variable_id < CDF_OK){
      CDF__Status_Handler(variable_id);
    }
    
    CDFMETADATA__INITIALIZE_ZVAR_ATTR(&meta,id,&zvarname[0],"DEPEND_0");
    depend_0_name = STRING(meta.numElems + 1,' ');
    memcpy(&depend_0_name[0],(char*)meta.buffer,meta.numElems);
    depend_0_id = CDFgetVarNum(id,&depend_0_name[0]);
    CDFMETADATA__FINALIZE(&meta);
    
    CDFMETADATA__INITIALIZE_ZVAR_ATTR(&meta,id,&zvarname[0],"DEPEND_1");
    depend_1_name = STRING(meta.numElems + 1,' ');
    memcpy(&depend_1_name[0],(char*)meta.buffer,meta.numElems);
    depend_1_id = CDFgetVarNum(id,&depend_1_name[0]);
    CDFMETADATA__FINALIZE(&meta);    

    cerr << "HOGE" << endl;
    
    variable_name = get_name(id,variable_id);
    depend_0_name = get_name(id,depend_0_id);
    depend_1_name = get_name(id,depend_1_id);

    cerr << "PIYO" << endl;

    variable_catdesc = get_catdesc(id,variable_id);
    depend_0_catdesc = get_catdesc(id,depend_0_id);
    depend_1_catdesc = get_catdesc(id,depend_1_id);
    variable_units = get_units(id,variable_id);
    //depend_0_units = get_units(id,depend_0_id);
    depend_1_units = get_units(id,depend_1_id);
    //variable_units = ".";
    depend_0_units = ".";
    //depend_1_units = ".";
    
    variable_label = variable_catdesc + " [" + variable_units + "] ";
    depend_0_label = depend_0_catdesc + " [" + depend_0_units + "] ";
    depend_1_label = depend_1_catdesc + " [" + depend_1_units + "] ";
    
    CDF__Close(&id);

    Matrix__fetch(variable,&variable_name[0],&filename[0]);
    Matrix__fetch(depend_0,&depend_0_name[0],&filename[0]);
    Matrix__fetch(depend_1,&depend_1_name[0],&filename[0]);    
  }
};
