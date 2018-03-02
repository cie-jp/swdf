/********************************************************************************
 *
 * Ceilometer Level1 CDF
 *
 * z variable
 *
 *  epoch                           : time
 *  H                               : height[m]
 *
 *  unit_identification_char        : Unit identification character 0...9,A...Z
 *  software_level                  : Software level ID 100...999
 *  message_number                  : Message number 1...2
 *  subclasses_message_char         : Character for subclasses of message 1...5
 *
 *  cloud_base_status               : Number of cloud base detected 0...5,/
 *  warning_alarm_info              : Warning and Alarm information
 *  cloud_base_height               : Cloud base height

 *  AWS                             : Alarm, Warning, and internal status information
 *
 *  cloud_amount_status             : Cloud amount of the first layer in oktas
 *  cloud_layer_height              : Height of the cloud layer
 *
 *  Parameter_SCALE                 : Parameter SCALE, 100(%) is normal
 *  dH                              : Backscatter profile resolution in meters
 *  sample_length                   : Length of the profile in samples
 *  laser_pulse_energy              : Laser pulse energy, % of nominal factory setting
 *  laser_temp                      : Laser temperature degrees C (-50...+99)
 *  window_transmission_estimate    : Window transmission estimate % (0...100)
 *  tilt_angle                      : Tilt angle, degrees from vertical (0...90)
 *  background_light                : Background light, millivolts at internal ADC input (0...2500)
 *  measurement_params              : Measurement parameters
 *  back_scat_sum                   : SUM of detected and normalized backscatter
 *
 *  back_scat                       : Backscatter coefficient
 *
 *
 *                                  2017/10/15
 *                                  Created by Kota Makino
 *
 ********************************************************************************/

#include<time.h>
#include"CDF_L1_CL31.h"

// *************************
// 1st line
// -------------------------
extern void CDF_L1_CL31__Set_zVar_epoch                        (CDFid id);
extern void CDF_L1_CL31__Set_zVar_H                            (CDFid id);
// *************************
// 2nd line
// -------------------------
extern void CDF_L1_CL31__Set_zVar_unit_identification_char     (CDFid id);
extern void CDF_L1_CL31__Set_zVar_software_level               (CDFid id);
extern void CDF_L1_CL31__Set_zVar_message_number               (CDFid id);
extern void CDF_L1_CL31__Set_zVar_subclasses_message_char      (CDFid id);
// *************************
// 3rd line
// -------------------------
extern void CDF_L1_CL31__Set_zVar_cloud_base_status            (CDFid id);
extern void CDF_L1_CL31__Set_zVar_warning_alarm_info           (CDFid id);
extern void CDF_L1_CL31__Set_zVar_cloud_base_height            (CDFid id);
extern void CDF_L1_CL31__Set_zVar_AWS                          (CDFid id);
// *************************
// 4th line
// -------------------------
extern void CDF_L1_CL31__Set_zVar_cloud_amount_status          (CDFid id);
extern void CDF_L1_CL31__Set_zVar_cloud_layer_height           (CDFid id);
// *************************
// 5th line
// -------------------------
extern void CDF_L1_CL31__Set_zVar_Parameter_SCALE              (CDFid id);
extern void CDF_L1_CL31__Set_zVar_dH                           (CDFid id);
extern void CDF_L1_CL31__Set_zVar_sample_length                (CDFid id);
extern void CDF_L1_CL31__Set_zVar_laser_pulse_energy           (CDFid id);
extern void CDF_L1_CL31__Set_zVar_laser_temp                   (CDFid id);
extern void CDF_L1_CL31__Set_zVar_window_transmission_estimate (CDFid id);
extern void CDF_L1_CL31__Set_zVar_tilt_angle                   (CDFid id);
extern void CDF_L1_CL31__Set_zVar_background_light             (CDFid id);
extern void CDF_L1_CL31__Set_zVar_measurement_params           (CDFid id);
extern void CDF_L1_CL31__Set_zVar_back_scat_sum                (CDFid id);
// *************************
// 6th line
// -------------------------
extern void CDF_L1_CL31__Set_zVar_back_scat                    (CDFid id);


