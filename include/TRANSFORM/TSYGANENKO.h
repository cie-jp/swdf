/*****************************************************************
 * 
 * Tsyganenko 2005
 *
 *                           Created  by Mamoru Ota (2017/11/15)
 *
 *****************************************************************/ 

#ifndef _TSYGANENKO_H_INCLUDE_
#define _TSYGANENKO_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

void Tsyganenko_2005(double *brr,
		     double *bth,
		     double *bph,
		     double  r,    
		     double  theta,
		     double  phi,  
		     int     year,
		     int     month,
		     int     day,
		     int     hour,
		     int     minute,
		     double  second);
  
#ifdef __cplusplus
}
#endif

#endif
