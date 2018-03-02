/********************************************************************************************************
 *
 * CDF操作関連ライブラリ
 *
 *    Parsivel共通 L2 z変数
 *                  01 rain_intensity              : 降雨強度[mm/h]                        (****.*** | 0000.000 ~  9999.999)
 *                  02 accumulated_rain_amount     : 積算総雨量(32bit)[mm]                 (****.**  | 0000.00  ~  0300.00 )
 *                  03 weathercode_rain            : 天気コード(SYNOP Table4680)           (**       |   00     ~    99    )
 *                  04 weathercode_snow            : 天気コード(SYNOP Table4677)           (**       |   00     ~    99    )
 *                  05 weathercode_intedity        : 天気コード(MENTAR/SPECI Table4678)    (NP,(-/+)DZ,(-/+)RADZ,(-/+)RA,(-/+)RASN,(-/+)SN,(-/+)SG,(-/+)GS,GR)
 *                  07 radar_reflectivity          : レーダ反射因子(32bit)[dBz]            (**.***   |   -9.999 ~    09.999)
 *                  08 MOR_visibility              : 視程(気象光学距離)[m]                 (*****    |    0     ~ 20000    )
 *                  09 sample_interval             : サンプル周期[s]                       (*****    |    0     ~ 03600    )
 *                  10 signal_amplitude            : 信号振幅                              (*****    |    0     ~ 99999    )
 *                  11 particles_number            : 粒子数                                (*****    |    0     ~ 99999    )
 *                  12 temperature                 : センサ内温度[°C]                     (***      |  -99     ~   100    )
 *                  15 firmware_DSP                : DSPのバージョン                       (******)
 *                  16 heating_current             : 加熱電流[A]                           (*.**     |    0.00  ~     4.00 )
 *                  17 power_supply_voltage        : 電源電圧[V]                           (**.*     |    0.0   ~    30.0  )
 *                  18 sensor_status               : センサのステータス                    (*        |    0     ~     3    )
 *                  19 measurement_start_time      : 観測開始時間                          (DD.MM.YYYY_hh:mm:ss)
 *               20 21 epoch                       : センサの時間,日時                     (hh:mm:ss)(DD.MM.YYYY)
 *                  22 device_name[8];             : 基地局名                              (****)
 *                  34 kinetic_energy              : 運動エネルギー[J/(m2h)]               (***.***  |  000.000 ~   999.999)
 *                  35 snow_intensity              : 降雪強度[mm/h]                        (****.**  | 0000.00  ~  9999.99 )
 *                  90 field_N[32]                 : 粒径分布[log (1/m3 mm)]               (**.***;  |  -9.999  ~    99.999) x 32
 *                  90 field_v[32]                 : 落下速度[m/s]                         (**.***;  |   0.000  ~    99.999) x 32
 *                  93 Dv_histgram[32][32]         : 生データ                              (***;     | 000      ~   999    ) x 32 x 32
 *
 *******************************************************************************************************/


#include"CDF_L2_PARSIVEL.h"

