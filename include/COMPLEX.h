/***************************************************************** 
 *
 * 複素数型
 *
 *
 *                           Created  by Mamoru Ota (2018/01/25)
 * 
 *****************************************************************/

#ifndef _COMPLEX_H_INCLUDE_
#define _COMPLEX_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include"DATATYPE.h"

  typedef struct{
    REAL8 real;
    REAL8 imag;
  }COMPLEX;

  REAL8   COMPLEX__REAL      (COMPLEX z);
  REAL8   COMPLEX__IMAG      (COMPLEX z);
  REAL8   COMPLEX__NORM      (COMPLEX z);
  REAL8   COMPLEX__ABS       (COMPLEX z);
  REAL8   COMPLEX__ARG       (COMPLEX z);
  COMPLEX COMPLEX__MAKE_RE_IM(REAL8   real,
			      REAL8   imag);
  COMPLEX COMPLEX__MAKE_ZERO ();
  COMPLEX COMPLEX__MAKE_REAL (REAL8   real);
  COMPLEX COMPLEX__MAKE_IMAG (REAL8   imag);
  COMPLEX COMPLEX__MAKE_POLAR(REAL8   r,
			      REAL8   theta);
  COMPLEX COMPLEX__CONJ      (COMPLEX z);
  COMPLEX COMPLEX__INV       (COMPLEX z);
  COMPLEX COMPLEX__POW       (COMPLEX z,
			      REAL8   p);
  COMPLEX COMPLEX__ADD       (COMPLEX z1,
			      COMPLEX z2);
  COMPLEX COMPLEX__SUB       (COMPLEX z1,
			      COMPLEX z2);
  COMPLEX COMPLEX__MUL       (COMPLEX z1,
			      COMPLEX z2);
  COMPLEX COMPLEX__DIV       (COMPLEX z1,
			      COMPLEX z2);
  //f(z) = sum _{i=0}^{n} [a_{i}z^{i}]
  COMPLEX COMPLEX__POLYNOMIAL(COMPLEX z,
			      COMPLEX a[],//[1 + n]
			      INT4    n);
  
#ifdef __cplusplus
}
#endif

#endif
