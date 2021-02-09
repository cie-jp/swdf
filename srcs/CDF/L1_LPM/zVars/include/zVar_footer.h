#define Set_zVar_(_varName_)       JOINT(JOINT(NAMESPACE,__Set_zVar_),_varName_)
#define Set_Data_(_varName_)       JOINT(JOINT(NAMESPACE,__Set_Data_),_varName_)

#define Set_zVar_vAttr_(_varType_) JOINT(CDF__Set_zVar_vAttr_,_varType_)

#define Get_DataType1(_varType_)   Get_DataType0(_varType_)
#define Get_DataType0(_varType_)           CDF_##_varType_ 

#ifdef SUFFIX
#define funcName JOINT(varName,SUFFIX)
#else
#define funcName varName
#endif

//#define DEBUG 

void Set_zVar_(funcName)(CDFid id){
  const long numE    = numElems   ;
  const long numD    = numDims    ;
  const long dimS[3] = dimSizes   ;
  const long dimV[3] = dimVarys   ;
  const long recV    = recVariance;
  CDFstatus  status;
  long       varNum;

#ifdef DEBUG
  fprintf(stderr,"Create zVariable [%30s : %30s]\n",TSTR(varName),TSTR(varType));
#endif
  status = CDFcreatezVar( id,
			  TSTR(varName),
			  Get_DataType1(varType),
			  numE,
			  numD,
			 (numD != 0L) ? dimS : NULL,
			  recV,
			 (numD != 0L) ? dimV : NULL,
			 &varNum);
  if(status != CDF_OK){
    CDF__Status_Handler(status);
  }
#ifdef DEBUG
  fprintf(stderr," + numElems = %4ld, numDims = %4ld [%5ld(%s):%5ld(%s):%5ld(%s)] Record(%s)\n",
	  numE,
	  numD,
	  dimS[0],(dimV[0] == VARY) ? "  VARY" : "NOVARY",
	  dimS[1],(dimV[1] == VARY) ? "  VARY" : "NOVARY",
	  dimS[2],(dimV[2] == VARY) ? "  VARY" : "NOVARY",
	          (recV    == VARY) ? "  VARY" : "NOVARY");
#endif

#ifdef COMPRESS
  long        cType;
  long        cParms[CDF_MAX_PARMS];

  cType     = GZIP_COMPRESSION;
  cParms[0] = 6L;
  status = CDFsetzVarCompression(id,varNum,cType,cParms);  
  if(status != CDF_OK){
    CDF__Status_Handler(status);
  }
#endif

#ifdef FILLVAL
  const JOINT(CDF__,varType) padValue = FILLVAL; 

  status = CDFsetzVarPadValue(id,varNum,&padValue);
  if(status != CDF_OK){
    CDF__Status_Handler(status);
  }  
#endif

#ifdef SPARSE_PAD
  status = CDFsetzVarSparseRecords(id,varNum,PAD_SPARSERECORDS);
  if(status != CDF_OK){
    CDF__Status_Handler(status);
  }
#endif

#ifdef FILLVAL  
  Set_zVar_vAttr_(varType)(id,TSTR(varName),ISTR(FILLVAL)     ,FILLVAL     );
#endif
#ifdef VALIDMIN 
  Set_zVar_vAttr_(varType)(id,TSTR(varName),ISTR(VALIDMIN)    ,VALIDMIN    );
#endif
#ifdef VALIDMAX
  Set_zVar_vAttr_(varType)(id,TSTR(varName),ISTR(VALIDMAX)    ,VALIDMAX    );
#endif
#ifdef CATDESC
  Set_zVar_vAttr_(CHARS)  (id,TSTR(varName),ISTR(CATDESC)     ,CATDESC     );
#endif
#ifdef FIELDNAM
  Set_zVar_vAttr_(CHARS)  (id,TSTR(varName),ISTR(FIELDNAM)    ,FIELDNAM    );
#endif
#ifdef VAR_TYPE
  Set_zVar_vAttr_(CHARS)  (id,TSTR(varName),ISTR(VAR_TYPE)    ,VAR_TYPE    );
#endif
#ifdef VAR_NOTES
  Set_zVar_vAttr_(CHARS)  (id,TSTR(varName),ISTR(VAR_NOTES)   ,VAR_NOTES   );
#endif
#ifdef DICT_KEY
  Set_zVar_vAttr_(CHARS)  (id,TSTR(varName),ISTR(DICT_KEY)    ,DICT_KEY    );
#endif
#ifdef MONOTON
  Set_zVar_vAttr_(CHARS)  (id,TSTR(varName),ISTR(MONOTON)     ,MONOTON     );
#endif
#ifdef UNITS
  Set_zVar_vAttr_(CHARS)  (id,TSTR(varName),ISTR(UNITS)       ,UNITS       );
#endif
#ifdef UNIT_PTR
  Set_zVar_vAttr_(CHARS)  (id,TSTR(varName),ISTR(UNIT_PTR)    ,UNIT_PTR    );
#endif
#ifdef UNITS_PTR
  Set_zVar_vAttr_(CHARS)  (id,TSTR(varName),ISTR(UNITS_PTR)   ,UNITS_PTR   );
#endif
#ifdef DEPEND_0
  Set_zVar_vAttr_(CHARS)  (id,TSTR(varName),ISTR(DEPEND_0)    ,DEPEND_0    );
#endif
#ifdef DEPEND_1
  Set_zVar_vAttr_(CHARS)  (id,TSTR(varName),ISTR(DEPEND_1)    ,DEPEND_1    );
#endif
#ifdef DEPEND_2
  Set_zVar_vAttr_(CHARS)  (id,TSTR(varName),ISTR(DEPEND_2)    ,DEPEND_2    );
#endif
#ifdef DEPEND_3
  Set_zVar_vAttr_(CHARS)  (id,TSTR(varName),ISTR(DEPEND_3)    ,DEPEND_3    );
#endif
#ifdef FORMAT
  Set_zVar_vAttr_(CHARS)  (id,TSTR(varName),ISTR(FORMAT)      ,FORMAT      );
#endif
#ifdef FORM_PTR
  Set_zVar_vAttr_(CHARS)  (id,TSTR(varName),ISTR(FORM_PTR)    ,FORM_PTR    );
#endif
#ifdef DISPLAY_TYPE
  Set_zVar_vAttr_(CHARS)  (id,TSTR(varName),ISTR(DISPLAY_TYPE),DISPLAY_TYPE);
#endif
#ifdef SCALETYP
  Set_zVar_vAttr_(CHARS)  (id,TSTR(varName),ISTR(SCALETYP)    ,SCALETYP    );
#endif
#ifdef LABLAXIS
  Set_zVar_vAttr_(CHARS)  (id,TSTR(varName),ISTR(LABLAXIS)    ,LABLAXIS    );
#endif
#ifdef LABL_PTR_1
  Set_zVar_vAttr_(CHARS)  (id,TSTR(varName),ISTR(LABL_PTR_1)  ,LABL_PTR_1  );
#endif
#ifdef LABL_PTR_2
  Set_zVar_vAttr_(CHARS)  (id,TSTR(varName),ISTR(LABL_PTR_2)  ,LABL_PTR_2  );
#endif
#ifdef LABL_PTR_3
  Set_zVar_vAttr_(CHARS)  (id,TSTR(varName),ISTR(LABL_PTR_3)  ,LABL_PTR_3  );
#endif
#ifdef BUNDLE_1
  Set_zVar_vAttr_(CHARS)  (id,TSTR(varName),ISTR(BUNDLE_1)    ,BUNDLE_1    );
#endif
}

void Set_Data_(funcName)(CDFid                 id,
		 	 long                  recNum,
		 	 JOINT(CDF__,varType) *value){
  CDFstatus status;

  status = CDFputzVarRecordData(id,
				CDFgetVarNum(id,(char*)TSTR(varName)),
				recNum,
				value);
  if(status != CDF_OK){
#ifdef DEBUG
  fprintf(stderr,"Set zVariable [%30s : %30s]\n",TSTR(varName),TSTR(varType));
#endif  
    CDF__Status_Handler(status);
  }
}