extern void CDF_L2_PARSIVEL__Set_zVar_rain_intensity            (CDFid id);//01
extern void CDF_L2_PARSIVEL__Set_zVar_accumulated_rain_amount   (CDFid id);//02
extern void CDF_L2_PARSIVEL__Set_zVar_weathercode_rain          (CDFid id);//03
extern void CDF_L2_PARSIVEL__Set_zVar_weathercode_snow          (CDFid id);//04
extern void CDF_L2_PARSIVEL__Set_zVar_weathercode_intensity     (CDFid id);//05
extern void CDF_L2_PARSIVEL__Set_zVar_radar_reflectivity        (CDFid id);//07
extern void CDF_L2_PARSIVEL__Set_zVar_MOR_visibility            (CDFid id);//08
extern void CDF_L2_PARSIVEL__Set_zVar_sample_interval           (CDFid id);//09
extern void CDF_L2_PARSIVEL__Set_zVar_signal_amplitude          (CDFid id);//10
extern void CDF_L2_PARSIVEL__Set_zVar_particle_number           (CDFid id);//11
extern void CDF_L2_PARSIVEL__Set_zVar_temperature               (CDFid id);//12
extern void CDF_L2_PARSIVEL__Set_zVar_firmware_DSP_version      (CDFid id);//15
extern void CDF_L2_PARSIVEL__Set_zVar_heating_current           (CDFid id);//16
extern void CDF_L2_PARSIVEL__Set_zVar_power_supply_voltage      (CDFid id);//17
extern void CDF_L2_PARSIVEL__Set_zVar_sensor_status             (CDFid id);//18
extern void CDF_L2_PARSIVEL__Set_zVar_measurement_start_time    (CDFid id);//19
extern void CDF_L2_PARSIVEL__Set_zVar_epoch                     (CDFid id);//20,21
extern void CDF_L2_PARSIVEL__Set_zVar_device_name               (CDFid id);//22
extern void CDF_L2_PARSIVEL__Set_zVar_kinetic_energy            (CDFid id);//34
extern void CDF_L2_PARSIVEL__Set_zVar_snow_intensity            (CDFid id);//35
extern void CDF_L2_PARSIVEL__Set_zVar_field_N                   (CDFid id);//90
extern void CDF_L2_PARSIVEL__Set_zVar_field_v                   (CDFid id);//91
extern void CDF_L2_PARSIVEL__Set_zVar_Dv_histgram               (CDFid id);//93
extern void CDF_L2_PARSIVEL__Set_zVar_D                         (CDFid id);
extern void CDF_L2_PARSIVEL__Set_zVar_dD                        (CDFid id);
extern void CDF_L2_PARSIVEL__Set_zVar_v                         (CDFid id);
extern void CDF_L2_PARSIVEL__Set_zVar_dv                        (CDFid id);
//L2
extern void CDF_L2_PARSIVEL__Set_zVar_R_rain                    (CDFid id);
extern void CDF_L2_PARSIVEL__Set_zVar_R_snow                    (CDFid id);
extern void CDF_L2_PARSIVEL__Set_zVar_Re                        (CDFid id);
extern void CDF_L2_PARSIVEL__Set_zVar_Z                         (CDFid id);
extern void CDF_L2_PARSIVEL__Set_zVar_Ze_rain                   (CDFid id);
extern void CDF_L2_PARSIVEL__Set_zVar_Ze_snow                   (CDFid id);
extern void CDF_L2_PARSIVEL__Set_zVar_K                         (CDFid id);
extern void CDF_L2_PARSIVEL__Set_zVar_E                         (CDFid id);

