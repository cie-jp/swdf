/***************************************************************** 
 *
 * CLDIA (Common Library for Data Integration and Analysis) 
 *
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/

#include"DTIME.h"

#include"FFT.h"
#include"RANDOM.h"
#include"SVG/SVGPLOT.h"
#include"MATRIX.h"
#include"COMPLEX.h"
#include"CDF_COMMON.h"

#include"CL31.h"

#ifdef __cplusplus

#include"CPP/STRINGS.h"

#include"CPP/TMatrix.h"

typedef TMatrix<REAL>        RMatrix;
typedef TMatrix<COMP>        CMatrix;
typedef TMatrix<TIME_TT2000> EMatrix;

typedef TVector<REAL>        RVector;
typedef TVector<COMP>        CVector;
typedef TVector<TIME_TT2000> EVector;

#include"CPP/ERG_orbit.h"

#endif
