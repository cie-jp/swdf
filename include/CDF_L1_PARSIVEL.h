/*****************************************************************
 *
 * CDF操作関連ライブラリ
 *
 *    Parsivel共通 L1 z変数
 *
 *    ID            No.
 *    01            01 降雨強度[mm/h]                     (****.*** | 0000.000 ~  9999.999)
 *    02            02 積算降雨量(32bit)[mm]              (****.**  | 0000.00  ~  0300.00 )
 *    03            03 天気コード(SYNOP Table 4680)       (**       |   00     ~    99    )
 *    04            04 天気コード(SYNOP Table 4677)       (**       |   00     ~    99    )
 *    05            05 天気コード(METAR/SPECI Table 4678) (NP,(-/+)DZ,(-/+)RADZ,(-/+)RA,(-/+)RASN,(-/+)SN,(-/+)SG,(-/+)GS,GR)
 *             (-)  06 天気コード(NWS)                    (C ,L(-/+) ,RL(-/+)  ,R(-/+) ,RLS(-/+) ,S(-/+) ,SG     ,SP     ,A )
 *    06            07 レーダ反射因子(32bit)[dBZ]         (**.***   |   -9.999 ~    09.999)
 *    07            08 視程(気象光学距離)[m]              (*****    |    0     ~ 20000    )
 *    08            09 サンプリング周期  [s]              (*****    |    0     ~ 03600    )
 *    09            10 信号振幅                           (*****    |    0     ~ 99999    )
 *    10            11 粒子数                             (*****    |    0     ~ 99999    )
 *    11            12 センサ内温度[°C]                   (***      |  -99     ~   100    )
 *             (-)  13 センサシリアルナンバー             (******)
 *             (-)  14 IOPバージョン                      (******)
 *    12            15 DSPバージョン                      (******)
 *    13            16 加熱電流[A]                        (*.**     |    0.00  ~     4.00 )
 *    14            17 電源電圧[V]                        (**.*     |    0.0   ~    30.0  )
 *    15            18 センサのステータス                 (*        |    0     ~     3    )
 *                                                                       0 : Everything OK
 *                                                                       1 : Laser protective glass is dirty, but measurements are still possible
 *                                                                       2 : Laser protective glass is dirty, partially covered. No further usable measurements are possible.
 *                                                                       3 : Laser damaged
 *    16            19 観測開始時間                       (DD.MM.YYYY_hh:mm:ss)
 *    17            20 センサの時間                       (hh:mm:ss)
 *    18            21 センサの日時                       (DD.MM.YYYY)
 *    19            22 基地局名                           (****)
 *             (-)  23 基地局番号                         (****)
 *             (X)  24 降雨量(32bit)[mm]                  (***.***  |  000.000 ~   999.999)
 *             (X)  25 エラーコード                       (***)
 *             (X)  26 PCBの温度[°C]                      (***      |  -99     ~   100    )
 *             (X)  27 右センサヘッドの温度[°C]           (***      |  -99     ~   100    )
 *             (X)  28 左センサヘッドの温度[°C]           (***      |  -99     ~   100    )
 *             (U)  29
 *             (X)  30 降雨強度(16bit,最高  30)[mm/h]     (**.***   |    0.000 ~    30.000)
 *             (X)  31 降雨強度(16bit,最高1200)[mm/h]     (****.*   | 0000.0   ~  1200.0  )
 *             (X)  32 積算降雨量(16bit)[mm]              (****.**  | 0000.00  ~  0300.00 )
 *             (X)  33 レーダ反射因子(16bit)[dBZ]         (**.**    |   -9.99  ~     9.99 )
 *    20            34 運動エネルギー[J/(m^2h)]           (***.***  |  000.000 ~   999.999)
 *    21            35 降雪強度[mm/h]                     (****.**  | 0000.00  ~  9999.99 )
 *             (U)  36-89
 *    22            90 粒径分布 [log_{10} (1/m3 mm)]      (**.***;  |  -9.999  ~    99.999) x 32
 *    23            91 落下速度 [m/s]                     (**.***;  |   0.000  ~    99.999) x 32
 *             (U)  92
 *    24            93 生データ                           (***;     | 000      ~   999    ) x 32 x 32
 *
 *                  (U) : 未使用, (X) : Manualに記載のデータであるが, 観測データに出力されていないデータ, (-) データは存在するが, L1 CDFで除外するもの
 *
 *   <<< データ除外の理由 >>>
 *     No.06 : No.05と重複する情報であるため
 *     No.13 : No.22(基地局名)に含まれるため
 *     No.14 : IOPが何なのかManualに説明されておらず, 用途不明なため
 *     No.23 : 常に空白データとなっているため
 *
 *   <<< 参考文献 >>>
 *     1. Parsivel Manual (Operating instructions Present Weather Sensor OTT Parsivel^2)
 *
 *****************************************************************/