// *************************
// 1st line
// -------------------------
extern void CDF_L1_CL31__Set_Data_epoch                            (CDFid id,long recNum,CDF__TIME_TT2000 *value);
extern void CDF_L1_CL31__Set_Data_H                                (CDFid id,long recNum,CDF__UINT2       *value);
// *************************
// 2nd line
// -------------------------
extern void CDF_L1_CL31__Set_Data_unit_identification_char         (CDFid id,long recNum,CDF__CHAR       *value);
extern void CDF_L1_CL31__Set_Data_software_level                   (CDFid id,long recNum,CDF__UINT2       *value);
extern void CDF_L1_CL31__Set_Data_message_number                   (CDFid id,long recNum,CDF__UINT1       *value);
extern void CDF_L1_CL31__Set_Data_subclasses_message_char          (CDFid id,long recNum,CDF__UINT1       *value);
// *************************
// 3rd line
// -------------------------
extern void CDF_L1_CL31__Set_Data_cloud_base_status                (CDFid id,long recNum,CDF__UINT1       *value);
extern void CDF_L1_CL31__Set_Data_warning_alarm_info               (CDFid id,long recNum,CDF__CHAR       *value);
extern void CDF_L1_CL31__Set_Data_cloud_base_height                (CDFid id,long recNum,CDF__UINT4       *value);
extern void CDF_L1_CL31__Set_Data_AWS                              (CDFid id,long recNum,CDF__CHAR        *value);
// *************************
// 4th line
// -------------------------
extern void CDF_L1_CL31__Set_Data_cloud_amount_status              (CDFid id,long recNum,CDF__UINT1       *value);
extern void CDF_L1_CL31__Set_Data_cloud_layer_height               (CDFid id,long recNum,CDF__UINT2       *value);
// *************************
// 5th line
// -------------------------
extern void CDF_L1_CL31__Set_Data_Parameter_SCALE                  (CDFid id,long recNum,CDF__UINT4       *value);
extern void CDF_L1_CL31__Set_Data_dH                               (CDFid id,long recNum,CDF__UINT1       *value);
extern void CDF_L1_CL31__Set_Data_sample_length                    (CDFid id,long recNum,CDF__UINT2       *value);
extern void CDF_L1_CL31__Set_Data_laser_pulse_energy               (CDFid id,long recNum,CDF__UINT2       *value);
extern void CDF_L1_CL31__Set_Data_laser_temp                       (CDFid id,long recNum,CDF__INT2        *value);
extern void CDF_L1_CL31__Set_Data_window_transmission_estimate     (CDFid id,long recNum,CDF__UINT1       *value);
extern void CDF_L1_CL31__Set_Data_tilt_angle                       (CDFid id,long recNum,CDF__UINT1       *value);
extern void CDF_L1_CL31__Set_Data_background_light                 (CDFid id,long recNum,CDF__UINT2       *value);
extern void CDF_L1_CL31__Set_Data_measurement_params               (CDFid id,long recNum,CDF__CHAR       *value);
extern void CDF_L1_CL31__Set_Data_back_scat_sum                    (CDFid id,long recNum,CDF__UINT2       *value);
// *************************
// 6th line
// -------------------------
extern void CDF_L1_CL31__Set_Data_back_scat                        (CDFid id,long recNum,CDF__REAL8       *value);

void CDF_L1_CL31__Create   (CDFid      *id_ptr,
			   const char *filepath,
			   const char *data_version,
			   const char *device_name,
			   const char *device_version_number,
			   const char *device_serial_number){
  CDF__Create(id_ptr,filepath);
  CDF_L1_CL31__Set_gAttr(*id_ptr,
			filepath,
			data_version,
			device_name,
			device_version_number,
			device_serial_number);
  CDF_L1_CL31__Set_vAttr(*id_ptr);
  CDF_L1_CL31__Set_zVars(*id_ptr);
}