extern void CDF_L2_PARSIVEL__Set_Data_rain_intensity            (CDFid id,long recNum,CDF__REAL4 *value);
extern void CDF_L2_PARSIVEL__Set_Data_accumulated_rain_amount   (CDFid id,long recNum,CDF__REAL4 *value);
extern void CDF_L2_PARSIVEL__Set_Data_weathercode_rain          (CDFid id,long recNum,CDF__INT2 *value);
extern void CDF_L2_PARSIVEL__Set_Data_weathercode_snow          (CDFid id,long recNum,CDF__INT2 *value);
extern void CDF_L2_PARSIVEL__Set_Data_weathercode_intensity     (CDFid id,long recNum,CDF__INT2 *value);
extern void CDF_L2_PARSIVEL__Set_Data_radar_reflectivity        (CDFid id,long recNum,CDF__REAL4 *value);
extern void CDF_L2_PARSIVEL__Set_Data_MOR_visibility            (CDFid id,long recNum,CDF__UINT2 *value);
extern void CDF_L2_PARSIVEL__Set_Data_sample_interval           (CDFid id,long recNum,CDF__UINT2 *value);
extern void CDF_L2_PARSIVEL__Set_Data_signal_amplitude          (CDFid id,long recNum,CDF__UINT4 *value);
extern void CDF_L2_PARSIVEL__Set_Data_particle_number           (CDFid id,long recNum,CDF__UINT4 *value);
extern void CDF_L2_PARSIVEL__Set_Data_temperature               (CDFid id,long recNum,CDF__INT2 *value);
extern void CDF_L2_PARSIVEL__Set_Data_firmware_DSP_version      (CDFid id,long recNum,CDF__CHAR  *value);
extern void CDF_L2_PARSIVEL__Set_Data_heating_current           (CDFid id,long recNum,CDF__REAL4 *value);
extern void CDF_L2_PARSIVEL__Set_Data_power_supply_voltage      (CDFid id,long recNum,CDF__REAL4 *value);
extern void CDF_L2_PARSIVEL__Set_Data_sensor_status             (CDFid id,long recNum,CDF__UINT1 *value);
extern void CDF_L2_PARSIVEL__Set_Data_measurement_start_time    (CDFid id,long recNum,CDF__TIME_TT2000 *value);
extern void CDF_L2_PARSIVEL__Set_Data_epoch                     (CDFid id,long recNum,CDF__TIME_TT2000 *value);
extern void CDF_L2_PARSIVEL__Set_Data_device_name               (CDFid id,long recNum,CDF__CHAR *value);
extern void CDF_L2_PARSIVEL__Set_Data_kinetic_energy            (CDFid id,long recNum,CDF__REAL4 *value);
extern void CDF_L2_PARSIVEL__Set_Data_snow_intensity            (CDFid id,long recNum,CDF__REAL4 *value);
extern void CDF_L2_PARSIVEL__Set_Data_field_N                   (CDFid id,long recNum,CDF__REAL4 *value);
extern void CDF_L2_PARSIVEL__Set_Data_field_v                   (CDFid id,long recNum,CDF__REAL4 *value);
extern void CDF_L2_PARSIVEL__Set_Data_Dv_histgram               (CDFid id,long recNum,CDF__UINT2 *value);
extern void CDF_L2_PARSIVEL__Set_Data_D                         (CDFid id,long recNum,CDF__REAL4 *value);
extern void CDF_L2_PARSIVEL__Set_Data_dD                        (CDFid id,long recNum,CDF__REAL4 *value);
extern void CDF_L2_PARSIVEL__Set_Data_v                         (CDFid id,long recNum,CDF__REAL4 *value);
extern void CDF_L2_PARSIVEL__Set_Data_dv                        (CDFid id,long recNum,CDF__REAL4 *value);
//L2
extern void CDF_L2_PARSIVEL__Set_Data_R_rain                    (CDFid id,long recNum,CDF__REAL4 *value);
extern void CDF_L2_PARSIVEL__Set_Data_R_snow                    (CDFid id,long recNum,CDF__REAL4 *value);
extern void CDF_L2_PARSIVEL__Set_Data_Re                        (CDFid id,long recNum,CDF__REAL4 *value);
extern void CDF_L2_PARSIVEL__Set_Data_Z                         (CDFid id,long recNum,CDF__REAL4 *value);
extern void CDF_L2_PARSIVEL__Set_Data_Ze_rain                   (CDFid id,long recNum,CDF__REAL4 *value);
extern void CDF_L2_PARSIVEL__Set_Data_Ze_snow                   (CDFid id,long recNum,CDF__REAL4 *value);
extern void CDF_L2_PARSIVEL__Set_Data_K                         (CDFid id,long recNum,CDF__REAL4  *value);
extern void CDF_L2_PARSIVEL__Set_Data_E                         (CDFid id,long recNum,CDF__REAL4  *value);


