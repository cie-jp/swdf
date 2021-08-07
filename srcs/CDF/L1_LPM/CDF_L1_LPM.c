/********************************************************************************************************
 *
 * CDF操作関連ライブラリ
 *
 *    LPM共通 L1 z変数
 *               20 21 epoch                       : センサの時間,日時                     (hh:mm:ss)(DD.MM.YYYY)
 *                  93 Dv_histgram[32][32]         : 生データ                              (***;     | 000      ~   999    ) x 32 x 32
 *
 *******************************************************************************************************/

#include"CDF_L1_LPM.h"

extern void CDF_L1_LPM__Set_zVar_epoch                     (CDFid id);
extern void CDF_L1_LPM__Set_zVar_R                         (CDFid id);
extern void CDF_L1_LPM__Set_zVar_R_liquid                  (CDFid id);
extern void CDF_L1_LPM__Set_zVar_R_solid                   (CDFid id);
extern void CDF_L1_LPM__Set_zVar_Z                         (CDFid id);
extern void CDF_L1_LPM__Set_zVar_N                         (CDFid id);
extern void CDF_L1_LPM__Set_zVar_ND                        (CDFid id);
extern void CDF_L1_LPM__Set_zVar_Nv                        (CDFid id);
extern void CDF_L1_LPM__Set_zVar_Dv_histgram               (CDFid id);
extern void CDF_L1_LPM__Set_zVar_D                         (CDFid id);
extern void CDF_L1_LPM__Set_zVar_dD                        (CDFid id);
extern void CDF_L1_LPM__Set_zVar_v                         (CDFid id);
extern void CDF_L1_LPM__Set_zVar_dv                        (CDFid id);
extern void CDF_L1_LPM__Set_zVar_weathercode_rain          (CDFid id);
extern void CDF_L1_LPM__Set_zVar_weathercode_snow          (CDFid id);
extern void CDF_L1_LPM__Set_zVar_weathercode_intensity     (CDFid id);

extern void CDF_L1_LPM__Set_Data_epoch                     (CDFid id,long recNum,CDF__TIME_TT2000 *value);
extern void CDF_L1_LPM__Set_Data_R                         (CDFid id,long recNum,CDF__REAL4 *value);
extern void CDF_L1_LPM__Set_Data_R_liquid                  (CDFid id,long recNum,CDF__REAL4 *value);
extern void CDF_L1_LPM__Set_Data_R_solid                   (CDFid id,long recNum,CDF__REAL4 *value);
extern void CDF_L1_LPM__Set_Data_Z                         (CDFid id,long recNum,CDF__REAL4 *value);
extern void CDF_L1_LPM__Set_Data_N                         (CDFid id,long recNum,CDF__UINT2 *value);
extern void CDF_L1_LPM__Set_Data_ND                        (CDFid id,long recNum,CDF__UINT2 *value);
extern void CDF_L1_LPM__Set_Data_Nv                        (CDFid id,long recNum,CDF__UINT2 *value);
extern void CDF_L1_LPM__Set_Data_Dv_histgram               (CDFid id,long recNum,CDF__UINT2 *value);
extern void CDF_L1_LPM__Set_Data_D                         (CDFid id,long recNum,CDF__REAL4 *value);
extern void CDF_L1_LPM__Set_Data_dD                        (CDFid id,long recNum,CDF__REAL4 *value);
extern void CDF_L1_LPM__Set_Data_v                         (CDFid id,long recNum,CDF__REAL4 *value);
extern void CDF_L1_LPM__Set_Data_dv                        (CDFid id,long recNum,CDF__REAL4 *value);
extern void CDF_L1_LPM__Set_Data_weathercode_rain          (CDFid id,long recNum,CDF__INT2 *value);
extern void CDF_L1_LPM__Set_Data_weathercode_snow          (CDFid id,long recNum,CDF__INT2 *value);
extern void CDF_L1_LPM__Set_Data_weathercode_intensity     (CDFid id,long recNum,CDF__INT2 *value);


void CDF_L1_LPM__Create   (CDFid      *id_ptr,
                                const char *filepath,const char *data_version){
    CDF__Create(id_ptr,filepath);
    CDF_L1_LPM__Set_gAttr(*id_ptr);
    CDF_L1_LPM__Set_vAttr(*id_ptr);
    CDF_L1_LPM__Set_zVars(*id_ptr);
}