void CDF_L1_CL31__Set_gAttr(CDFid       id,
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
  CDF__Set_gAttr(id,"Source_name"          ,"Ceilometer");
  CDF__Set_gAttr(id,"Data_type"            ,"L1>Level 1 Data");
  CDF__Set_gAttr(id,"Mission_group"        ,"Intelligent informatics lab. (Shiina lab.)");  
  CDF__Set_gAttr(id,"Descriptor"           ,".");
  CDF__Set_gAttr(id,"PI_name"              ,"Toru Shiina");
  CDF__Set_gAttr(id,"PI_affiliation"       ,"National Institute of Technology, Toyama College (Imizu Campus)");
  CDF__Set_gAttr(id,"Generated_by"         ,"Kota Makino");
  CDF__Set_gAttr(id,"Logical_file_id"      ,logical_file_id);
  CDF__Set_gAttr(id,"Generated_time"       ,gen_time);
  CDF__Set_gAttr(id,"Data_version"         ,data_version);
  CDF__Set_gAttr(id,"TITLE"                ,"Ceilometer backscatter coefficient");
  CDF__Set_gAttr(id,"Device_name"          ,device_name);
  CDF__Set_gAttr(id,"Device_version_number",device_version_number);
  CDF__Set_gAttr(id,"Device_serial_number" ,device_serial_number);
  CDF__Set_gAttr(id,"Time_zone_information","UTC+09");
  CDF__Set_gAttr(id,"Time_resolution"      ,"10 seconds");
}

