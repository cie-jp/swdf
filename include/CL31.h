/*****************************************************************
 * 
 * CL31
 *
 *                           Created  by Mamoru Ota (2018/02/27)
 *
 *****************************************************************/ 

#ifndef _CL31_H_INCLUDE_
#define _CL31_H_INCLUDE_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"CDF_L1_CL31.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CL31__LINE1_LEN      (14 +    9)
#define CL31__LINE2_LEN      (14 +   34)
#define CL31__LINE3_LEN      (14 +   36)
#define CL31__LINE4_LEN      (14 +   48)
#define CL31__LINE5_LEN      (14 + 3851)
#define CL31__LINE6_LEN      (14 +    5)
#define CL31__LINE7_LEN      ( 0 +    1)

#define CL31__LINES_LEN_MSG1 (CL31__LINE2_LEN +               0 + CL31__LINE4_LEN + CL31__LINE5_LEN + CL31__LINE6_LEN + CL31__LINE7_LEN)
#define CL31__LINES_LEN_MSG2 (CL31__LINE2_LEN + CL31__LINE3_LEN + CL31__LINE4_LEN + CL31__LINE5_LEN + CL31__LINE6_LEN + CL31__LINE7_LEN)

  typedef struct{
    FILE *fp;
    CHAR  buf  [CL31__LINES_LEN_MSG2];
    UCHAR tmp  [3993];
    CHAR  line1[CL31__LINE1_LEN];
    CHAR *line2;
    CHAR *line3;
    CHAR *line4;
    CHAR *line5;
    CHAR *line6;
    CHAR *line7;
    int   YYYY;
    int   MM;
    int   DD;
    int   hh;
    int   mm;
    int   ss;
    CHAR  unit_id;
    int   software_level_id;
    int   msg_number;
    int   subclass;
    int   detection_status;
    CHAR  WA_info;
    int   val1,val2,val3;
    UCHAR AWS[12];

    //3rd line (of message no.2)
    UINT1  cloud_amount_status[5];
    UINT2  cloud_layer_height [5];
    
    //4th line (of message no.2)
    UINT4  Parameter_SCALE;
    UINT1  dH;
    UINT2  sample_length;
    UINT2  laser_pulse_energy;
    INT2   laser_temp;
    UINT1  window_transmission_estimate;
    UINT1  tilt_angle;
    UINT2  background_light;
    CHAR   measurement_params[9];
    UINT2  back_scat_sum;

    //5th line (of message no.2)
    REAL8  back_scat[1500];
  }CL31;

  int   CL31__INITIALIZE (CL31 *cl31,const char *filename);
  void  CL31__FINALIZE   (CL31 *cl31);
  int   CL31__READ       (CL31 *cl31);
  void  CL31__SHOWINFO   (CL31 *cl31);
  void  CL31__GET_DATA   (CL31 *cl31,CDF_L1_CL31__DATA *dat);

  int   CL31__CHECK_HEAD (CL31 *cl31);
  int   CL31__CHECK_LINE1(CL31 *cl31);
  int   CL31__CHECK_LINE2(CL31 *cl31);
  int   CL31__CHECK_LINE3(CL31 *cl31);
  int   CL31__CHECK_LINE4(CL31 *cl31);
  int   CL31__CHECK_LINE5(CL31 *cl31);
  int   CL31__CHECK_LINE6(CL31 *cl31);
  int   CL31__CHECK_LINE7(CL31 *cl31);
  UINT2 CL31__CHECK_CRC16(CL31 *cl31);

#ifdef __cplusplus
}
#endif

#endif