void CDF_L1_LPM__Set_gAttr(CDFid id){
    CDF__Set_gAttr(id,"Discipline"                ,"Meteorology");
    CDF__Set_gAttr(id,"Project"                   ,"Ground-based remote sensing for precipitation");
    CDF__Set_gAttr(id,"Source_name"               ,"LPM");
    CDF__Set_gAttr(id,"Data_type"                 ,"L1>Level 1 Data");
    CDF__Set_gAttr(id,"Mission_group"             ,"Intelligent informatics lab. (Shiina lab.)");
    CDF__Set_gAttr(id,"Descriptor"                ,".");
    CDF__Set_gAttr(id,"PI_name"                   ,"Toru Shiina");
    CDF__Set_gAttr(id,"PI_affiliation"            ,"Toyama National College of Technology (Imizu Campus)");
    CDF__Set_gAttr(id,"Generated_by"              ,"Mamoru Ota");
    CDF__Set_gAttr(id,"Data_version"              ,"01");
    CDF__Set_gAttr(id,"TITLE"                     ,"LPM");
    CDF__Set_gAttr(id,"Time_zone_information"     ,"UTC+09");
    /* CDF__Set_gAttr(id,"Device_name"               ,dn);
     CDF__Set_gAttr(id,"Device_version_number"     ,dvs);
     CDF__Set_gAttr(id,"Device_serial_number"      ,dsn);*/
    CDF__Set_gAttr(id,"Time_resolution"           ,"60 seconds");
}

void CDF_L1_LPM__Set_vAttr(CDFid id){
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

void CDF_L1_LPM__Set_zVars(CDFid id){
    CDF_L1_LPM__Set_zVar_epoch                     (id);
    CDF_L1_LPM__Set_zVar_R                         (id);
    CDF_L1_LPM__Set_zVar_R_liquid                  (id);
    CDF_L1_LPM__Set_zVar_R_solid                   (id);
    CDF_L1_LPM__Set_zVar_Z                         (id);
    CDF_L1_LPM__Set_zVar_N                         (id);
    CDF_L1_LPM__Set_zVar_ND                        (id);
    CDF_L1_LPM__Set_zVar_Nv                        (id);
    CDF_L1_LPM__Set_zVar_Dv_histgram               (id);
    CDF_L1_LPM__Set_zVar_D                         (id);
    CDF_L1_LPM__Set_zVar_dD                        (id);
    CDF_L1_LPM__Set_zVar_v                         (id);
    CDF_L1_LPM__Set_zVar_dv                        (id);
    CDF_L1_LPM__Set_zVar_weathercode_rain          (id);
    CDF_L1_LPM__Set_zVar_weathercode_snow          (id);
    CDF_L1_LPM__Set_zVar_weathercode_intensity     (id);    
}

void CDF_L1_LPM__Set_Data(CDF_L1_LPM__DATA *dat,CDFid id,long recNum){
    CDF_L1_LPM__Set_Data_epoch                     (id,recNum,&dat->epoch                      );
    CDF_L1_LPM__Set_Data_R                         (id,recNum,&dat->R                          );
    CDF_L1_LPM__Set_Data_R_liquid                  (id,recNum,&dat->R_liquid                   );
    CDF_L1_LPM__Set_Data_R_solid                   (id,recNum,&dat->R_solid                    );
    CDF_L1_LPM__Set_Data_Z                         (id,recNum,&dat->Z                          );
    CDF_L1_LPM__Set_Data_N                         (id,recNum,&dat->N                          );
    CDF_L1_LPM__Set_Data_ND                        (id,recNum,&dat->ND[0]                      );
    CDF_L1_LPM__Set_Data_Nv                        (id,recNum,&dat->Nv[0]                      );
    CDF_L1_LPM__Set_Data_Dv_histgram               (id,recNum,&dat->Dv_histgram[0][0]          );
    CDF_L1_LPM__Set_Data_D                         (id,recNum,&dat->D[0]                       );
    CDF_L1_LPM__Set_Data_dD                        (id,recNum,&dat->dD[0]                      );
    CDF_L1_LPM__Set_Data_v                         (id,recNum,&dat->v[0]                       );
    CDF_L1_LPM__Set_Data_dv                        (id,recNum,&dat->dv[0]                      );
    CDF_L1_LPM__Set_Data_weathercode_rain          (id,recNum,&dat->weathercode_rain           );
    CDF_L1_LPM__Set_Data_weathercode_snow          (id,recNum,&dat->weathercode_snow           );
    CDF_L1_LPM__Set_Data_weathercode_intensity     (id,recNum,&dat->weathercode_intensity      ); 
}

void CDF_L1_LPM__Get_Data(CDF_L1_LPM__DATA *dat,CDFid id,long recNum){
    char     *varNames[16] = {
        "epoch",
        "R",
        "R_liquid",
        "R_solid",
        "Z",
        "N",
        "ND",
        "Nv",
        "Dv_histgram",
        "D",
        "dD",
        "v",
        "dv",
        "weathercode_rain",
        "weathercode_snow",
        "weathercode_intensity"
    };
    
    void     *buffers [16] = {
        &dat->epoch,
        &dat->R,
        &dat->R_liquid,
        &dat->R_solid,
        &dat->Z,
        &dat->N,
        &dat->ND[0],
        &dat->Nv[0],
        &dat->Dv_histgram[0][0],
        &dat->D[0],
        &dat->dD[0],
        &dat->v[0],
        &dat->dv[0],
        &dat->weathercode_rain,
        &dat->weathercode_snow,
        &dat->weathercode_intensity
    };
    CDFstatus status;
    
    status = CDFgetzVarsRecordData(id,
                                   16L,
                                   varNames,
                                   recNum,
                                   buffers);
    if(status != CDF_OK){
        CDF__Status_Handler(status);
    }
}