void CDF_L1_CL31__Set_vAttr(CDFid id){
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

void CDF_L1_CL31__Set_zVars(CDFid id){
    // 1st line
    CDF_L1_CL31__Set_zVar_epoch                        (id);
    CDF_L1_CL31__Set_zVar_H                            (id);
    // 2nd line
    CDF_L1_CL31__Set_zVar_unit_identification_char     (id);
    CDF_L1_CL31__Set_zVar_software_level               (id);
    CDF_L1_CL31__Set_zVar_message_number               (id);
    CDF_L1_CL31__Set_zVar_subclasses_message_char      (id);
    // 3rd line
    CDF_L1_CL31__Set_zVar_cloud_base_status            (id);
    CDF_L1_CL31__Set_zVar_warning_alarm_info           (id);
    CDF_L1_CL31__Set_zVar_cloud_base_height            (id);
    CDF_L1_CL31__Set_zVar_AWS                          (id);
    // 4th line
    CDF_L1_CL31__Set_zVar_cloud_amount_status          (id);
    CDF_L1_CL31__Set_zVar_cloud_layer_height           (id);
    // 5th line
    CDF_L1_CL31__Set_zVar_Parameter_SCALE              (id);
    CDF_L1_CL31__Set_zVar_dH                           (id);
    CDF_L1_CL31__Set_zVar_sample_length                (id);
    CDF_L1_CL31__Set_zVar_laser_pulse_energy           (id);
    CDF_L1_CL31__Set_zVar_laser_temp                   (id);
    CDF_L1_CL31__Set_zVar_window_transmission_estimate (id);
    CDF_L1_CL31__Set_zVar_tilt_angle                   (id);
    CDF_L1_CL31__Set_zVar_background_light             (id);
    CDF_L1_CL31__Set_zVar_measurement_params           (id);
    CDF_L1_CL31__Set_zVar_back_scat_sum                (id);
    // 6th line
    CDF_L1_CL31__Set_zVar_back_scat                    (id);
}

void CDF_L1_CL31__Set_Data(CDF_L1_CL31__DATA *dat,CDFid id,long recNum){
    // 1st line
    CDF_L1_CL31__Set_Data_epoch                        (id,recNum,&dat->epoch   );
    CDF_L1_CL31__Set_Data_H                            (id,recNum,&dat->H[0]    );
    // 2nd line
    CDF_L1_CL31__Set_Data_unit_identification_char     (id,recNum,&dat->unit_identification_char   );
    CDF_L1_CL31__Set_Data_software_level               (id,recNum,&dat->software_level   );
    CDF_L1_CL31__Set_Data_message_number               (id,recNum,&dat->message_number   );
    CDF_L1_CL31__Set_Data_subclasses_message_char      (id,recNum,&dat->subclasses_message_char   );
    // 3rd line
    CDF_L1_CL31__Set_Data_cloud_base_status            (id,recNum,&dat->cloud_base_status      );
    CDF_L1_CL31__Set_Data_warning_alarm_info           (id,recNum,&dat->warning_alarm_info      );
    CDF_L1_CL31__Set_Data_cloud_base_height            (id,recNum,&dat->cloud_base_height[0]      );
    CDF_L1_CL31__Set_Data_AWS                          (id,recNum,&dat->AWS[0]      );
    // 4th line
    CDF_L1_CL31__Set_Data_cloud_amount_status          (id,recNum,&dat->cloud_amount_status[0]      );
    CDF_L1_CL31__Set_Data_cloud_layer_height           (id,recNum,&dat->cloud_layer_height[0]      );
    // 5th line
    CDF_L1_CL31__Set_Data_Parameter_SCALE              (id,recNum,&dat->Parameter_SCALE      );
    CDF_L1_CL31__Set_Data_dH                           (id,recNum,&dat->dH      );
    CDF_L1_CL31__Set_Data_sample_length                (id,recNum,&dat->sample_length      );
    CDF_L1_CL31__Set_Data_laser_pulse_energy           (id,recNum,&dat->laser_pulse_energy      );
    CDF_L1_CL31__Set_Data_laser_temp                   (id,recNum,&dat->laser_temp      );
    CDF_L1_CL31__Set_Data_window_transmission_estimate (id,recNum,&dat->window_transmission_estimate      );
    CDF_L1_CL31__Set_Data_tilt_angle                   (id,recNum,&dat->tilt_angle      );
    CDF_L1_CL31__Set_Data_background_light             (id,recNum,&dat->background_light      );
    CDF_L1_CL31__Set_Data_measurement_params           (id,recNum,&dat->measurement_params[0]      );
    CDF_L1_CL31__Set_Data_back_scat_sum                (id,recNum,&dat->back_scat_sum      );
    // 6th line
    CDF_L1_CL31__Set_Data_back_scat                    (id,recNum,&dat->back_scat[0]    );
}

void CDF_L1_CL31__Get_Data(CDF_L1_CL31__DATA *dat,CDFid id,long recNum){
  char *varNames[] = {
        // 1st line
        "epoch",
        "H",
        // 2nd line
        "unit_identification_char",
        "software_level",
        "message_number",
        "subclasses_message_char",
        // 3rd line
        "cloud_base_status",
        "warning_alarm_info",
        "cloud_base_height",
        "AWS",
        // 4th line
        "cloud_amount_status",
        "cloud_layer_height",
        // 5th line
        "Parameter_SCALE",
        "dH",
        "sample_length",
        "laser_pulse_energy",
        "laser_temp",
        "window_transmission_estimate",
        "tilt_angle",
        "background_light",
        "measurement_params",
        "back_scat_sum",
        // 6th line
        "back_scat",
  };

  void *buffers [] = {
        // 1st line
        &dat->epoch,
        &dat->H[0],
        // 2nd line
        &dat->unit_identification_char,
        &dat->software_level,
        &dat->message_number,
        &dat->subclasses_message_char,
        // 3rd line
        &dat->cloud_base_status,
        &dat->warning_alarm_info,
        &dat->cloud_base_height[0],
        &dat->AWS[0],
        // 4th line
        &dat->cloud_amount_status[0],
        &dat->cloud_layer_height[0],
        // 5th line
        &dat->Parameter_SCALE,
        &dat->dH,
        &dat->sample_length,
        &dat->laser_pulse_energy,
        &dat->laser_temp,
        &dat->window_transmission_estimate,
        &dat->tilt_angle,
        &dat->background_light,
        &dat->measurement_params[0],
        &dat->back_scat_sum,
        // 6th line
        &dat->back_scat[0],
  };
  CDFstatus status;

  status = CDFgetzVarsRecordData(id,
				 23L,
				 varNames,
				 recNum,
				 buffers);  
  if(status != CDF_OK){
    CDF__Status_Handler(status);
  }
}
