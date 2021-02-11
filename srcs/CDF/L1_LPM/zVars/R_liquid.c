/*****************************************************************
 *
 * CDF操作関連ライブラリ
 *
 *    LPM共通 L1 z変数 R_liquid [REAL4型]
 *    降雨強度[mm/h]
 *
 *****************************************************************/

#include"zVar_header.h"

// **********************************************
//  zVariable
// **********************************************

#define varName R_liquid
#define varType REAL4

#define numElems          1
#define numDims           0                     //配列数
#define dimSizes    {    0,    0,     0}//配列サイズ
#define dimVarys    {  VARY,  VARY,  VARY}      //配列の変化の有無
#define recVariance    VARY                     //

// **********************************************
//  vAttribute (ISTP/IACG Guidelines)
// **********************************************

#define FILLVAL      0.000                      //データが欠損しているところに入れる値
#define VALIDMIN     0.000                      //データの最小値
#define VALIDMAX     9999.999                   //データの最大値
#define CATDESC      "R_liquid"                        //変数の説明
#define FIELDNAM     TSTR(varName)              //変数名
#define VAR_TYPE     "data"                     //変数の識別子（data/support_data/metadataなど)
//#define VAR_NOTES    "."                      //変数に関する補助的な説明
//#define DICT_KEY     "."                      //データカテゴリ
//#define MONOTON      "."                      //レコード番号に対してZ変数地が単調増加ならINCREASE,
//単調減少ならDECREASE, それ以外なら未定義
#define UNITS        "mm/h"                      //単位
//#define UNIT_PTR     "."                      //単位（ベクトル）
//#define UNITS_PTR    "."                      //無視
#define DEPEND_0     "epoch"                    //時間変化以外の依存関係を持つデータ
//#define DEPEND_1     "."                  　          //依存関係を持つ情報を格納した変数名を記す
//#define DEPEND_2     "."
//#define DEPEND_3     "."
//#define FORMAT       "."                      //描画またはファイル出力する際のファーマット
//#define FORM_PTR     "."                      //出力フォーマット
//#define DISPLAY_TYPE "."                      //データの描画方法（spectrogram/time_seriesなど）
#define SCALETYP     "linear"                   //グラフ描画時のスケールの指定(線形"linear"/対数"log")
#define LABLAXIS     TSTR(varName)              //y軸のラベル名
//#define LABL_PTR_1   "."                      //多次元データでのラベル
//#define LABL_PTR_2   "."
//#define LABL_PTR_3   "."
//#define BUNDLE_1     "."                      //無視

#include"zVar_footer.h"
