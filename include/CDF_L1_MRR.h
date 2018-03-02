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

#ifndef _CDF_L1_MRR_H_INCLUDE_
#define _CDF_L1_MRR_H_INCLUDE_

#include"CDF_COMMON.h"

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct{
    CDF__TIME_TT2000 epoch;    
    CDF__UINT2       H [32];
    CDF__UINT1       dH;
    CDF__REAL4       V [64];
    CDF__REAL4       dV;
    CDF__REAL4       TF[32];
    CDF__UINT4       CC;
    CDF__UINT4       F [32][64];
    CDF__UINT4       F_sum [32];
    CDF__UINT1       MDQ;
    CDF__UINT2       BW;
  }CDF_L1_MRR__DATA;

  void CDF_L1_MRR__Create   (CDFid      *id_ptr,
			     const char *filepath,
			     const char *data_version,
			     const char *device_name,
			     const char *device_version_number,
			     const char *device_serial_number);

  void CDF_L1_MRR__Set_gAttr(CDFid       id,
			     const char *logical_file_id,
			     const char *data_version,
			     const char *device_name,
			     const char *device_version_number,
			     const char *device_serial_number);
  void CDF_L1_MRR__Set_vAttr(CDFid id);
  void CDF_L1_MRR__Set_zVars(CDFid id);

  void CDF_L1_MRR__Set_Data (CDF_L1_MRR__DATA *dat,CDFid id,long recNum);
  void CDF_L1_MRR__Get_Data (CDF_L1_MRR__DATA *dat,CDFid id,long recNum);

#ifdef __cplusplus
}
#endif

#endif
