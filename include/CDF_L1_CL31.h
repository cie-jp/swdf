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

#ifndef _CDF_L1_CL31_H_INCLUDE_
#define _CDF_L1_CL31_H_INCLUDE_

#include"CDF_COMMON.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct{
        // 1st line
        CDF__TIME_TT2000    epoch;
        CDF__UINT2          H [770];
        
        // 2nd line
        CDF__CHAR           unit_identification_char;
        CDF__UINT2          software_level;
        CDF__UINT1          message_number;
        CDF__UINT1          subclasses_message_char;
        
        // 3rd line
        CDF__UINT1  cloud_base_status;
        CDF__CHAR   warning_alarm_info;
        CDF__UINT4  cloud_base_height[3];
        CDF__CHAR   AWS[12];
        
        // 4th line
        CDF__UINT1  cloud_amount_status[5];
        CDF__UINT2  cloud_layer_height[5];
        
        // 5th line
        CDF__UINT4  Parameter_SCALE;
        CDF__UINT1  dH;
        CDF__UINT2  sample_length;
        CDF__UINT2  laser_pulse_energy;
        CDF__INT2   laser_temp;
        CDF__UINT1  window_transmission_estimate;
        CDF__UINT1  tilt_angle;
        CDF__UINT2  background_light;
        CDF__CHAR   measurement_params[9];
        CDF__UINT2  back_scat_sum;
        
        // 6th line
        CDF__REAL8  back_scat[770];
        
    }CDF_L1_CL31__DATA;

  void CDF_L1_CL31__Create   (CDFid      *id_ptr,
			     const char *filepath,
			     const char *data_version,
			     const char *device_name,
			     const char *device_version_number,
			     const char *device_serial_number);

  void CDF_L1_CL31__Set_gAttr(CDFid       id,
			     const char *logical_file_id,
			     const char *data_version,
			     const char *device_name,
			     const char *device_version_number,
			     const char *device_serial_number);
  void CDF_L1_CL31__Set_vAttr(CDFid id);
  void CDF_L1_CL31__Set_zVars(CDFid id);

  void CDF_L1_CL31__Set_Data (CDF_L1_CL31__DATA *dat,CDFid id,long recNum);
  void CDF_L1_CL31__Get_Data (CDF_L1_CL31__DATA *dat,CDFid id,long recNum);

#ifdef __cplusplus
}
#endif

#endif
