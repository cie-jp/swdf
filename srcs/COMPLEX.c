/***************************************************************** 
 *
 * 複素数型
 *
 *
 *                           Created  by Mamoru Ota (2018/01/25)
 * 
 *****************************************************************/

#include<math.h>
#include"COMPLEX.h"

REAL8   COMPLEX__REAL      (COMPLEX z){
  return z.real;
}

REAL8   COMPLEX__IMAG      (COMPLEX z){
  return z.imag;
}

REAL8   COMPLEX__NORM      (COMPLEX z){
  return z.real * z.real + z.imag * z.imag;
}

REAL8   COMPLEX__ABS       (COMPLEX z){
  return sqrt(COMPLEX__NORM(z));
}

REAL8   COMPLEX__ARG       (COMPLEX z){
  return atan2(z.imag,z.real);
}

COMPLEX COMPLEX__MAKE_RE_IM(REAL8   real,
			    REAL8   imag){
  COMPLEX z;
  
  z.real = real;
  z.imag = imag;
  
  return z;
}  

COMPLEX COMPLEX__MAKE_ZERO (){
  return COMPLEX__MAKE_RE_IM( 0.0, 0.0);
}

COMPLEX COMPLEX__MAKE_REAL (REAL8   real){
  return COMPLEX__MAKE_RE_IM(real, 0.0);
}

COMPLEX COMPLEX__MAKE_IMAG (REAL8   imag){
  return COMPLEX__MAKE_RE_IM( 0.0,imag);
}

COMPLEX COMPLEX__MAKE_POLAR(REAL8   r,
			    REAL8   theta){
  return COMPLEX__MAKE_RE_IM(r * cos(theta),r * sin(theta));
}

COMPLEX COMPLEX__CONJ      (COMPLEX z){
  return COMPLEX__MAKE_RE_IM(+z.real,-z.imag);
}

COMPLEX COMPLEX__INV       (COMPLEX z){
  REAL8   z_norm;
  
  z_norm = COMPLEX__NORM(z);
  return COMPLEX__MAKE_RE_IM(z.real / z_norm,-z.imag / z_norm);
}

COMPLEX COMPLEX__POW       (COMPLEX z,
			    REAL8   p){
  return COMPLEX__MAKE_POLAR(pow(COMPLEX__ABS(z),p),COMPLEX__ARG(z) * p);
}


COMPLEX COMPLEX__ADD       (COMPLEX z1,
			    COMPLEX z2){
  return COMPLEX__MAKE_RE_IM(z1.real + z2.real,z1.imag + z2.imag);
}

COMPLEX COMPLEX__SUB       (COMPLEX z1,
			    COMPLEX z2){
  return COMPLEX__MAKE_RE_IM(z1.real - z2.real,z1.imag - z2.imag);
}

COMPLEX COMPLEX__MUL       (COMPLEX z1,
			    COMPLEX z2){
  return COMPLEX__MAKE_RE_IM(z1.real * z2.real - z1.imag * z2.imag,z1.real * z2.imag + z1.imag * z2.real);
}

COMPLEX COMPLEX__DIV       (COMPLEX z1,
			    COMPLEX z2){
  return COMPLEX__MUL(z1,COMPLEX__INV(z2));
}

COMPLEX COMPLEX__POLYNOMIAL(COMPLEX z,
			    COMPLEX a[],
			    INT4    n){
  COMPLEX f;
  INT4    i;
  
  f = a[0];
  for(i = 1;i <= n;i++){
    f = COMPLEX__ADD(f,COMPLEX__MUL(a[i],COMPLEX__POW(z,(REAL8)i)));
  }
  return f;
}
