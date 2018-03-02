/***************************************************************** 
 *
 * SVGPLOT AUTOTICS
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#ifndef _SVGPLOT_AUTOTICS_H_INCLUDE_
#define _SVGPLOT_AUTOTICS_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include"SVG_BASE.h"
#include"SVGPLOT_TICS.h"

void SVGPLOT__AUTOTICS_REAL8           (REAL8              tics1[],
					INT4              *tics1num,
					REAL8              tics2[],
					INT4              *tics2num,
					REAL8              valmin,
					REAL8              valmax,
					SVGPLOT__SCALETYPE scaletype);

void SVGPLOT__AUTOTICS_TIME_TT2000     (TIME_TT2000        tics1[],
					INT4              *tics1num,
					TIME_TT2000        tics2[],
					INT4              *tics2num,
					TIME_TT2000        tmin,
					TIME_TT2000        tmax);

void SVGPLOT__AUTOTICS_TIME_TT2000_HHMM(TIME_TT2000        tics1[],
					INT4              *tics1num,
					TIME_TT2000        tics2[],
					INT4              *tics2num,
					TIME_TT2000        tmin,
					TIME_TT2000        tmax,
					INT4               dt1,
					INT4               dt2);//時間刻み[min]

void SVGPLOT__AUTOTICS_TIME_TT2000_DATE(TIME_TT2000        tics1[],
					INT4              *tics1num,
					TIME_TT2000        tics2[],
					INT4              *tics2num,
					TIME_TT2000        tmin,
					TIME_TT2000        tmax,
					INT4               dt1,
					INT4               dt2);//時間刻み[day]

#ifdef __cplusplus
}
#endif

#endif
