/*****************************************************************
 * 
 * CDF操作関連ライブラリ
 * 
 *                           Modified by Mamoru Ota (2017/12/12)
 *                           Modified by Mamoru Ota (2017/06/08)
 *                           Created  by Mamoru Ota (2017/06/03)
 *
 *****************************************************************/ 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"cdf.h"
#include"CDF_COMMON.h"

void CDF__Make_Directory(const char *dirname){
  char    command[10 + CDF_PATHNAME_LEN];
  sprintf(command,"mkdir -p %s",dirname);
  system (command);
}

void CDF__Status_Handler(CDFstatus status){
  char message[CDF_STATUSTEXT_LEN + 1];
  
  if(status < CDF_WARN){
    fprintf(stderr,"An error has occurred, halting...\n");
    CDFerror(status,message);
    fprintf(stderr,"%s\n",message);
    exit(status);
  }else{
    if(status < CDF_OK){
      fprintf(stderr,"Warning, function may not have completed as expected...\n");
      CDFerror(status,message);
      fprintf(stderr,"%s\n",message);      
    }else{
      if(status > CDF_OK){
	fprintf(stderr,"Function completed successfully, but be advised that...\n");
	CDFerror(status,message);
	fprintf(stderr,"%s\n",message);      	
      }
    }
  }
}