#ifndef _CDF_L1_PARSIVEL_H_INCLUDE_
#define _CDF_L1_PARSIVEL_H_INCLUDE_

#include"CDF_COMMON.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    typedef struct{                                 //対応データNo.    DEPEND0 DEPEND1 DEPEND2 依存関係                  UNITS            SCALETYP(基本的にlinearで, ダイナミックレンジ(値の最小・最大の幅)が広くグラフが見づらい場合にlogとします. 一般的な例を以下に記載します. )
        CDF__REAL4          rain_intensity;           //01               epoch   -       -       (時刻)                    mm/h             linear
        CDF__REAL4          accumulated_rain_amount;  //02               epoch   -       -       (時刻)                    mm               linear
        CDF__INT2           weathercode_rain;         //03,04,05         epoch   -       -       (時刻)
        CDF__INT2           weathercode_snow;         //03,04,05         epoch   -       -       (時刻)
        CDF__INT2           weathercode_intensity;    //03,04,05         epoch   -       -       (時刻)
        CDF__REAL4          radar_reflectivity;       //07               epoch   -       -       (時刻)                    dBz              linear
        CDF__UINT2          MOR_visibility;           //08               epoch   -       -       (時刻)                    m                linear
        CDF__UINT2          sample_interval;          //09               epoch   -       -       (時刻)                    s                linear
        CDF__UINT4          signal_amplitude;         //10               epoch   -       -       (時刻)                                     log
        CDF__UINT4          particle_number;          //11               epoch   -       -       (時刻)                                     log
        CDF__INT2           temperature;              //12               epoch   -       -       (時刻)                    °C               linear
        CDF__CHAR           firmware_DSP_version;     //15               -       -       -       (時刻に依存しない固定値)
        CDF__REAL4          heating_current;          //16               epoch   -       -       (時刻)                    A                linear
        CDF__REAL4          power_supply_voltage;     //17               epoch   -       -       (時刻)                    V                linear
        CDF__UINT1          sensor_status;            //18               epoch   -       -       (時刻)
        CDF__TIME_TT2000    measurement_start_time;   //19               epoch   -       -       (時刻)                                     linear
        CDF__TIME_TT2000    epoch;                    //20,21            -       -       -
        CDF__CHAR           device_name[8];           //22               -       -       -       (時刻に依存しない固定値)
        CDF__REAL4          kinetic_energy;           //34               epoch   -       -       (時刻)                    J/(m^2h)         log
        CDF__REAL4          snow_intensity;           //35               epoch   -       -       (時刻)                    mm/h             linear
        CDF__REAL4          field_N[32];              //90               epoch   D       -       (時刻x粒径)               log_10(1/m^3 mm) linear
        CDF__REAL4          field_v[32];              //91               epoch   D       -       (時刻x粒径)               m/s              linear
        CDF__UINT2          Dv_histgram[32][32];      //93               epoch   D       v       (時刻x粒径x落下速度)                       linear
        //(Dv_histgram[粒径クラス番号 - 1][速度クラス番号 - 1])
        //補助情報(DEPENDの記述は必要なし)
        CDF__REAL4          D [32];                   //各クラスの平均粒径    (CDF_L1_PARSIVEL__D )
        CDF__REAL4          dD[32];                   //各クラスの粒径幅      (CDF_L1_PARSIVEL__dD)
        CDF__REAL4          v [32];                   //各クラスの平均落下速度 (CDF_L1_PARSIVEL__v )
        CDF__REAL4          dv[32];                   //各クラスの落下速度幅   (CDF_L1_PARSIVEL__dv)
    }CDF_L1_PARSIVEL__DATA;
    
    void CDF_L1_PARSIVEL__Create   (CDFid      *id_ptr,
                                    const char *filepath,const char *data_version);
    
    void CDF_L1_PARSIVEL__Set_gAttr(CDFid id);
    
    void CDF_L1_PARSIVEL__Set_vAttr(CDFid id);
    void CDF_L1_PARSIVEL__Set_zVars(CDFid id);
    
    void CDF_L1_PARSIVEL__Set_Data (CDF_L1_PARSIVEL__DATA *dat,CDFid id,long recNum);
    void CDF_L1_PARSIVEL__Get_Data (CDF_L1_PARSIVEL__DATA *dat,CDFid id,long recNum);
    
#ifdef __cplusplus
}
#endif

#endif
