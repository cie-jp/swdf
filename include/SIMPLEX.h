/***************************************************************** 
 *
 * Simplex法
 *
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/

#ifndef _SIMPLEX_H_INCLUDE_
#define _SIMPLEX_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include<stdio.h>
#include<math.h>
#include<float.h>

/**************************************************************************/
//Simplex Method Phase 1
//c(col)
//A(row x col)
//b(row)         : b >= 0
//T(col)         : an array of basic variable index
//eps            : allowable error
//is_nonnegative 
/**************************************************************************/
int simplex_phase1(double c[],double *A,double b[],int T[],int row,int col,double eps,int is_nonnegative);

/**************************************************************************/
//Simplex Method Phase 2
//x(col)
//c(col)
//A(row x col)
//b(row) : b >= 0
//T(col) : an array of basic variable index
/**************************************************************************/
int simplex_phase2(double x[],double c[],double *A,double b[],int T[],int row,int col);

/**************************************************************************/
//Reviced Simplex Method 0
//x* = argmin sum ci * |xi| subject to b = Ax, x >= 0
//x(col)
//c(col)
//A(row x col)
//b(row)
//is_nonnegative
/**************************************************************************/
int reviced_simplex0(double x[],double c[],double *A,double b[],int row,int col,int is_nonnegative);

/**************************************************************************/
//Reviced Simplex Method 1
//x* = argmin sum ci * |xi| subject to b = Ax, x >= 0
//x(col)
//c(col)
//A(row x col)
//b(row)
/**************************************************************************/
int reviced_simplex1(double x[],double c[],double *A,double b[],int row,int col);

/**************************************************************************/
//Reviced Simplex Method 2
//x* = argmin sum ci * |xi| subject to b = Ax
//x(col)
//c(col)
//A(row x col)
//b(row)
/**************************************************************************/
int reviced_simplex2(double x[],double c[],double *A,double b[],int row,int col);

#ifdef __cplusplus
}
#endif
  
#endif
