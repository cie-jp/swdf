/***************************************************************** 
 *
 * 基本関数
 *
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/

#include"MATRIX.h"

REAL REAL__ZERO    (){
  return  0;
}

REAL REAL__ONE     (){
  return  1;
}

REAL REAL__POSITIVE(REAL x){
  return +x;
}

REAL REAL__NEGATIVE(REAL x){
  return -x;
}

REAL REAL__ABS     (REAL x){
  return fabs(x);
}

INT  REAL__EQ      (REAL x,REAL y){
  return x == y;
}

INT  REAL__NEQ     (REAL x,REAL y){
  return x != y;
}

REAL REAL__ADD     (REAL x,REAL y){
  return  x + y;
}

REAL REAL__SUB     (REAL x,REAL y){
  return  x - y;
}

REAL REAL__MUL     (REAL x,REAL y){
  return  x * y;
}

REAL REAL__DIV     (REAL x,REAL y){
  return  x / y;
}

REAL REAL__FMA     (REAL x,REAL y,REAL z){
  return  fma(x,y,z);
}

INT  REAL__GT      (REAL x,REAL y){
  return  x >  y;
}

INT  REAL__GE      (REAL x,REAL y){
  return  x >= y;
}

INT  REAL__LT      (REAL x,REAL y){
  return  x <  y;
}

INT  REAL__LE      (REAL x,REAL y){
  return  x <= y;
}

void REAL__PRINT   (REAL x,FILE *fp){
  fprintf(fp,"%10.5f",x);
}

COMP COMP__ZERO    (){
  return  COMPLEX__MAKE_ZERO();
}

COMP COMP__ONE     (){
  return  COMPLEX__MAKE_REAL(1.0);
}

COMP COMP__POSITIVE(COMP x){
  return  x;
}

COMP COMP__NEGATIVE(COMP x){
  return  COMPLEX__MAKE_RE_IM(-COMPLEX__REAL(x),-COMPLEX__IMAG(x));
}

REAL COMP__ABS     (COMP x){
  return  COMPLEX__ABS(x);
}

INT  COMP__EQ      (COMP x,COMP y){
  return (COMPLEX__REAL(x) == COMPLEX__REAL(y)) && (COMPLEX__IMAG(x) == COMPLEX__IMAG(y));
}

INT  COMP__NEQ     (COMP x,COMP y){
  return (COMPLEX__REAL(x) != COMPLEX__REAL(y)) || (COMPLEX__IMAG(x) != COMPLEX__IMAG(y));
}

COMP COMP__ADD     (COMP x,COMP y){
  return  COMPLEX__ADD(x,y);
}

COMP COMP__SUM     (COMP x,COMP y){
  return  COMPLEX__SUB(x,y);
}

COMP COMP__MUL     (COMP x,COMP y){
  return  COMPLEX__MUL(x,y);
}

COMP COMP__DIV     (COMP x,COMP y){
  return  COMPLEX__DIV(x,y);
}

COMP COMP__FMA     (COMP x,COMP y,COMP z){
  return  COMPLEX__ADD(COMPLEX__MUL(x,y),z);
}

void COMP__PRINT   (COMP x,FILE *fp){
  fprintf(fp,"(%10.5f,%10.5f)",COMPLEX__REAL(x),COMPLEX__IMAG(x));
}
