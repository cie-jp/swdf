/***************************************************************** 
 *
 * メモリ管理
 *
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/

#ifndef _MEMORY_H_INCLUDE_
#define _MEMORY_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#define ERROR__SHOW(comment)              fprintf(stderr,"=== ERROR ===\nfile  name  : %s\nfunc. name  : %s\nline number : %d\ncomment     : %s\n",__FILE__,__func__,__LINE__,comment)

#define MEMORY__NEW(mem,type,num,comment) if((mem = (type*)malloc(sizeof(type) * (num))) == NULL){ERROR__SHOW(comment);exit(EXIT_FAILURE);}
#define MEMORY__DEL(mem)                  free(mem)
  
#ifdef __cplusplus
}
#endif

#endif
