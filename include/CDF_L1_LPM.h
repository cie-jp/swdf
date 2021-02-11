/*****************************************************************
 *
 * CDF操作関連ライブラリ
 *
 *    LPM共通 L1 z変数
 *
 *****************************************************************/

#ifndef _CDF_L1_LPM_H_INCLUDE_
#define _CDF_L1_LPM_H_INCLUDE_

#include"CDF_COMMON.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    typedef struct{
      CDF__TIME_TT2000    epoch;
      CDF__REAL4          R;
      CDF__REAL4          R_liquid;
      CDF__REAL4          R_solid;
      CDF__REAL4          Z;      
      CDF__UINT2          N;
      CDF__UINT2          ND[22];
      CDF__UINT2          Nv[20];
        CDF__UINT2          Dv_histgram[22][20];      //93               epoch   D       v       (時刻x粒径x落下速度)                       linear
        //(Dv_histgram[粒径クラス番号 - 1][速度クラス番号 - 1])
        //補助情報(DEPENDの記述は必要なし)
        CDF__REAL4          D [22];                   //各クラスの平均粒径    (CDF_L1_LPM__D )
        CDF__REAL4          dD[22];                   //各クラスの粒径幅      (CDF_L1_LPM__dD)
        CDF__REAL4          v [20];                   //各クラスの平均落下速度 (CDF_L1_LPM__v )
        CDF__REAL4          dv[20];                   //各クラスの落下速度幅   (CDF_L1_LPM__dv)
    }CDF_L1_LPM__DATA;
    
    void CDF_L1_LPM__Create   (CDFid      *id_ptr,
                               const char *filepath,const char *data_version);
  
    void CDF_L1_LPM__Set_gAttr(CDFid id);
    
    void CDF_L1_LPM__Set_vAttr(CDFid id);
    void CDF_L1_LPM__Set_zVars(CDFid id);
    
    void CDF_L1_LPM__Set_Data (CDF_L1_LPM__DATA *dat,CDFid id,long recNum);
    void CDF_L1_LPM__Get_Data (CDF_L1_LPM__DATA *dat,CDFid id,long recNum);
    
#ifdef __cplusplus
}
#endif

#endif
