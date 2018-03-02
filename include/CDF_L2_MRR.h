/*****************************************************************
 * 
 * CDF操作関連ライブラリ
 * 
 *    MRR共通 L2 z変数
 *                  epoch      / H             / 
 *                  V          / TF            / 
 *                  BW         / CC            /
 *                  MDQ        / F
 *                  D          / N             /
 *                  Ze         / Z             /
 *                  RR         / W             /
 *                  VW         / LWC           /
 * 
 *                           Modified by Mamoru Ota (2017/06/06)
 *                           Created  by Mamoru Ota (2017/06/03)
 *
 *****************************************************************/ 

#ifndef _CDF_L2_MRR_H_INCLUDE_
#define _CDF_L2_MRR_H_INCLUDE_

#include"CDF_COMMON.h"

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct{
    CDF__TIME_TT2000 epoch;    
    CDF__UINT2       H  [32];
    CDF__UINT1       dH;
    CDF__REAL4       V  [64];
    CDF__REAL4       dV;
    CDF__REAL4       TF [32];
    CDF__UINT2       BW;
    CDF__UINT4       CC;
    CDF__UINT1       MDQ;
    CDF__REAL4       F  [32][64];
    CDF__REAL4       D  [32][64];
    CDF__REAL4       N  [32][64];
    CDF__REAL4       Ze [32];
    CDF__REAL4       Z  [32];
    CDF__REAL4       RR [32];
    CDF__REAL4       W  [32];
    CDF__REAL4       VW [32];
    CDF__REAL4       LWC[32];
  }CDF_L2_MRR__DATA;

  void CDF_L2_MRR__Create   (CDFid      *id_ptr,
			     const char *filepath,
			     const char *data_version,
			     const char *device_name,
			     const char *device_version_number,
			     const char *device_serial_number);

  void CDF_L2_MRR__Set_gAttr(CDFid       id,
			     const char *logical_file_id,
			     const char *data_version,
			     const char *device_name,
			     const char *device_version_number,
			     const char *device_serial_number);
  void CDF_L2_MRR__Set_vAttr(CDFid id);
  void CDF_L2_MRR__Set_zVars(CDFid id);

  void CDF_L2_MRR__Set_Data (CDF_L2_MRR__DATA *dat,CDFid id,long recNum);
  void CDF_L2_MRR__Get_Data (CDF_L2_MRR__DATA *dat,CDFid id,long recNum);

#ifdef __cplusplus
}
#endif

#endif
