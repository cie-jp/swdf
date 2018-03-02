/*****************************************************************
 *
 * データ型のサイズ検証プログラム
 * 
 *
 *                           Created  by Mamoru Ota (2017/06/14)
 * 
 *****************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"DATATYPE.h"

int main(int argc,const char *argv[]){
  if(sizeof(CHAR       ) !=  1){
    fprintf(stderr,"Data Type Validation : ERROR [%s]\n","CHAR"       );
    return EXIT_FAILURE;
  }
  if(sizeof(UCHAR      ) !=  1){
    fprintf(stderr,"Data Type Validation : ERROR [%s]\n","UCHAR"      );
    return EXIT_FAILURE;
  }
  if(sizeof(BYTE       ) !=  1){
    fprintf(stderr,"Data Type Validation : ERROR [%s]\n","BYTE"       );
    return EXIT_FAILURE;
  }
  if(sizeof(INT1       ) !=  1){
    fprintf(stderr,"Data Type Validation : ERROR [%s]\n","INT1"       );
    return EXIT_FAILURE;
  }
  if(sizeof(INT2       ) !=  2){
    fprintf(stderr,"Data Type Validation : ERROR [%s]\n","INT2"       );
    return EXIT_FAILURE;
  }
  if(sizeof(INT4       ) !=  4){
    fprintf(stderr,"Data Type Validation : ERROR [%s]\n","INT4"       );
    return EXIT_FAILURE;
  }
  if(sizeof(INT8       ) !=  8){
    fprintf(stderr,"Data Type Validation : ERROR [%s]\n","INT8"       );
    return EXIT_FAILURE;
  }
  if(sizeof(UINT1      ) !=  1){
    fprintf(stderr,"Data Type Validation : ERROR [%s]\n","UINT1"      );
    return EXIT_FAILURE;
  }
  if(sizeof(UINT2      ) !=  2){
    fprintf(stderr,"Data Type Validation : ERROR [%s]\n","UINT2"      );
    return EXIT_FAILURE;
  }
  if(sizeof(UINT4      ) !=  4){
    fprintf(stderr,"Data Type Validation : ERROR [%s]\n","UINT4"      );
    return EXIT_FAILURE;
  }
  if(sizeof(FLOAT      ) !=  4){
    fprintf(stderr,"Data Type Validation : ERROR [%s]\n","FLOAT"      );
    return EXIT_FAILURE;
  }
  if(sizeof(DOUBLE     ) !=  8){
    fprintf(stderr,"Data Type Validation : ERROR [%s]\n","DOUBLE"     );
    return EXIT_FAILURE;
  }
  if(sizeof(REAL4      ) !=  4){
    fprintf(stderr,"Data Type Validation : ERROR [%s]\n","REAL4"      );
    return EXIT_FAILURE;
  }
  if(sizeof(REAL8      ) !=  8){
    fprintf(stderr,"Data Type Validation : ERROR [%s]\n","REAL8"      );
    return EXIT_FAILURE;
  }
  if(sizeof(EPOCH      ) !=  8){
    fprintf(stderr,"Data Type Validation : ERROR [%s]\n","EPOCH"      );
    return EXIT_FAILURE;
  }
  if(sizeof(EPOCH16    ) != 16){
    fprintf(stderr,"Data Type Validation : ERROR [%s]\n","EPOCH16"    );
    return EXIT_FAILURE;
  }
  if(sizeof(TIME_TT2000) !=  8){
    fprintf(stderr,"Data Type Validation : ERROR [%s]\n","TIME_TT2000");
    return EXIT_FAILURE;
  }
  if(sizeof(RGBA       ) !=  4){
    fprintf(stderr,"Data Type Validation : ERROR [%s]\n","RGBA"      );
    return EXIT_FAILURE;
  }

  fprintf(stdout,"Data Type Validation : OK\n");
  return EXIT_SUCCESS;
}