void CDF_L2_PARSIVEL__Create   (CDFid      *id_ptr,
                                const char *filepath,const char *data_version){
    CDF__Create(id_ptr,filepath);
    CDF_L2_PARSIVEL__Set_gAttr(*id_ptr);
    CDF_L2_PARSIVEL__Set_vAttr(*id_ptr);
    CDF_L2_PARSIVEL__Set_zVars(*id_ptr);
}

void CDF_L2_PARSIVEL__Set_gAttr(CDFid id){
    CDF__Set_gAttr(id,"Discipline"                ,"Meteorology");
    CDF__Set_gAttr(id,"Project"                   ,"Ground-based remote sensing for precipitation");
    CDF__Set_gAttr(id,"Source_name"               ,"PARSIVEL");
    CDF__Set_gAttr(id,"Data_type"                 ,"L2>Level 2 Data");
    CDF__Set_gAttr(id,"Mission_group"             ,"Intelligent informatics lab. (Shiina lab.)");
    CDF__Set_gAttr(id,"Descriptor"                ,".");
    CDF__Set_gAttr(id,"PI_name"                   ,"Toru Shiina");
    CDF__Set_gAttr(id,"PI_affiliation"            ,"Toyama National College of Technology (Imizu Campus)");
    CDF__Set_gAttr(id,"Generated_by"              ,"Mamoru Ota");
    CDF__Set_gAttr(id,"Data_version"              ,"02");
    CDF__Set_gAttr(id,"TITLE"                     ,"PARSIVEL");
    CDF__Set_gAttr(id,"Time_zone_information"     ,"UTC+09");
    /* CDF__Set_gAttr(id,"Device_name"               ,dn);
     CDF__Set_gAttr(id,"Device_version_number"     ,dvs);
     CDF__Set_gAttr(id,"Device_serial_number"      ,dsn);*/
    CDF__Set_gAttr(id,"Time_resolution"           ,"60 seconds");
}

