/***************************************************************** 
 *
 * TEXT CSV
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#ifndef _TEXT_CSV_H_INCLUDE_
#define _TEXT_CSV_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include<stdio.h>
#include"DATATYPE.h"

#define TEXT_CSV__BUFLEN (1024 * 1024)
#define TEXT_CSV__MAXNUM (512)
  
  typedef struct{
    CHAR  mem[TEXT_CSV__BUFLEN];//作業用バッファ1
    CHAR  buf[TEXT_CSV__BUFLEN];//作業用バッファ2
    CHAR  nul;
    CHAR *ptr[TEXT_CSV__MAXNUM];
    INT4  num;
  }TEXT_CSV;

  const CHAR *TEXT_CSV__SEARCH_CHARS (const CHAR *text,
				      const CHAR *chars);

  INT4        TEXT_CSV__DECOMPOSITION(TEXT_CSV   *csv,
				      const CHAR *text,
				      const CHAR *delimiters);

  INT8        TEXT_CSV__GET_NUM_ROWS (FILE       *fp,
				      const CHAR *comment_chars);

  INT4        TEXT_CSV__READ_LINE    (TEXT_CSV   *csv,
				      FILE       *fp,
				      const CHAR *delimiters,
				      const CHAR *comment_chars);

  CHAR       *TEXT_CSV__GET_DATA     (TEXT_CSV   *csv,
				      INT4        col);
  
#ifdef __cplusplus
}
#endif

#endif
