/*****************************************************************
 * 
 * CDF操作関連ライブラリ
 * 
 *    MRR共通 L1 z変数 
 *                  epoch : 時刻
 *                  H     : 高度
 *                  dH    : 高度分解能
 *                  V     : 鉛直ドップラー速度
 *                  dV    : 鉛直ドップラー速度分解能
 *                  TF    : 伝達関数
 *                  CC    : キャリブレーション定数
 *                  F     : レーダー反射率
 *                  F_sum : Fのドップラー速度に関する総和
 *                  MDQ   : MRRデータクオリティ
 *                  BW    : バンド幅
 * 
 *                           Modified by Mamoru Ota (2017/06/08)
 *                           Modified by Mamoru Ota (2017/06/06)
 *                           Created  by Mamoru Ota (2017/06/03)
 *
 *****************************************************************/ 

#include<time.h>
#include"CDF_L1_MRR.h"

extern void CDF_L1_MRR__Set_zVar_epoch(CDFid id);    
extern void CDF_L1_MRR__Set_zVar_H    (CDFid id);
extern void CDF_L1_MRR__Set_zVar_dH   (CDFid id);    
extern void CDF_L1_MRR__Set_zVar_V    (CDFid id);    
extern void CDF_L1_MRR__Set_zVar_dV   (CDFid id);    
extern void CDF_L1_MRR__Set_zVar_TF   (CDFid id);    
extern void CDF_L1_MRR__Set_zVar_CC   (CDFid id);
extern void CDF_L1_MRR__Set_zVar_F    (CDFid id);
extern void CDF_L1_MRR__Set_zVar_F_sum(CDFid id);
extern void CDF_L1_MRR__Set_zVar_MDQ  (CDFid id);
extern void CDF_L1_MRR__Set_zVar_BW   (CDFid id);

extern void CDF_L1_MRR__Set_Data_epoch(CDFid id,long recNum,CDF__TIME_TT2000 *value);
extern void CDF_L1_MRR__Set_Data_H    (CDFid id,long recNum,CDF__UINT2       *value);
extern void CDF_L1_MRR__Set_Data_dH   (CDFid id,long recNum,CDF__UINT1       *value);
extern void CDF_L1_MRR__Set_Data_V    (CDFid id,long recNum,CDF__REAL4       *value);    
extern void CDF_L1_MRR__Set_Data_dV   (CDFid id,long recNum,CDF__REAL4       *value);
extern void CDF_L1_MRR__Set_Data_TF   (CDFid id,long recNum,CDF__REAL4       *value);
extern void CDF_L1_MRR__Set_Data_CC   (CDFid id,long recNum,CDF__UINT4       *value);
extern void CDF_L1_MRR__Set_Data_F    (CDFid id,long recNum,CDF__UINT4       *value);
extern void CDF_L1_MRR__Set_Data_F_sum(CDFid id,long recNum,CDF__UINT4       *value);
extern void CDF_L1_MRR__Set_Data_MDQ  (CDFid id,long recNum,CDF__UINT1       *value);
extern void CDF_L1_MRR__Set_Data_BW   (CDFid id,long recNum,CDF__UINT2       *value);

void CDF_L1_MRR__Create   (CDFid      *id_ptr,
			   const char *filepath,
			   const char *data_version,
			   const char *device_name,
			   const char *device_version_number,
			   const char *device_serial_number){
  CDF__Create(id_ptr,filepath);
  CDF_L1_MRR__Set_gAttr(*id_ptr,
			filepath,
			data_version,
			device_name,
			device_version_number,
			device_serial_number);
  CDF_L1_MRR__Set_vAttr(*id_ptr);
  CDF_L1_MRR__Set_zVars(*id_ptr);
}

void CDF_L1_MRR__Set_gAttr(CDFid       id,
			   const char *logical_file_id,
			   const char *data_version,
			   const char *device_name,
			   const char *device_version_number,
			   const char *device_serial_number){
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

  CDF__Set_gAttr(id,"Discipline"           ,"Meteorology");
  CDF__Set_gAttr(id,"Project"              ,"Ground-based remote sensing for precipitation");
  CDF__Set_gAttr(id,"Source_name"          ,"Micro Rain Radar");
  CDF__Set_gAttr(id,"Data_type"            ,"L1>Level 1 Data");
  CDF__Set_gAttr(id,"Mission_group"        ,"Intelligent informatics lab. (Shiina lab.)");  
  CDF__Set_gAttr(id,"Descriptor"           ,".");
  CDF__Set_gAttr(id,"PI_name"              ,"Toru Shiina");
  CDF__Set_gAttr(id,"PI_affiliation"       ,"National Institute of Technology, Toyama College (Imizu Campus)");
  CDF__Set_gAttr(id,"Generated_by"         ,"Mamoru Ota");
  CDF__Set_gAttr(id,"Logical_file_id"      ,logical_file_id);
  CDF__Set_gAttr(id,"Generated_time"       ,gen_time);
  CDF__Set_gAttr(id,"Data_version"         ,data_version);
  CDF__Set_gAttr(id,"TITLE"                ,"MRR RawSpectra");
  CDF__Set_gAttr(id,"Device_name"          ,device_name);
  CDF__Set_gAttr(id,"Device_version_number",device_version_number);
  CDF__Set_gAttr(id,"Device_serial_number" ,device_serial_number);
  CDF__Set_gAttr(id,"Time_zone_information","UTC+09");
  CDF__Set_gAttr(id,"Time_resolution"      ,"10 seconds");
}

