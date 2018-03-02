/***************************************************************** 
 *
 * TEXT CSV
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"TEXT_CSV.h"

const CHAR *TEXT_CSV__SEARCH_CHARS(const CHAR *text,
				   const CHAR *chars){
  INT4 n,m;

  for(n = 0;text[n] != '\0';n++){
    for(m = 0;chars[m] != '\0';m++){
      if(text[n] == chars[m]){
	return &text[n];
      }
    }
  }
  return NULL;
}

INT4        TEXT_CSV__DECOMPOSITION(TEXT_CSV   *csv,
				    const CHAR *text,
				    const CHAR *delimiters){
  INT4 n,m,k,c;
  INT4 state;
  INT4 ctype;
  INT4 isrec;

  strncpy(csv->buf,text,TEXT_CSV__BUFLEN);
  csv->num = 0;
  isrec    = 0;
  state    = 0;
  for(n = 0;n < TEXT_CSV__BUFLEN;n++){
    if(csv->buf[n] == '"'){
      state = (state == 0) ? 1 : 0;
    }
    if((state == 0) && ((csv->buf[n] == '\r') || (csv->buf[n] == '\n') || (csv->buf[n] == '\0'))){
      break;
    }    
    ctype = 0;
    for(m = 0;delimiters[m] != '\0';m++){
      if(csv->buf[n] == delimiters[m]){
	ctype = (delimiters[m] == ' ') ? 1 : 2;
	break;
      }
    }
    if(state == 0){
      if(!isrec && (ctype == 2)){
	if(csv->num >= TEXT_CSV__MAXNUM){
	  fprintf(stderr,"[ERROR : TEXT_CSV__DECOMPOSITION]\n");
	  return -1;
	}
	csv->ptr[csv->num] = &csv->buf[n];
	csv->num++;
      }
      if(ctype > 0){
	csv->buf[n] = '\0';
	isrec = 0;
	continue;
      }
    }
    if(!isrec){
      if(csv->num >= TEXT_CSV__MAXNUM){
	fprintf(stderr,"[ERROR : TEXT_CSV__DECOMPOSITION]\n");
	return -1;
      }
      csv->ptr[csv->num] = &csv->buf[n];
      csv->num++;
      isrec = 1;
    }
  }

  for(k = 0;k < csv->num;k++){
    state = 0;
    c     = 0;
    for(n = 0;;n++){
      switch(state){
      case 0:
	if(csv->ptr[k][n] == '"'){
	  state = 1;
	}else{
	  csv->mem[c] = csv->ptr[k][n];
	  c++;
	}
	break;
      case 1:
	if(csv->ptr[k][n] == '"'){
	  state = 2;
	}else{
	  csv->mem[c] = csv->ptr[k][n];
	  c++;
	}
	break;
      case 2:
	if(csv->ptr[k][n] == '"'){
	  state = 1;
	}else{
	  state = 0;
	}
	csv->mem[c] = csv->ptr[k][n];
	c++;
	break;
      }
      if(csv->ptr[k][n] == '\0'){
	break;
      }
    }
    if(state > 0){
      fprintf(stderr,"[WARNING : TEXT_CSV__DECOMPOSITION]\n");
    }
    if(c == 0){
      csv->ptr[k][0] = '\0';
    }else{
      strcpy(csv->ptr[k],csv->mem);
    }
  }

  return 0;
}

INT8        TEXT_CSV__GET_NUM_ROWS (FILE       *fp,
				    const CHAR *comment_chars){
  INT8  pos;
  CHAR  buf[TEXT_CSV__BUFLEN]; 
  INT8  num;

  pos = ftell(fp);  

  fseek(fp,0L ,SEEK_SET);

  num = 0L;
  while(fgets(buf,TEXT_CSV__BUFLEN,fp) != NULL){
    if(TEXT_CSV__SEARCH_CHARS(buf,"\r\n") == NULL){
      fprintf(stderr,"[ERROR : TEXT_CSV__GET_NUM_ROWS]\n");      
      return -1L;
    }
    if(strchr(comment_chars,buf[0]) != NULL){
      continue;
    }
    num++;
  }

  fseek(fp,pos,SEEK_SET);

  return num;
}

INT4        TEXT_CSV__READ_LINE    (TEXT_CSV   *csv,
				    FILE       *fp,
				    const CHAR *delimiters,
				    const CHAR *comment_chars){
  while(fgets(csv->mem,TEXT_CSV__BUFLEN,fp) != NULL){
    if(TEXT_CSV__SEARCH_CHARS(csv->mem,"\r\n") == NULL){
      fprintf(stderr,"[ERROR : TEXT_CSV__READ_LINE]\n");      
      return -1;
    }
    if(strchr(comment_chars,csv->mem[0]) != NULL){
      continue;
    }
    return TEXT_CSV__DECOMPOSITION(csv,csv->mem,delimiters);
  }  
  return -1;
}

CHAR       *TEXT_CSV__GET_DATA     (TEXT_CSV   *csv,
				    INT4        col){
  if((0 <= col) && (col < csv->num)){
    return csv->ptr[col];
  }else{
    csv->nul = '\0';
    return &csv->nul;
  }
}