void CDF__Check_DataType(){
  CDFstatus status;
  long      numBytes;
  
  // *************************************************************************
  // CHAR
  // *************************************************************************
  if((status = CDFgetDataTypeSize((long)CDF_CHAR       ,&numBytes)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  if(sizeof(CDF__CHAR       ) != numBytes){
    fprintf(stderr,"sizeof(%s) !=  %2lu\n",TSTR(CDF__CHAR       ),numBytes);
    exit(EXIT_FAILURE);
  }
  // *************************************************************************
  // UCHAR
  // *************************************************************************
  if((status = CDFgetDataTypeSize((long)CDF_UCHAR      ,&numBytes)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  if(sizeof(CDF__UCHAR      ) != numBytes){
    fprintf(stderr,"sizeof(%s) !=  %2lu\n",TSTR(CDF__UCHAR      ),numBytes);
    exit(EXIT_FAILURE);
  }
  // *************************************************************************
  // BYTE
  // *************************************************************************
  if((status = CDFgetDataTypeSize((long)CDF_BYTE       ,&numBytes)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  if(sizeof(CDF__BYTE       ) != numBytes){
    fprintf(stderr,"sizeof(%s) !=  %2lu\n",TSTR(CDF__BYTE       ),numBytes);
    exit(EXIT_FAILURE);
  }
  // *************************************************************************
  // INT1
  // *************************************************************************
  if((status = CDFgetDataTypeSize((long)CDF_INT1       ,&numBytes)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  if(sizeof(CDF__INT1       ) != numBytes){
    fprintf(stderr,"sizeof(%s) !=  %2lu\n",TSTR(CDF__INT1       ),numBytes);
    exit(EXIT_FAILURE);
  }
  // *************************************************************************
  // INT2
  // *************************************************************************
  if((status = CDFgetDataTypeSize((long)CDF_INT2       ,&numBytes)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  if(sizeof(CDF__INT2       ) != numBytes){
    fprintf(stderr,"sizeof(%s) !=  %2lu\n",TSTR(CDF__INT2       ),numBytes);
    exit(EXIT_FAILURE);
  }
  // *************************************************************************
  // INT4
  // *************************************************************************
  if((status = CDFgetDataTypeSize((long)CDF_INT4       ,&numBytes)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  if(sizeof(CDF__INT4       ) != numBytes){
    fprintf(stderr,"sizeof(%s) !=  %2lu\n",TSTR(CDF__INT4       ),numBytes);
    exit(EXIT_FAILURE);
  }
  // *************************************************************************
  // INT8
  // *************************************************************************
  if((status = CDFgetDataTypeSize((long)CDF_INT8       ,&numBytes)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  if(sizeof(CDF__INT8       ) != numBytes){
    fprintf(stderr,"sizeof(%s) !=  %2lu\n",TSTR(CDF__INT8       ),numBytes);
    exit(EXIT_FAILURE);
  }
  // *************************************************************************
  // UINT1
  // *************************************************************************
  if((status = CDFgetDataTypeSize((long)CDF_UINT1      ,&numBytes)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  if(sizeof(CDF__UINT1      ) != numBytes){
    fprintf(stderr,"sizeof(%s) !=  %2lu\n",TSTR(CDF__UINT1      ),numBytes);
    exit(EXIT_FAILURE);
  }
  // *************************************************************************
  // UINT2
  // *************************************************************************
  if((status = CDFgetDataTypeSize((long)CDF_UINT2      ,&numBytes)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  if(sizeof(CDF__UINT2      ) != numBytes){
    fprintf(stderr,"sizeof(%s) !=  %2lu\n",TSTR(CDF__UINT2      ),numBytes);
    exit(EXIT_FAILURE);
  }
  // *************************************************************************
  // UINT4
  // *************************************************************************
  if((status = CDFgetDataTypeSize((long)CDF_UINT4      ,&numBytes)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  if(sizeof(CDF__UINT4      ) != numBytes){
    fprintf(stderr,"sizeof(%s) !=  %2lu\n",TSTR(CDF__UINT4      ),numBytes);
    exit(EXIT_FAILURE);
  }
  // *************************************************************************
  // FLOAT
  // *************************************************************************
  if((status = CDFgetDataTypeSize((long)CDF_FLOAT      ,&numBytes)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  if(sizeof(CDF__FLOAT      ) != numBytes){
    fprintf(stderr,"sizeof(%s) !=  %2lu\n",TSTR(CDF__FLOAT      ),numBytes);
    exit(EXIT_FAILURE);
  }
  // *************************************************************************
  // DOUBLE
  // *************************************************************************
  if((status = CDFgetDataTypeSize((long)CDF_DOUBLE     ,&numBytes)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  if(sizeof(CDF__DOUBLE     ) != numBytes){
    fprintf(stderr,"sizeof(%s) !=  %2lu\n",TSTR(CDF__DOUBLE     ),numBytes);
    exit(EXIT_FAILURE);
  }
  // *************************************************************************
  // REAL4
  // *************************************************************************
  if((status = CDFgetDataTypeSize((long)CDF_REAL4      ,&numBytes)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  if(sizeof(CDF__REAL4      ) != numBytes){
    fprintf(stderr,"sizeof(%s) !=  %2lu\n",TSTR(CDF__REAL4      ),numBytes);
    exit(EXIT_FAILURE);
  }
  // *************************************************************************
  // REAL8
  // *************************************************************************
  if((status = CDFgetDataTypeSize((long)CDF_REAL8      ,&numBytes)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  if(sizeof(CDF__REAL8      ) != numBytes){
    fprintf(stderr,"sizeof(%s) !=  %2lu\n",TSTR(CDF__REAL8      ),numBytes);
    exit(EXIT_FAILURE);
  }
  // *************************************************************************
  // EPOCH
  // *************************************************************************
  if((status = CDFgetDataTypeSize((long)CDF_EPOCH      ,&numBytes)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  if(sizeof(CDF__EPOCH      ) != numBytes){
    fprintf(stderr,"sizeof(%s) !=  %2lu\n",TSTR(CDF__EPOCH      ),numBytes);
    exit(EXIT_FAILURE);
  }
  // *************************************************************************
  // EPOCH16
  // *************************************************************************
  if((status = CDFgetDataTypeSize((long)CDF_EPOCH16    ,&numBytes)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  if(sizeof(CDF__EPOCH16    ) != numBytes){
    fprintf(stderr,"sizeof(%s) !=  %2lu\n",TSTR(CDF__EPOCH16    ),numBytes);
    exit(EXIT_FAILURE);
  }
  // *************************************************************************
  // TIME_TT2000
  // *************************************************************************
  if((status = CDFgetDataTypeSize((long)CDF_TIME_TT2000,&numBytes)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  if(sizeof(CDF__TIME_TT2000) != numBytes){
    fprintf(stderr,"sizeof(%s) !=  %2lu\n",TSTR(CDF__TIME_TT2000),numBytes);
    exit(EXIT_FAILURE);
  }
}

void CDF__Show_Library_Info(FILE *fp){
  CDFstatus status;
  char      copyright[CDF_COPYRIGHT_LEN + 1];
  long      version;
  long      release;
  long      increment;
  char      subIncrement;
  int       mode;
  int       validate;

  fprintf(fp,"*** CDF Library Information ***\n");
  // *************************************************************************
  // Copyright
  // *************************************************************************
  fprintf(fp,"--- Copyright --- \n");
  if((status = CDFgetLibraryCopyright(copyright)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  fprintf(fp,"%s\n",copyright);
  // *************************************************************************
  // Version
  // *************************************************************************
  if((status = CDFgetLibraryVersion(&version,&release,&increment,&subIncrement)) != CDF_OK){
    CDF__Status_Handler(status);    
  }
  fprintf(fp,"--- Version   --- \n");
  fprintf(fp,"V%ld.%ld.%ld %c\n",version,release,increment,subIncrement); 
  // *************************************************************************
  // File backward mode
  // *************************************************************************
  mode = CDFgetFileBackward();
  switch(mode){
  case BACKWARDFILEon :fprintf(fp,"Backward mode : on \n");break;
  case BACKWARDFILEoff:fprintf(fp,"Backward mode : off\n");break;
  default:             fprintf(fp,"Backward mode : %d \n",mode);
  }
  // *************************************************************************
  // Data validation
  // *************************************************************************
  validate = CDFgetValidate();
  switch(validate){
  case VALIDATEFILEon :fprintf(fp,"Data validation : on \n");break;
  case VALIDATEFILEoff:fprintf(fp,"Data validation : off\n");break;
  default:             fprintf(fp,"Data validation : %d \n",validate);
  }
}

void CDF__Show_Info(CDFid id,FILE *fp){
  CDFstatus status;
  char      filename[CDF_PATHNAME_LEN];
  long      numBuffers;
  long      checksum;
  long      compType;
  long      compParams[CDF_MAX_PARMS];
  long      compPercentage;
  char      copyright[CDF_COPYRIGHT_LEN + 1];
  long      lastUpdated;
  long      format;
  long      encoding;
  long      decoding;
  long      majority;
  long      version;
  long      release;
  long      increment;
  long      negtoPosfp0;
  long      readOnlyMode;
  long      zMode;
  int       mode;
  int       validate;

  fprintf(fp,"*** CDF Information ***\n");
  // *************************************************************************
  // File Name
  // *************************************************************************  
  if((status = CDFgetName(id,filename)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  fprintf(fp,"FileName : %s\n",filename);
  // *************************************************************************
  // Cache Size
  // *************************************************************************
  if((status = CDFgetCacheSize  (id,&numBuffers)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  fprintf(fp,"CacheSize : %ld\n",numBuffers);
  // *************************************************************************
  // Checksum
  // *************************************************************************
  if((status = CDFgetChecksum   (id,&checksum  )) != CDF_OK){
    CDF__Status_Handler(status);
  }
  switch(checksum){
  case NO_CHECKSUM: fprintf(fp,"Checksum mode :  NO_CHECKSUM\n");break;
  case MD5_CHECKSUM:fprintf(fp,"Checksum mode : MD5_CHECKSUM\n");break;
  default:          fprintf(fp,"Checksum mode : ????????????\n");
  }
  // *************************************************************************
  // Compression
  // *************************************************************************
  if((status = CDFgetCompression(id,&compType,compParams,&compPercentage)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  switch(compType){
  case    NO_COMPRESSION:fprintf(fp,"Compression : %s %3lu%%\n",   "NO_COMPRESSION" ,compPercentage);break;
  case   RLE_COMPRESSION:fprintf(fp,"Compression : %s %3lu%%\n",  "RLE_COMPRESSION" ,compPercentage);break;
  case  HUFF_COMPRESSION:fprintf(fp,"Compression : %s %3lu%%\n", "HUFF_COMPRESSION" ,compPercentage);break;
  case AHUFF_COMPRESSION:fprintf(fp,"Compression : %s %3lu%%\n","AHUFF_COMPRESSION" ,compPercentage);break;
  case  GZIP_COMPRESSION:fprintf(fp,"Compression : %s %3lu%%\n", "GZIP_COMPRESSION" ,compPercentage);
                         fprintf(fp,"            : The level of compression = %ld\n",compParams[0]);
    break;
  default:               fprintf(fp,"Compression : ?????????\n");
  }
  // *************************************************************************
  // Compression Cache Size
  // *************************************************************************
  if((status = CDFgetCompressionCacheSize(id,&numBuffers)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  fprintf(fp,"Compression CacheSize : %ld\n",numBuffers);
  // *************************************************************************
  // Copyright
  // *************************************************************************
  fprintf(fp,"Copyright\n");
  if((status = CDFgetCopyright(id,copyright)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  fprintf(fp,"%s\n",copyright);
  // *************************************************************************
  // Last date a new leap second was added
  // *************************************************************************
  if((status = CDFgetLeapSecondLastUpdated(id,&lastUpdated)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  fprintf(fp,"The last date a new leap second was added : %04ld/%02ld/%02ld\n",lastUpdated / 10000,(lastUpdated % 10000) / 100,lastUpdated % 100);
  // *************************************************************************
  // Format
  // *************************************************************************
  if((status = CDFgetFormat(id,&format)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  switch(format){
  case SINGLE_FILE:fprintf(fp,"Format : SINGLE_FILE\n");break;
  case  MULTI_FILE:fprintf(fp,"Format :  MULTI_FILE\n");break;
  default:         fprintf(fp,"Format : ???????????\n");      
  }
  // *************************************************************************
  // Encoding
  // *************************************************************************
  if((status = CDFgetEncoding(id,&encoding)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  switch(encoding){
  case       HOST_ENCODING:fprintf(fp,"Encoding : %s\n",      "HOST_ENCODING");break;
  case    NETWORK_ENCODING:fprintf(fp,"Encoding : %s\n",   "NETWORK_ENCODING");break;
  case        VAX_ENCODING:fprintf(fp,"Encoding : %s\n",       "VAX_ENCODING");break;
  case  ALPHAVMSd_ENCODING:fprintf(fp,"Encoding : %s\n", "ALPHAVMSd_ENCODING");break;
  case  ALPHAVMSg_ENCODING:fprintf(fp,"Encoding : %s\n", "ALPHAVMSg_ENCODING");break;
  case  ALPHAVMSi_ENCODING:fprintf(fp,"Encoding : %s\n", "ALPHAVMSi_ENCODING");break;
  case  ALPHAOSF1_ENCODING:fprintf(fp,"Encoding : %s\n", "ALPHAOSF1_ENCODING");break;
  case        SUN_ENCODING:fprintf(fp,"Encoding : %s\n",       "SUN_ENCODING");break;
  case        SGi_ENCODING:fprintf(fp,"Encoding : %s\n",       "SGi_ENCODING");break;
  case DECSTATION_ENCODING:fprintf(fp,"Encoding : %s\n","DECSTATION_ENCODING");break;
  case      IBMRS_ENCODING:fprintf(fp,"Encoding : %s\n",     "IBMRS_ENCODING");break;
  case      IBMPC_ENCODING:fprintf(fp,"Encoding : %s\n",     "IBMPC_ENCODING");break;
  case        PPC_ENCODING:fprintf(fp,"Encoding : %s\n",       "PPC_ENCODING");break;
  case         HP_ENCODING:fprintf(fp,"Encoding : %s\n",        "HP_ENCODING");break;
  case       NeXT_ENCODING:fprintf(fp,"Encoding : %s\n",      "NeXT_ENCODING");break;
  default:                 fprintf(fp,"Encoding : ??\n");
  }
  // *************************************************************************
  // Decoding
  // *************************************************************************
  if((status = CDFgetDecoding(id,&decoding)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  switch(decoding){
  case       HOST_DECODING:fprintf(fp,"Decoding : %s\n",      "HOST_DECODING");break;
  case    NETWORK_DECODING:fprintf(fp,"Decoding : %s\n",   "NETWORK_DECODING");break;
  case        VAX_DECODING:fprintf(fp,"Decoding : %s\n",       "VAX_DECODING");break;
  case  ALPHAVMSd_DECODING:fprintf(fp,"Decoding : %s\n", "ALPHAVMSd_DECODING");break;
  case  ALPHAVMSg_DECODING:fprintf(fp,"Decoding : %s\n", "ALPHAVMSg_DECODING");break;
  case  ALPHAVMSi_DECODING:fprintf(fp,"Decoding : %s\n", "ALPHAVMSi_DECODING");break;
  case  ALPHAOSF1_DECODING:fprintf(fp,"Decoding : %s\n", "ALPHAOSF1_DECODING");break;
  case        SUN_DECODING:fprintf(fp,"Decoding : %s\n",       "SUN_DECODING");break;
  case        SGi_DECODING:fprintf(fp,"Decoding : %s\n",       "SGi_DECODING");break;
  case DECSTATION_DECODING:fprintf(fp,"Decoding : %s\n","DECSTATION_DECODING");break;
  case      IBMRS_DECODING:fprintf(fp,"Decoding : %s\n",     "IBMRS_DECODING");break;
  case      IBMPC_DECODING:fprintf(fp,"Decoding : %s\n",     "IBMPC_DECODING");break;
  case        PPC_DECODING:fprintf(fp,"Decoding : %s\n",       "PPC_DECODING");break;
  case         HP_DECODING:fprintf(fp,"Decoding : %s\n",        "HP_DECODING");break;
  case       NeXT_DECODING:fprintf(fp,"Decoding : %s\n",      "NeXT_DECODING");break;
  default:                 fprintf(fp,"Decoding : ??\n");
  }
  // *************************************************************************
  // Variable majority
  // *************************************************************************
  if((status = CDFgetMajority(id,&majority)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  switch(majority){
  case    ROW_MAJOR:fprintf(fp,"Majority : %s\n",   "ROW_MAJOR");break;
  case COLUMN_MAJOR:fprintf(fp,"Majority : %s\n","COLUMN_MAJOR");break;
  default:          fprintf(fp,"Majority : ??\n");
  }
  // *************************************************************************
  // Version
  // *************************************************************************
  if((status = CDFgetVersion(id,&version,&release,&increment)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  fprintf(fp,"Version : %ld.%ld.%ld\n",version,release,increment);
  // *************************************************************************
  // NegtoPosfp0Mode
  // *************************************************************************
  if((status = CDFgetNegtoPosfp0Mode(id,&negtoPosfp0)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  switch(negtoPosfp0){
  case NEGtoPOSfp0on :fprintf(fp,"NEGtoPOSfp0 : on \n");break;
  case NEGtoPOSfp0off:fprintf(fp,"NEGtoPOSfp0 : off\n");break;
  default:            fprintf(fp,"NEGtoPOSfp0 : ?? \n");  
  }
  // *************************************************************************
  // readOnlyMode
  // *************************************************************************
  if((status = CDFgetReadOnlyMode(id,&readOnlyMode)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  switch(readOnlyMode){
  case READONLYon :fprintf(fp,"READONLY : on \n");break;
  case READONLYoff:fprintf(fp,"READONLY : off\n");break;
  default:         fprintf(fp,"READONLY : ?? \n");  
  }  
  // *************************************************************************
  // Stage Cache Size
  // *************************************************************************
  if((status = CDFgetStageCacheSize(id,&numBuffers)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  fprintf(fp,"StageCacheSize : %ld\n",numBuffers);
  // *************************************************************************
  // zMode
  // *************************************************************************
  if((status = CDFgetzMode(id,&zMode)) != CDF_OK){
    CDF__Status_Handler(status);
  }
  switch(zMode){
  case zMODEon1:fprintf(fp,"zMODE : on1\n");break;
  case zMODEon2:fprintf(fp,"zMODE : on2\n");break;
  case zMODEoff:fprintf(fp,"zMODE : off\n");break;
  default:      fprintf(fp,"zMODE : ?? \n");
  }
  // *************************************************************************
  // File backward mode
  // *************************************************************************
  mode = CDFgetFileBackward();
  switch(mode){
  case BACKWARDFILEon :fprintf(fp,"Backward mode : on \n");break;
  case BACKWARDFILEoff:fprintf(fp,"Backward mode : off\n");break;
  default:             fprintf(fp,"Backward mode : %d \n",mode);
  }
  // *************************************************************************
  // Data validation
  // *************************************************************************
  validate = CDFgetValidate();
  switch(validate){
  case VALIDATEFILEon :fprintf(fp,"Data validation : on \n");break;
  case VALIDATEFILEoff:fprintf(fp,"Data validation : off\n");break;
  default:             fprintf(fp,"Data validation : %d \n",validate);
  }
}

void CDF__Create(CDFid *id_ptr,const char *filename){
  CDFstatus status;

  status = CDFcreateCDF((char*)filename,id_ptr);
  if(status != CDF_OK){
    CDF__Status_Handler(status);
  }
  
  fprintf(stderr,"Create CDF file: %s\n", filename);
}

void CDF__Delete(CDFid *id_ptr){
  CDFstatus status;
  char      filename[CDF_PATHNAME_LEN];
  CDFid     id = *id_ptr;

  if(id == NULL){
    return;
  }
  status = CDFgetName(id,filename);
  if(status != CDF_OK){
    CDF__Status_Handler(status);
  }
  status = CDFdeleteCDF(id);
  if(status != CDF_OK){
    CDF__Status_Handler(status);
  }
  *id_ptr = NULL;

  fprintf(stderr,"Delete CDF file: %s\n",filename);
}

long CDF__Open(CDFid *id_ptr,const char *filename){
  CDFstatus status;
  long      recNum;

  status = CDFopenCDF((char*)filename,id_ptr);
  if(status == NO_SUCH_CDF){
    return -2;
  }
  if(status != CDF_OK){
    CDF__Status_Handler(status);
  }

  status = CDFgetzVarsMaxWrittenRecNum(*id_ptr,&recNum);
  if(status != CDF_OK){
    CDF__Status_Handler(status);
  }

  fprintf(stderr,"Open   CDF file: %s\n", filename);

  return recNum;
}

void CDF__Close(CDFid *id_ptr){
  CDFstatus status;
  char      filename[CDF_PATHNAME_LEN];
  CDFid     id = *id_ptr;

  if(id == NULL){
    return;
  }
  status = CDFgetName(id,filename);
  if(status != CDF_OK){
    CDF__Status_Handler(status);
  }
  status = CDFcloseCDF(id);
  if(status != CDF_OK){
    CDF__Status_Handler(status);
  }
  *id_ptr = NULL;

  fprintf(stderr,"Close  CDF file: %s.cdf\n",filename);
}

void CDF__Set_gAttr(CDFid id,const char *attrName,const char *text){
  CDFstatus status;
  long      attrNum;

  if((attrNum = CDFgetAttrNum(id,(char*)attrName)) < CDF_OK){
    status = CDFcreateAttr(id,attrName,GLOBAL_SCOPE,&attrNum);
    if(status != CDF_OK){
      CDF__Status_Handler(status);
    }        
  }
  
  status = CDFputAttrgEntry(id,attrNum,0L,CDF_CHAR,strlen(text),(void*)text);
  if(status != CDF_OK){
    CDF__Status_Handler(status);
  }      
}

void CDF__Set_gAttr_Generated_time(CDFid id){
  time_t           timer;
  struct tm       *gmt;
  CDF__TIME_TT2000 gen_epoch;
  char             gen_time[TT2000_3_STRING_LEN];

  time(&timer);
  gmt       = gmtime(&timer);
  gen_epoch = CDF_TT2000_from_UTC_parts((double)(gmt->tm_year +     1900),
					(double)(gmt->tm_mon  +        1),
					(double) gmt->tm_mday,
					(double) gmt->tm_hour,
					(double) gmt->tm_min,
					(double)(gmt->tm_sec  + 9 * 3600),
					TT2000END);
  CDF_TT2000_to_UTC_string(gen_epoch,gen_time,3);

  CDF__Set_gAttr(id,"Generated_time",gen_time);
}

void CDF__Get_gAttr(CDFid id,const char *attrName,      char *text,int text_len){
  CDFstatus status;
  long      dataType;
  long      numElems;
  CDFdata   gAttr;

  status = CDFreadgAttrEntry(id,CDFgetAttrNum(id,(char*)attrName),0L,&dataType,&numElems,&gAttr);
  if(status != CDF_OK){
    CDF__Status_Handler(status);
  }     
  if(dataType != CDF_CHAR){
    fprintf(stderr,"gAttr dataType != CDF_CHAR\n");
    exit(EXIT_FAILURE);
  }
  if(numElems  > text_len){
    fprintf(stderr,"gAttr numElems  > text_len\n");
  }
  memcpy(text,gAttr,text_len);
  CDFdataFree(gAttr);
}

int  CDF__Check_gAttr(CDFid id,const char *attrName,const char *text){
  CDFstatus status;
  long      dataType;
  long      numElems;
  CDFdata   gAttr;
  int       is_valid = 1;

  status = CDFreadgAttrEntry(id,CDFgetAttrNum(id,(char*)attrName),0L,&dataType,&numElems,&gAttr);
  if(status != CDF_OK){
    CDF__Status_Handler(status);
  }     
  if(dataType != CDF_CHAR){
    fprintf(stderr,"gAttr dataType != CDF_CHAR\n");
    exit(EXIT_FAILURE);
  }
  if(strcmp((char*)gAttr,text) != 0){
    is_valid = 0;
  }
  CDFdataFree(gAttr);
  return is_valid;
}

void CDF__Set_vAttr(CDFid id,const char *attrName){
  CDFstatus status;
  long      attrNum;

  status = CDFcreateAttr(id,attrName,VARIABLE_SCOPE,&attrNum);
  if(status != CDF_OK){
    CDF__Status_Handler(status);
  }
}

void CDF__Set_zVar_vAttr           (CDFid id,const char *varName,const char *attrName,void *value,long dataType,long elemNum){
  CDFstatus status;

  status = CDFputAttrzEntry(id,
			    CDFgetAttrNum(id,(char*)attrName),
			    CDFgetVarNum( id,(char*) varName),
			    dataType,
			    elemNum,
			    value);
  if(status != CDF_OK){
    CDF__Status_Handler(status);
  }  
}

void CDF__Set_zVar_vAttr_CHAR       (CDFid id,const char *varName,const char* attrName,CDF__CHAR         value){
  CDF__Set_zVar_vAttr(id,varName,attrName,      &value,CDF_CHAR       ,1L);
}

void CDF__Set_zVar_vAttr_CHARS      (CDFid id,const char *varName,const char* attrName,const CDF__CHAR  *value){
  CDF__Set_zVar_vAttr(id,varName,attrName,(void*)value,CDF_CHAR       ,strlen((const char*)value));
}

void CDF__Set_zVar_vAttr_UCHAR      (CDFid id,const char *varName,const char* attrName,CDF__UCHAR        value){
  CDF__Set_zVar_vAttr(id,varName,attrName,      &value,CDF_UCHAR      ,1L);
}

void CDF__Set_zVar_vAttr_UCHARS     (CDFid id,const char *varName,const char* attrName,const CDF__UCHAR *value){
  CDF__Set_zVar_vAttr(id,varName,attrName,(void*)value,CDF_UCHAR      ,strlen((const char*)value));
}

void CDF__Set_zVar_vAttr_BYTE       (CDFid id,const char *varName,const char* attrName,CDF__BYTE         value){
  CDF__Set_zVar_vAttr(id,varName,attrName,      &value,CDF_BYTE       ,1L);
}

void CDF__Set_zVar_vAttr_INT1       (CDFid id,const char *varName,const char* attrName,CDF__INT1         value){
  CDF__Set_zVar_vAttr(id,varName,attrName,      &value,CDF_INT1       ,1L);
}

void CDF__Set_zVar_vAttr_INT2       (CDFid id,const char *varName,const char* attrName,CDF__INT2         value){
  CDF__Set_zVar_vAttr(id,varName,attrName,      &value,CDF_INT2       ,1L);
}

void CDF__Set_zVar_vAttr_INT4       (CDFid id,const char *varName,const char* attrName,CDF__INT4         value){
  CDF__Set_zVar_vAttr(id,varName,attrName,      &value,CDF_INT4       ,1L);
}

void CDF__Set_zVar_vAttr_INT8       (CDFid id,const char *varName,const char* attrName,CDF__INT8         value){
  CDF__Set_zVar_vAttr(id,varName,attrName,      &value,CDF_INT8       ,1L);
}

void CDF__Set_zVar_vAttr_UINT1      (CDFid id,const char *varName,const char* attrName,CDF__UINT1        value){
  CDF__Set_zVar_vAttr(id,varName,attrName,      &value,CDF_UINT1      ,1L);
}

void CDF__Set_zVar_vAttr_UINT2      (CDFid id,const char *varName,const char* attrName,CDF__UINT2        value){
  CDF__Set_zVar_vAttr(id,varName,attrName,      &value,CDF_UINT2      ,1L);
}

void CDF__Set_zVar_vAttr_UINT4      (CDFid id,const char *varName,const char* attrName,CDF__UINT4        value){
  CDF__Set_zVar_vAttr(id,varName,attrName,      &value,CDF_UINT4      ,1L);
}

void CDF__Set_zVar_vAttr_FLOAT      (CDFid id,const char *varName,const char* attrName,CDF__FLOAT        value){
  CDF__Set_zVar_vAttr(id,varName,attrName,      &value,CDF_FLOAT      ,1L);
}

void CDF__Set_zVar_vAttr_DOUBLE     (CDFid id,const char *varName,const char* attrName,CDF__DOUBLE       value){
  CDF__Set_zVar_vAttr(id,varName,attrName,      &value,CDF_DOUBLE     ,1L);
}

void CDF__Set_zVar_vAttr_REAL4      (CDFid id,const char *varName,const char* attrName,CDF__REAL4        value){
  CDF__Set_zVar_vAttr(id,varName,attrName,      &value,CDF_REAL4      ,1L);
}

void CDF__Set_zVar_vAttr_REAL8      (CDFid id,const char *varName,const char* attrName,CDF__REAL8        value){
  CDF__Set_zVar_vAttr(id,varName,attrName,      &value,CDF_REAL8      ,1L);
}

void CDF__Set_zVar_vAttr_EPOCH      (CDFid id,const char *varName,const char* attrName,CDF__EPOCH        value){
  CDF__Set_zVar_vAttr(id,varName,attrName,      &value,CDF_EPOCH      ,1L);
}

void CDF__Set_zVar_vAttr_EPOCH16    (CDFid id,const char *varName,const char* attrName,CDF__EPOCH16      value){
  CDF__Set_zVar_vAttr(id,varName,attrName,      &value,CDF_EPOCH16    ,1L);
}

void CDF__Set_zVar_vAttr_TIME_TT2000(CDFid id,const char *varName,const char* attrName,CDF__TIME_TT2000  value){
  CDF__Set_zVar_vAttr(id,varName,attrName,      &value,CDF_TIME_TT2000,1L);
}

void CDF__Get_zVar_padValue         (CDFid id,const char *varName,void       *padValue){
  CDFstatus status;

  status = CDFgetzVarPadValue(id,CDFgetVarNum(id,(char*)varName),&padValue);
  if(status == NO_PADVALUE_SPECIFIED){
    CDF__Status_Handler(status);
  }
}