void CDF_L1_MRR__Set_vAttr(CDFid id){
  CDF__Set_vAttr(id,"FILLVAL"     );
  CDF__Set_vAttr(id,"VALIDMIN"    );
  CDF__Set_vAttr(id,"VALIDMAX"    );
  CDF__Set_vAttr(id,"CATDESC"     );
  CDF__Set_vAttr(id,"FIELDNAM"    );
  CDF__Set_vAttr(id,"VAR_TYPE"    );
  CDF__Set_vAttr(id,"VAR_NOTES"   );  
  CDF__Set_vAttr(id,"DICT_KEY"    );
  CDF__Set_vAttr(id,"MONOTON"     );
  CDF__Set_vAttr(id,"UNITS"       ); 
  CDF__Set_vAttr(id,"UNIT_PTR"    );
  CDF__Set_vAttr(id,"UNITS_PTR"   );
  CDF__Set_vAttr(id,"DEPEND_0"    );
  CDF__Set_vAttr(id,"DEPEND_1"    );
  CDF__Set_vAttr(id,"DEPEND_2"    );
  CDF__Set_vAttr(id,"DEPEND_3"    );
  CDF__Set_vAttr(id,"FORMAT"      );
  CDF__Set_vAttr(id,"FORM_PTR"    );
  CDF__Set_vAttr(id,"DISPLAY_TYPE");
  CDF__Set_vAttr(id,"SCALETYP"    );
  CDF__Set_vAttr(id,"LABLAXIS"    );
  CDF__Set_vAttr(id,"LABL_PTR_1"  );
  CDF__Set_vAttr(id,"LABL_PTR_2"  );
  CDF__Set_vAttr(id,"LABL_PTR_3"  );
  CDF__Set_vAttr(id,"BUNDLE_1"    );
}

void CDF_L1_MRR__Set_zVars(CDFid id){
  CDF_L1_MRR__Set_zVar_epoch(id);
  CDF_L1_MRR__Set_zVar_H    (id);
  CDF_L1_MRR__Set_zVar_dH   (id);
  CDF_L1_MRR__Set_zVar_V    (id);
  CDF_L1_MRR__Set_zVar_dV   (id);
  CDF_L1_MRR__Set_zVar_TF   (id);
  CDF_L1_MRR__Set_zVar_CC   (id);
  CDF_L1_MRR__Set_zVar_F    (id);
  CDF_L1_MRR__Set_zVar_F_sum(id);
  CDF_L1_MRR__Set_zVar_MDQ  (id);
  CDF_L1_MRR__Set_zVar_BW   (id);
}

void CDF_L1_MRR__Set_Data(CDF_L1_MRR__DATA *dat,CDFid id,long recNum){
  CDF_L1_MRR__Set_Data_epoch(id,recNum,&dat->epoch   );
  CDF_L1_MRR__Set_Data_H    (id,recNum,&dat->H[0]    );
  CDF_L1_MRR__Set_Data_dH   (id,recNum,&dat->dH      );
  CDF_L1_MRR__Set_Data_V    (id,recNum,&dat->V[0]    );
  CDF_L1_MRR__Set_Data_dV   (id,recNum,&dat->dV      );
  CDF_L1_MRR__Set_Data_TF   (id,recNum,&dat->TF[0]   );
  CDF_L1_MRR__Set_Data_CC   (id,recNum,&dat->CC      );
  CDF_L1_MRR__Set_Data_F    (id,recNum,&dat->F[0][0] );
  CDF_L1_MRR__Set_Data_F_sum(id,recNum,&dat->F_sum[0]);
  CDF_L1_MRR__Set_Data_MDQ  (id,recNum,&dat->MDQ     );
  CDF_L1_MRR__Set_Data_BW   (id,recNum,&dat->BW      );
}

void CDF_L1_MRR__Get_Data(CDF_L1_MRR__DATA *dat,CDFid id,long recNum){
  char     *varNames[] = {"epoch",
			  "H",
			  "dH",
			  "V",
			  "dV",
			  "TF",
			  "CC",
			  "F",
			  "F_sum",
			  "MDQ",
			  "BW"};
  void     *buffers [] = {&dat->epoch,
			  &dat->H[0],
			  &dat->dH,
			  &dat->V[0],
			  &dat->dV,
			  &dat->TF[0],
			  &dat->CC,
			  &dat->F[0][0],			  
			  &dat->F_sum[0],
			  &dat->MDQ,
			  &dat->BW};
  CDFstatus status;

  status = CDFgetzVarsRecordData(id,
				 11L,
				 varNames,
				 recNum,
				 buffers);  
  if(status != CDF_OK){
    CDF__Status_Handler(status);
  }
}
