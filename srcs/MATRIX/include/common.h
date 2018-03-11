/***************************************************************** 
 *
 * 行列計算共通ヘッダ
 *
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"MATRIX.h"

#define T__ZERO     JOINT(TYPE,__ZERO)
#define T__ONE      JOINT(TYPE,__ONE )
#define T__TWO      JOINT(TYPE,__TWO )
#define T__MAKE     JOINT(TYPE,__MAKE)
#define T__REAL     JOINT(TYPE,__REAL)
#define T__POSITIVE JOINT(TYPE,__POSITIVE)
#define T__NEGATIVE JOINT(TYPE,__NEGATIVE)
#define T__ABS      JOINT(TYPE,__ABS  )
#define T__NORM     JOINT(TYPE,__NORM )
#define T__EQ       JOINT(TYPE,__EQ   )
#define T__NEQ      JOINT(TYPE,__NEQ  )
#define T__ADD      JOINT(TYPE,__ADD  )
#define T__SUB      JOINT(TYPE,__SUB  )
#define T__MUL      JOINT(TYPE,__MUL  )
#define T__DIV      JOINT(TYPE,__DIV  )
#define T__FMA      JOINT(TYPE,__FMA  )
#define T__PRINT    JOINT(TYPE,__PRINT)

#define T__MATRIX_LU_DECOMPOSITION  JOINT(TYPE,__MATRIX_LU_DECOMPOSITION )
#define T__MATRIX_LUP_DECOMPOSITION JOINT(TYPE,__MATRIX_LUP_DECOMPOSITION)
#define T__MATRIX_INV               JOINT(TYPE,__MATRIX_INV)
#define T__MATRIX_SOLVE             JOINT(TYPE,__MATRIX_SOLVE)
#define T__MATRIX_PRINT             JOINT(TYPE,__MATRIX_PRINT)
#define T__MATRIX_MUL               JOINT(TYPE,__MATRIX_MUL)

#define T__MATRIX_BIDIAGONALIZATION JOINT(TYPE,__MATRIX_BIDIAGONALIZATION)