void CDF_L2_PARSIVEL__Set_vAttr(CDFid id){
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

void CDF_L2_PARSIVEL__Set_zVars(CDFid id){
    CDF_L2_PARSIVEL__Set_zVar_rain_intensity            (id);
    CDF_L2_PARSIVEL__Set_zVar_accumulated_rain_amount   (id);
    CDF_L2_PARSIVEL__Set_zVar_weathercode_rain          (id);
    CDF_L2_PARSIVEL__Set_zVar_weathercode_snow          (id);
    CDF_L2_PARSIVEL__Set_zVar_weathercode_intensity     (id);
    CDF_L2_PARSIVEL__Set_zVar_radar_reflectivity        (id);
    CDF_L2_PARSIVEL__Set_zVar_MOR_visibility            (id);
    CDF_L2_PARSIVEL__Set_zVar_sample_interval           (id);
    CDF_L2_PARSIVEL__Set_zVar_signal_amplitude          (id);
    CDF_L2_PARSIVEL__Set_zVar_particle_number           (id);
    CDF_L2_PARSIVEL__Set_zVar_temperature               (id);
    CDF_L2_PARSIVEL__Set_zVar_firmware_DSP_version      (id);
    CDF_L2_PARSIVEL__Set_zVar_heating_current           (id);
    CDF_L2_PARSIVEL__Set_zVar_power_supply_voltage      (id);
    CDF_L2_PARSIVEL__Set_zVar_sensor_status             (id);
    CDF_L2_PARSIVEL__Set_zVar_measurement_start_time    (id);
    CDF_L2_PARSIVEL__Set_zVar_epoch                     (id);
    CDF_L2_PARSIVEL__Set_zVar_device_name               (id);
    CDF_L2_PARSIVEL__Set_zVar_kinetic_energy            (id);
    CDF_L2_PARSIVEL__Set_zVar_snow_intensity            (id);
    CDF_L2_PARSIVEL__Set_zVar_field_N                   (id);
    CDF_L2_PARSIVEL__Set_zVar_field_v                   (id);
    CDF_L2_PARSIVEL__Set_zVar_Dv_histgram               (id);
    CDF_L2_PARSIVEL__Set_zVar_D                         (id);
    CDF_L2_PARSIVEL__Set_zVar_dD                        (id);
    CDF_L2_PARSIVEL__Set_zVar_v                         (id);
    CDF_L2_PARSIVEL__Set_zVar_dv                        (id);
    //L2
    CDF_L2_PARSIVEL__Set_zVar_R_rain                    (id);
    CDF_L2_PARSIVEL__Set_zVar_R_snow                    (id);
    CDF_L2_PARSIVEL__Set_zVar_Re                        (id);
    CDF_L2_PARSIVEL__Set_zVar_Z                         (id);
    CDF_L2_PARSIVEL__Set_zVar_Ze_rain                   (id);
    CDF_L2_PARSIVEL__Set_zVar_Ze_snow                   (id);
    CDF_L2_PARSIVEL__Set_zVar_K                         (id);
    CDF_L2_PARSIVEL__Set_zVar_E                         (id);
    
}

void CDF_L2_PARSIVEL__Set_Data(CDF_L2_PARSIVEL__DATA *dat,CDFid id,long recNum){
    CDF_L2_PARSIVEL__Set_Data_rain_intensity            (id,recNum,&dat->rain_intensity             );
    CDF_L2_PARSIVEL__Set_Data_accumulated_rain_amount   (id,recNum,&dat->accumulated_rain_amount    );
    CDF_L2_PARSIVEL__Set_Data_weathercode_rain          (id,recNum,&dat->weathercode_rain           );
    CDF_L2_PARSIVEL__Set_Data_weathercode_snow          (id,recNum,&dat->weathercode_snow           );
    CDF_L2_PARSIVEL__Set_Data_weathercode_intensity     (id,recNum,&dat->weathercode_intensity      );
    CDF_L2_PARSIVEL__Set_Data_radar_reflectivity        (id,recNum,&dat->radar_reflectivity         );
    CDF_L2_PARSIVEL__Set_Data_MOR_visibility            (id,recNum,&dat->MOR_visibility             );
    CDF_L2_PARSIVEL__Set_Data_sample_interval           (id,recNum,&dat->sample_interval            );
    CDF_L2_PARSIVEL__Set_Data_signal_amplitude          (id,recNum,&dat->signal_amplitude           );
    CDF_L2_PARSIVEL__Set_Data_particle_number           (id,recNum,&dat->particle_number            );
    CDF_L2_PARSIVEL__Set_Data_temperature               (id,recNum,&dat->temperature                );
    CDF_L2_PARSIVEL__Set_Data_firmware_DSP_version      (id,recNum,&dat->firmware_DSP_version       );
    CDF_L2_PARSIVEL__Set_Data_heating_current           (id,recNum,&dat->heating_current            );
    CDF_L2_PARSIVEL__Set_Data_power_supply_voltage      (id,recNum,&dat->power_supply_voltage       );
    CDF_L2_PARSIVEL__Set_Data_sensor_status             (id,recNum,&dat->sensor_status              );
    CDF_L2_PARSIVEL__Set_Data_measurement_start_time    (id,recNum,&dat->measurement_start_time     );
    CDF_L2_PARSIVEL__Set_Data_epoch                     (id,recNum,&dat->epoch                      );
    CDF_L2_PARSIVEL__Set_Data_device_name               (id,recNum,&dat->device_name[0]             );
    CDF_L2_PARSIVEL__Set_Data_kinetic_energy            (id,recNum,&dat->kinetic_energy             );
    CDF_L2_PARSIVEL__Set_Data_snow_intensity            (id,recNum,&dat->snow_intensity             );
    CDF_L2_PARSIVEL__Set_Data_field_N                   (id,recNum,&dat->field_N[0]                 );
    CDF_L2_PARSIVEL__Set_Data_field_v                   (id,recNum,&dat->field_v[0]                 );
    CDF_L2_PARSIVEL__Set_Data_Dv_histgram               (id,recNum,&dat->Dv_histgram[0][0]          );
    CDF_L2_PARSIVEL__Set_Data_D                         (id,recNum,&dat->D[0]                       );
    CDF_L2_PARSIVEL__Set_Data_dD                        (id,recNum,&dat->dD[0]                      );
    CDF_L2_PARSIVEL__Set_Data_v                         (id,recNum,&dat->v[0]                       );
    CDF_L2_PARSIVEL__Set_Data_dv                        (id,recNum,&dat->dv[0]                      );
    //L2
    CDF_L2_PARSIVEL__Set_Data_R_rain                    (id,recNum,&dat->R_rain                     );
    CDF_L2_PARSIVEL__Set_Data_R_snow                    (id,recNum,&dat->R_snow                     );
    CDF_L2_PARSIVEL__Set_Data_Re                        (id,recNum,&dat->Re[0][0]                   );
    CDF_L2_PARSIVEL__Set_Data_Z                         (id,recNum,&dat->Z                          );
    CDF_L2_PARSIVEL__Set_Data_Ze_rain                   (id,recNum,&dat->Ze_rain                    );
    CDF_L2_PARSIVEL__Set_Data_Ze_snow                   (id,recNum,&dat->Ze_snow                    );
    CDF_L2_PARSIVEL__Set_Data_K                         (id,recNum,&dat->K                          );
    CDF_L2_PARSIVEL__Set_Data_E                         (id,recNum,&dat->E                          );

}

void CDF_L2_PARSIVEL__Get_Data(CDF_L2_PARSIVEL__DATA *dat,CDFid id,long recNum){
    char     *varNames[35] = {
        "rain_intensity",
        "accumulated_rain_amount",
        "weathercode_rain",
        "weathercode_snow",
        "weathercode_intensity",
        "radar_reflectivity",
        "MOR_visibility",
        "sample_interval",
        "signal_amplitude",
        "particle_number",
        "temperature",
        "firmware_DSP_version",
        "heating_current",
        "power_supply_voltage",
        "sensor_status",
        "measurement_start_time",
        "epoch",
        "device_name",
        "kinetic_energy",
        "snow_intensity",
        "field_N",
        "field_v",
        "Dv_histgram",
        "D",
        "dD",
        "v",
        "dv",
//L2
        "R_rain",
        "R_snow",
        "Re",
        "Z",
        "Ze_rain",
        "Ze_snow",
        "K",
        "E"
    };
    
    void     *buffers [35] = {
        &dat->rain_intensity,
        &dat->accumulated_rain_amount,
        &dat->weathercode_rain,
        &dat->weathercode_snow,
        &dat->weathercode_intensity,
        &dat->radar_reflectivity,
        &dat->MOR_visibility,
        &dat->sample_interval,
        &dat->signal_amplitude,
        &dat->particle_number,
        &dat->temperature,
        &dat->firmware_DSP_version,
        &dat->heating_current,
        &dat->power_supply_voltage,
        &dat->sensor_status,
        &dat->measurement_start_time,
        &dat->epoch,
        &dat->device_name[0],
        &dat->kinetic_energy,
        &dat->snow_intensity,
        &dat->field_N[0],
        &dat->field_v[0],
        &dat->Dv_histgram[0][0],
        &dat->D[0],
        &dat->dD[0],
        &dat->v[0],
        &dat->dv[0],
        //L2
        &dat->R_rain,
        &dat->R_snow,
        &dat->Re[0][0],
        &dat->Z,
        &dat->Ze_rain,
        &dat->Ze_snow,
        &dat->K,
        &dat->E
    };
    CDFstatus status;
    
    status = CDFgetzVarsRecordData(id,
                                   35L,
                                   varNames,
                                   recNum,
                                   buffers);
    if(status != CDF_OK){
        CDF__Status_Handler(status);
    }
}
