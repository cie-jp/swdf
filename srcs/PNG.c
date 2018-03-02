/***************************************************************** 
 *
 * PNGファイル操作
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include  <zlib.h>
#include   "PNG.h"
#include   "BASE64_ENCODER.h"

UINT4 PNG__Calc_CRC       (UINT1 buf[],int             num);
void  PNG__Write_4B       (UINT4 val  ,FILE           *fp );
void  PNG__Write_4B_BASE64(UINT4 val  ,BASE64_ENCODER *enc);

UINT4 PNG__Calc_CRC       (UINT1 buf[],int             num){
  static UINT4 tbl[256];
  static INT4  flg =  1;
  UINT4  c;
  INT4   n,k;

  if(flg == 1){
    for(n = 0;n < 256;n++){
      c = (UINT4)n;
      for(k = 0;k < 8;k++){
	c = (c & 0x01) ? (0xEDB88320L ^ (c >> 1)) : (c >> 1);
      }
      tbl[n]  =   c;
    }
    flg = 0;
  }
  c   =  0xFFFFFFFFL;
  for(n = 0;n <  num;n++){
    c = tbl[(c ^ buf[n]) & 0xFF] ^ (c >> 8);
  }
  return 0xFFFFFFFFL ^ c;  
}

void  PNG__Write_4B       (UINT4 val  ,FILE           *fp ){
  UINT1 tmp[4];

  tmp[0] = (val >> 24) & 0xFF;
  tmp[1] = (val >> 16) & 0xFF;
  tmp[2] = (val >>  8) & 0xFF;
  tmp[3] =  val        & 0xFF;
  fwrite(tmp,1,4,fp);
}

void  PNG__Write_4B_BASE64(UINT4 val  ,BASE64_ENCODER *enc_ptr){
  UINT1 tmp[4];

  tmp[0] = (val >> 24) & 0xFF;
  tmp[1] = (val >> 16) & 0xFF;
  tmp[2] = (val >>  8) & 0xFF;
  tmp[3] =  val        & 0xFF;
  BASE64_ENCODER__ReadBytes (enc_ptr,tmp,4);
}


IMAGE load_png(const char *path,int *width,int    *height){
  UINT1  png[ 16] = {0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A,
		     0x00,0x00,0x00,0x0D,0x49,0x48,0x44,0x52};
  UINT1  buf[ 33];
  UINT1  rgb[256][3];
  UINT4 w,h,t,n,p;
  UINT4 siz;
  UINT1 *zip;
  UINT1 *ptr;
  UINT1 *img;
  UINT1 *scn;
  uLongf num;
  int    x,y,q;
  int    a,b,c,z;
  int    ll,tt,lt;
  FILE  *fp;

  if(path != NULL){
    fp = fopen(path,"rb");
    if(fp == NULL){
      return NULL;
    }
  }else{
    fp = stdin;
  }
  if(fread(buf,1,33,fp) <= 0){
    if(fp != stdin){
      fclose(fp);
    }
    return NULL;
  }
  if(memcmp(png,buf,16) != 0){
    if(fp != stdin){
      fclose(fp);
    }
    return NULL;
  } 
  w   = (buf[16] << 24) | (buf[17] << 16) | (buf[18] << 8) | buf[19];
  h   = (buf[20] << 24) | (buf[21] << 16) | (buf[22] << 8) | buf[23];
  t   =((buf[25] ==  2) ||(buf[25] ==  3))?  3 : 4;
  p   = (buf[25] ==  3) ?  1 : 0;
  n   = (1 + t) * w * h *  2;
  if((buf[24] != 8) || ((buf[25] != 2) && 
     (buf[25] != 3) &&  (buf[25] != 6))){
    if(fp != stdin){
      fclose(fp);
    }
    return NULL;
  }  
  if((buf[26] != 0) ||  (buf[27] != 0) || (buf[28] != 0) ){
    if(fp != stdin){
      fclose(fp);
    }
    return NULL;
  }
  if((ptr = zip  = (UINT1*)malloc(n))  ==  NULL){
    if(fp != stdin){
      fclose(fp);
    }
    return NULL;
  }
  while(fread(buf,1,8,fp) > 0){
    siz  =  (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
    if(memcmp(buf + 4,"IDAT",4) == 0){
      fread(ptr, 1, siz, fp);
      ptr  += siz;
    }else
    if(memcmp(buf + 4,"PLTE",4) == 0){
      fread(rgb[0],1,siz,fp);
    }else{
      fseek(fp,siz,SEEK_CUR);
    }
      fseek(fp, 4L,SEEK_CUR);
    if(memcmp(buf + 4,"IEND",4) == 0){
      break;
    }
  }
  if(fp != stdin){
    fclose(fp);
  }
  siz = (UINT4)(ptr - zip);
  num = (uLongf)(n   - siz);
  if(uncompress(ptr,&num,zip,siz) != Z_OK){
    free(zip);
    return NULL;
  }
  q   =  4 * w;
  siz =  q * h;
  if((img  = (UINT1*)malloc(siz)) == NULL){
    free(zip);
    return NULL;
  }
  scn  =  img;
  if(t == 0x03){
    if(p == 1){
      for(y = 0;y < h;y++){
	ptr++;
	for(x = 0;x < w;x++){
	  scn[0]  =  rgb[*ptr][0];
	  scn[1]  =  rgb[*ptr][1];
	  scn[2]  =  rgb[*ptr][2];
	  scn[3]  =  0xFF;
	  scn += 4;
	  ptr += 1;
	}
      }
    }else{
      switch(*ptr++){
      case 0x00:
      case 0x02:
	for(x = 0;x < q;x += 4){
	  scn[0]  =  ptr[0];
	  scn[1]  =  ptr[1];
	  scn[2]  =  ptr[2];
	  scn[3]  =  0xFF;
	  scn  += 4;
	  ptr  += 3;
	}
	break;
      case 0x01:
      case 0x03:
      case 0x04:
	scn[0]  =  ptr[0];
	scn[1]  =  ptr[1];
	scn[2]  =  ptr[2];
	scn[3]  =  0xFF;
	scn  += 4;
	ptr  += 3;
	for(x = 4;x < q;x += 4){
	  scn[0]  =  ptr[0] + scn[-4];
	  scn[1]  =  ptr[1] + scn[-3];
	  scn[2]  =  ptr[2] + scn[-2];
	  scn[3]  =  0xFF;
	  scn  += 4;
	  ptr  += 3;
	}
	break;
      }
      for(y = 1;y < h;y++){
	switch(*ptr++){
	case 0x00:
	  for(x = 0;x < q;x += 4){
	    scn[0]  =  ptr[0];
	    scn[1]  =  ptr[1];
	    scn[2]  =  ptr[2];
	    scn[3]  =  0xFF;
	    scn  += 4;
	    ptr  += 3;
	  }
	  break;
	case 0x01:
	  scn[0]  =  ptr[0];
	  scn[1]  =  ptr[1];
	  scn[2]  =  ptr[2];
	  scn[3]  =  0xFF;
	  scn  += 4;
	  ptr  += 3;
	  for(x = 4;x < q;x += 4){
	    scn[0]  =  ptr[0] + scn[-4];
	    scn[1]  =  ptr[1] + scn[-3];
	    scn[2]  =  ptr[2] + scn[-2];
	    scn[3]  =  0xFF;
	    scn  += 4;
	    ptr  += 3;
	  }
	  break;
	case 0x02:
	  for(x = 0;x < q;x += 4){
	    scn[0]  =  ptr[0] + scn[-q + 0];
	    scn[1]  =  ptr[1] + scn[-q + 1];
	    scn[2]  =  ptr[2] + scn[-q + 2];
	    scn[3]  =  0xFF;
	    scn  += 4;
	    ptr  += 3;
	  }
	  break;
	case 0x03:
	  scn[0]  =  ptr[0] + scn[-q + 0] / 2;
	  scn[1]  =  ptr[1] + scn[-q + 1] / 2;
	  scn[2]  =  ptr[2] + scn[-q + 2] / 2;
	  scn[3]  =  0xFF;
	  scn  += 4;
	  ptr  += 3;
	  for(x = 4;x < q;x += 4){
	    scn[0]  =  ptr[0] + (scn[-q + 0] + scn[-4]) / 2;
	    scn[1]  =  ptr[1] + (scn[-q + 1] + scn[-3]) / 2;
	    scn[2]  =  ptr[2] + (scn[-q + 2] + scn[-2]) / 2;
	    scn[3]  =  0xFF;
	    scn  += 4;
	    ptr  += 3;
	  }
	  break;
	case 0x04:
	  scn[0]  =  ptr[0] + scn[-q + 0];
	  scn[1]  =  ptr[1] + scn[-q + 1];
	  scn[2]  =  ptr[2] + scn[-q + 2];
	  scn[3]  =  0xFF;
	  scn  += 4;
	  ptr  += 3;
	  for(x = 4;x < q;x += 4){
	    ll =  scn[-4];
	    tt =  scn[-q + 0];
	    lt =  scn[-4 - q];
	    z  = ll + tt - lt;
	    a  =  abs(z - ll);
	    b  =  abs(z - tt);
	    c  =  abs(z - lt);
	    scn[0]  =  ptr[0];
	    scn[0] += ((a <= b) && (a <= c)) ? ll : 
	                           (b <= c)  ? tt : lt;
	    ll =  scn[-3];
	    tt =  scn[-q + 1];
	    lt =  scn[-3 - q];
	    z  = ll + tt - lt;
	    a  =  abs(z - ll);
	    b  =  abs(z - tt);
	    c  =  abs(z - lt);
	    scn[1]  =  ptr[1];
	    scn[1] += ((a <= b) && (a <= c)) ? ll : 
	                           (b <= c)  ? tt : lt;
	    ll =  scn[-2];
	    tt =  scn[-q + 2];
	    lt =  scn[-2 - q];
	    z  = ll + tt - lt;
	    a  =  abs(z - ll);
	    b  =  abs(z - tt);
	    c  =  abs(z - lt);
	    scn[2]  =  ptr[2];
	    scn[2] += ((a <= b) && (a <= c)) ? ll : 
	                           (b <= c)  ? tt : lt;
	    scn[3]  =  0xFF;
	    scn  += 4;
	    ptr  += 3;
	  }
	  break;
	}
      }
    }
  }else
  if(t == 0x04){
    switch(*ptr++){
    case 0x00:
    case 0x02:
      for(x = 0;x < q;x += 4){
	scn[0]  =  ptr[0];
	scn[1]  =  ptr[1];
	scn[2]  =  ptr[2];
	scn[3]  =  ptr[3];
	scn  += 4;
	ptr  += 4;
      }
      break;
    case 0x01:
    case 0x03:
    case 0x04:
      scn[0]  =  ptr[0];
      scn[1]  =  ptr[1];
      scn[2]  =  ptr[2];
      scn[3]  =  ptr[3];
      scn  += 4;
      ptr  += 4;
      for(x = 4;x < q;x += 4){
	scn[0]  =  ptr[0] + scn[-4];
        scn[1]  =  ptr[1] + scn[-3];
        scn[2]  =  ptr[2] + scn[-2];
        scn[3]  =  ptr[3] + scn[-1];
        scn  += 4;
        ptr  += 4;
      }
      break;
    }
    for(y = 1;y < h;y++){
      switch(*ptr++){
      case 0x00:
	for(x = 0;x < q;x += 4){
	  scn[0]  =  ptr[0];
	  scn[1]  =  ptr[1];
	  scn[2]  =  ptr[2];
	  scn[3]  =  ptr[3];
	  scn  += 4;
	  ptr  += 4;
	}
	break;
      case 0x01:
        scn[0]  =  ptr[0];
        scn[1]  =  ptr[1];
        scn[2]  =  ptr[2];
        scn[3]  =  ptr[3];
        scn  += 4;
        ptr  += 4;
	for(x = 4;x < q;x += 4){
	  scn[0]  =  ptr[0] + scn[-4];
	  scn[1]  =  ptr[1] + scn[-3];
	  scn[2]  =  ptr[2] + scn[-2];
	  scn[3]  =  ptr[3] + scn[-1];
	  scn  += 4;
	  ptr  += 4;
	}
	break;
      case 0x02:
	for(x = 0;x < q;x += 4){
	  scn[0]  =  ptr[0] + scn[-q + 0];
	  scn[1]  =  ptr[1] + scn[-q + 1];
	  scn[2]  =  ptr[2] + scn[-q + 2];
	  scn[3]  =  ptr[3] + scn[-q + 3];
	  scn  += 4;
	  ptr  += 4;
	}
	break;
      case 0x03:
        scn[0]  =  ptr[0] + scn[-q + 0] / 2;
        scn[1]  =  ptr[1] + scn[-q + 1] / 2;
        scn[2]  =  ptr[2] + scn[-q + 2] / 2;
        scn[3]  =  ptr[3] + scn[-q + 3] / 2;
        scn  += 4;
        ptr  += 4;
	for(x = 4;x < q;x += 4){
	  scn[0]  =  ptr[0] + (scn[-q + 0] + scn[-4]) / 2;
	  scn[1]  =  ptr[1] + (scn[-q + 1] + scn[-3]) / 2;
	  scn[2]  =  ptr[2] + (scn[-q + 2] + scn[-2]) / 2;
	  scn[3]  =  ptr[3] + (scn[-q + 3] + scn[-1]) / 2;
	  scn  += 4;
	  ptr  += 4;
	}
	break;
      case 0x04:
	scn[0]  =  ptr[0] + scn[-q + 0];
	scn[1]  =  ptr[1] + scn[-q + 1];
	scn[2]  =  ptr[2] + scn[-q + 2];
	scn[3]  =  ptr[3] + scn[-q + 3];
	scn  += 4;
	ptr  += 4;
	for(x = 4;x < q;x += 4){
	  ll =  scn[-4];
	  tt =  scn[-q + 0];
	  lt =  scn[-4 - q];
	  z  = ll + tt - lt;
	  a  =  abs(z - ll);
	  b  =  abs(z - tt);
	  c  =  abs(z - lt);
	  scn[0]  =  ptr[0];
	  scn[0] += ((a <= b) && (a <= c)) ? ll : 
	                         (b <= c)  ? tt : lt;
	  ll =  scn[-3];
	  tt =  scn[-q + 1];
	  lt =  scn[-3 - q];
	  z  = ll + tt - lt;
	  a  =  abs(z - ll);
	  b  =  abs(z - tt);
	  c  =  abs(z - lt);
	  scn[1]  =  ptr[1];
	  scn[1] += ((a <= b) && (a <= c)) ? ll : 
	                         (b <= c)  ? tt : lt;
	  ll =  scn[-2];
	  tt =  scn[-q + 2];
	  lt =  scn[-2 - q];
	  z  = ll + tt - lt;
	  a  =  abs(z - ll);
	  b  =  abs(z - tt);
	  c  =  abs(z - lt);
	  scn[2]  =  ptr[2];
	  scn[2] += ((a <= b) && (a <= c)) ? ll : 
	                         (b <= c)  ? tt : lt;
	  ll =  scn[-1];
	  tt =  scn[-q + 3];
	  lt =  scn[-1 - q];
	  z  = ll + tt - lt;
	  a  =  abs(z - ll);
	  b  =  abs(z - tt);
	  c  =  abs(z - lt);
	  scn[3]  =  ptr[3];
	  scn[3] += ((a <= b) && (a <= c)) ? ll : 
	                         (b <= c)  ? tt : lt;
	  scn  += 4;
	  ptr  += 4;
	}
	break;
      }
    }
  }
  free(zip);
 *width  =  (int)w;
 *height =  (int)h;
 return (IMAGE)img;
}

void  PNG__Output_File_Pointer(IMAGE img,UINT4 width,UINT4 height,FILE       *fp      ){
  // =================================================================
  // SIGNATURE
  // =================================================================
  UINT1 signat[ 8] = {0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A};

  fwrite(signat,1, 8,fp);
  // =================================================================
  // HEADER
  // =================================================================
  UINT1 header[25] = {0x00,0x00,0x00,0x0D,0x49,0x48,0x44,0x52,
		      0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
		      0x08,0x06,0x00,0x00,0x00,0xFF,0xFF,0xFF,
		      0xFF};
  UINT4 CRC;
  
  header[ 8] = (width  >> 24) & 0xFF;
  header[ 9] = (width  >> 16) & 0xFF;
  header[10] = (width  >>  8) & 0xFF;
  header[11] =  width         & 0xFF;

  header[12] = (height >> 24) & 0xFF;
  header[13] = (height >> 16) & 0xFF;
  header[14] = (height >>  8) & 0xFF;
  header[15] =  height        & 0xFF;

  CRC = PNG__Calc_CRC(&header[4],17);

  header[21] = (CRC    >> 24) & 0xFF;
  header[22] = (CRC    >> 16) & 0xFF;
  header[23] = (CRC    >>  8) & 0xFF;
  header[24] =  CRC           & 0xFF;

  fwrite(header,1,25,fp);
  // =================================================================
  // BODY
  // =================================================================
  UINT1 *buf;
  UINT1 *orig_dat;
  UINT4  orig_num;
  UINT1 *comp_dat;
  uLongf comp_num;
  UINT1 *idat_dat;
  UINT4  idat_num;
  INT4   m;

  // 1. IDATチャンクのデータサイズを計算
  orig_num = (1 + sizeof(RGBA) * width) * height;
  // 2. 圧縮後の許容最大データサイズ(シグネチャなし)を計算
  comp_num = 12 + orig_num * 1.001;
  // 3. 圧縮後の許容最大データサイズ(シグネチャ含む)を計算
  idat_num =  4 + comp_num;
  // 4. 必要メモリ領域を確保
  if((buf = (UINT1*)malloc(orig_num + idat_num)) == NULL){
    fprintf(stderr,"ERROR : PNG__Output_File_Pointer(#1)\n");
    exit(EXIT_FAILURE);
  }
  // 5. データ領域のポインタを設定
  orig_dat = &buf[           0];    
  comp_dat = &buf[orig_num + 4];
  idat_dat = &buf[orig_num + 0];
  // 6. 画像データから圧縮前IDATチャンクデータを作成
  for(m = 0;m < height;m++){
            orig_dat[(1 + sizeof(RGBA) * width) * m + 0] = 0x00;//フィルタ : None
    memcpy(&orig_dat[(1 + sizeof(RGBA) * width) * m + 1],
	   &     img[                    width  * m    ],
	                  sizeof(RGBA) * width);    
  }
  // 7. シグネチャ"IDAT"を格納
  memcpy(idat_dat,"IDAT",4);
  // 8. IDATチャンクデータを圧縮
  if(compress(comp_dat,&comp_num,orig_dat,orig_num) != Z_OK){
    free(buf);
    fprintf(stderr,"ERROR : PNG__Output_File_Pointer(#2)\n");
    exit(EXIT_FAILURE);
  }
  idat_num = 4 + comp_num;
  // 9. 圧縮データサイズを出力
  PNG__Write_4B(comp_num,fp);
  //10. IDATチャンクデータを出力
  fwrite(idat_dat,1,idat_num,fp);
  //11. IDATチャンクデータのCRCを出力
  PNG__Write_4B(PNG__Calc_CRC(idat_dat,idat_num),fp);
  //12. メモリを解放
  free(buf);

  // =================================================================
  // FOOTER
  // =================================================================
  UINT1 footer[12] = {0x00,0x00,0x00,0x00,0x49,0x45,0x4E,0x44,
		      0xAE,0x42,0x60,0x82};

  fwrite(footer,1,12,fp);
}

void  PNG__Output_BASE64      (IMAGE img,UINT4 width,UINT4 height,FILE       *fp      ){
  BASE64_ENCODER enc;

  BASE64_ENCODER__Initialize(&enc,fp);
  // =================================================================
  // SIGNATURE
  // =================================================================
  UINT1 signat[ 8] = {0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A};

  BASE64_ENCODER__ReadBytes (&enc,signat, 8);
  // =================================================================
  // HEADER
  // =================================================================
  UINT1 header[25] = {0x00,0x00,0x00,0x0D,0x49,0x48,0x44,0x52,
		      0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
		      0x08,0x06,0x00,0x00,0x00,0xFF,0xFF,0xFF,
		      0xFF};
  UINT4 CRC;
  
  header[ 8] = (width  >> 24) & 0xFF;
  header[ 9] = (width  >> 16) & 0xFF;
  header[10] = (width  >>  8) & 0xFF;
  header[11] =  width         & 0xFF;

  header[12] = (height >> 24) & 0xFF;
  header[13] = (height >> 16) & 0xFF;
  header[14] = (height >>  8) & 0xFF;
  header[15] =  height        & 0xFF;

  CRC = PNG__Calc_CRC(&header[4],17);

  header[21] = (CRC    >> 24) & 0xFF;
  header[22] = (CRC    >> 16) & 0xFF;
  header[23] = (CRC    >>  8) & 0xFF;
  header[24] =  CRC           & 0xFF;

  BASE64_ENCODER__ReadBytes (&enc,header,25);
  // =================================================================
  // BODY
  // =================================================================
  UINT1 *buf;
  UINT1 *orig_dat;
  UINT4  orig_num;
  UINT1 *comp_dat;
  uLongf comp_num;
  UINT1 *idat_dat;
  UINT4  idat_num;
  INT4   m;

  // 1. IDATチャンクのデータサイズを計算
  orig_num = (1 + sizeof(RGBA) * width) * height;
  // 2. 圧縮後の許容最大データサイズ(シグネチャなし)を計算
  comp_num = 12 + orig_num * 1.001;
  // 3. 圧縮後の許容最大データサイズ(シグネチャ含む)を計算
  idat_num =  4 + comp_num;
  // 4. 必要メモリ領域を確保
  if((buf = (UINT1*)malloc(orig_num + idat_num)) == NULL){
    fprintf(stderr,"ERROR : PNG__Output_BASE64(#1)\n");
    exit(EXIT_FAILURE);
  }
  // 5. データ領域のポインタを設定
  orig_dat = &buf[           0];    
  comp_dat = &buf[orig_num + 4];
  idat_dat = &buf[orig_num + 0];
  // 6. 画像データから圧縮前IDATチャンクデータを作成
  for(m = 0;m < height;m++){
            orig_dat[(1 + sizeof(RGBA) * width) * m + 0] = 0x00;//フィルタ : None
    memcpy(&orig_dat[(1 + sizeof(RGBA) * width) * m + 1],
	   &     img[                    width  * m    ],
	                  sizeof(RGBA) * width);    
  }
  // 7. シグネチャ"IDAT"を格納
  memcpy(idat_dat,"IDAT",4);
  // 8. IDATチャンクデータを圧縮
  if(compress(comp_dat,&comp_num,orig_dat,orig_num) != Z_OK){
    free(buf);
    fprintf(stderr,"ERROR : PNG__Output_BASE64(#2)\n");
    exit(EXIT_FAILURE);
  }
  idat_num = 4 + comp_num;
  // 9. 圧縮データサイズを出力
  PNG__Write_4B_BASE64(comp_num,&enc);
  //10. IDATチャンクデータを出力
  BASE64_ENCODER__ReadBytes (&enc,idat_dat,idat_num);
  //11. IDATチャンクデータのCRCを出力
  PNG__Write_4B_BASE64(PNG__Calc_CRC(idat_dat,idat_num),&enc);
  //12. メモリを解放
  free(buf);

  // =================================================================
  // FOOTER
  // =================================================================
  UINT1 footer[12] = {0x00,0x00,0x00,0x00,0x49,0x45,0x4E,0x44,
		      0xAE,0x42,0x60,0x82};

  BASE64_ENCODER__ReadBytes (&enc,footer,12);
  BASE64_ENCODER__Finalize  (&enc);
}

void  PNG__Output_File        (IMAGE img,UINT4 width,UINT4 height,const char *filename){
  FILE *fp;

  if((fp = fopen(filename,"wb")) == NULL){
    fprintf(stderr,"ERROR : PNG__Output_File(#1)\n");
    exit(EXIT_FAILURE);
  }
  PNG__Output_File_Pointer(img,width,height,fp);
  fclose(fp);
}
