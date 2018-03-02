/*****************************************************************
 * 
 * CL31
 *
 *                           Created  by Mamoru Ota (2018/02/27)
 *
 *****************************************************************/ 

#include"CL31.h"

int   CL31__INITIALIZE (CL31 *cl31,const char *filename){
  FILE *fp;
  CHAR *ptr;
  CHAR  str[3];
  int   YYYY,MM,DD;
  
  ptr = strrchr(filename,'/');
  if(ptr == NULL){
     ptr = (CHAR*)filename;
  }else{
     ptr++;
  }
  if((ptr[0] != 'c') || (ptr[1] != 'l') || (ptr[8] != '.') || (ptr[9] != 't') || (ptr[10] != 'x') || (ptr[11] != 't')){
    return -1;
  }
  str[0] = ptr[2];
  str[1] = ptr[3];
  str[2] = '\0';
  YYYY   = atoi(str) + 2000;
  if((YYYY < 2000) || (2100 < YYYY)){
    return -1;
  }
  str[0] = ptr[4];
  str[1] = ptr[5];
  str[2] = '\0';
  MM     = atoi(str);
  if((MM   <    1) || (  12 <   MM)){
    return -1;
  }
  str[0] = ptr[6];
  str[1] = ptr[7];
  str[2] = '\0';
  DD     = atoi(str);
  if((DD   <    1) || (  31 <   DD)){
    return -1;
  }
  
  if((fp = fopen(filename,"rb")) == NULL){
    return -1;
  }
  cl31->YYYY = YYYY;
  cl31->MM   = MM;
  cl31->DD   = DD;
  cl31->fp   = fp;
  return 0;
}

void  CL31__FINALIZE   (CL31 *cl31){
  fclose(cl31->fp);
}

int   CL31__READ       (CL31 *cl31){
  long pos;

 INIT:
  pos = ftell(cl31->fp);
  if(fread(cl31->line1,1,CL31__LINE1_LEN,cl31->fp) < CL31__LINE1_LEN){
    return -1;
  }
  if((cl31->line1[14] != 'C') || (cl31->line1[15] != 'L')){
    goto INVALID;
  }
  switch(cl31->line1[20]){
  case '1':
    if(fread(cl31->buf,1,CL31__LINES_LEN_MSG1,cl31->fp) < CL31__LINES_LEN_MSG1){
      return -1;
    }
    cl31->line2 = cl31->buf;
    cl31->line3 = NULL;
    cl31->line4 = cl31->line2 + CL31__LINE2_LEN;
    cl31->line5 = cl31->line4 + CL31__LINE4_LEN;
    cl31->line6 = cl31->line5 + CL31__LINE5_LEN;
    cl31->line7 = cl31->line6 + CL31__LINE6_LEN;
    break;
  case '2':
    if(fread(cl31->buf,1,CL31__LINES_LEN_MSG2,cl31->fp) < CL31__LINES_LEN_MSG2){
      return -1;
    }
    cl31->line2 = cl31->buf;
    cl31->line3 = cl31->line2 + CL31__LINE2_LEN;
    cl31->line4 = cl31->line3 + CL31__LINE3_LEN;
    cl31->line5 = cl31->line4 + CL31__LINE4_LEN;
    cl31->line6 = cl31->line5 + CL31__LINE5_LEN;
    cl31->line7 = cl31->line6 + CL31__LINE6_LEN;
    break;
  default:
    goto INVALID;
  }
  if(CL31__CHECK_HEAD (cl31) != 0){
    goto INVALID;
  }
  if(CL31__CHECK_LINE1(cl31) != 0){
    goto INVALID;
  }
  if(CL31__CHECK_LINE2(cl31) != 0){
    goto INVALID;
  }
  if(CL31__CHECK_LINE3(cl31) != 0){
    goto INVALID;
  }
  if(CL31__CHECK_LINE4(cl31) != 0){
    goto INVALID;
  }
  if(CL31__CHECK_LINE5(cl31) != 0){
    goto INVALID;
  }
  if(CL31__CHECK_LINE6(cl31) != 0){
    goto INVALID;
  }
  if(CL31__CHECK_LINE7(cl31) != 0){
    goto INVALID;
  }
  CL31__SHOWINFO(cl31);
  return 0;
 INVALID:
  fprintf(stderr,"[INVALID] %.20s\n",cl31->line1);
  fseek(cl31->fp,pos + 1L,SEEK_SET);
  goto INIT;  
}

void  CL31__SHOWINFO   (CL31 *cl31){
  fprintf(stderr,"[OK] %04d-%02d-%02d %02d:%02d:%02d %c %d %d %d\n",
          cl31->YYYY,
          cl31->MM,
          cl31->DD,
          cl31->hh,cl31->mm,cl31->ss,
          cl31->unit_id,
          cl31->software_level_id,
          cl31->msg_number,
          cl31->subclass);

  fprintf(stderr,"detection_status %d %c %d %d %d\n",
          cl31->detection_status,
          cl31->WA_info,
          cl31->val1,
          cl31->val2,
          cl31->val3);  
  // ************************************************************
  // Alarm 
  // ************************************************************
  if(cl31->AWS[ 0] & 0x8)fprintf(stderr,"[A status] Transmitter shut-off\n");
  if(cl31->AWS[ 0] & 0x4)fprintf(stderr,"[A status] Transmitter failure\n");
  if(cl31->AWS[ 0] & 0x2)fprintf(stderr,"[A status] Receiver failure\n");
  if(cl31->AWS[ 0] & 0x1)fprintf(stderr,"[A status] Voltage failure\n");
  if(cl31->AWS[ 1] & 0x8)fprintf(stderr,"[A status] Alignment failure\n");
  if(cl31->AWS[ 1] & 0x4)fprintf(stderr,"[A status] Memory error\n");
  if(cl31->AWS[ 1] & 0x2)fprintf(stderr,"[A status] Light path obstruction\n");
  if(cl31->AWS[ 1] & 0x1)fprintf(stderr,"[A status] Receiver saturation\n");
  if(cl31->AWS[ 2] & 0x8)fprintf(stderr,"[A status] spare\n");
  if(cl31->AWS[ 2] & 0x4)fprintf(stderr,"[A status] spare\n");
  if(cl31->AWS[ 2] & 0x2)fprintf(stderr,"[A status] spare\n");
  if(cl31->AWS[ 2] & 0x1)fprintf(stderr,"[A status] spare\n");
  if(cl31->AWS[ 3] & 0x8)fprintf(stderr,"[A status] spare\n");
  if(cl31->AWS[ 3] & 0x4)fprintf(stderr,"[A status] spare\n");
  if(cl31->AWS[ 3] & 0x2)fprintf(stderr,"[A status] Coaxial cable failure\n");
  if(cl31->AWS[ 3] & 0x1)fprintf(stderr,"[A status] Ceilometer engine board failure\n");
  // ************************************************************
  // Warning
  // ************************************************************
  if(cl31->AWS[ 4] & 0x8)fprintf(stderr,"[W status] Window contamination\n");
  if(cl31->AWS[ 4] & 0x4)fprintf(stderr,"[W status] Battery voltage low\n");
  if(cl31->AWS[ 4] & 0x2)fprintf(stderr,"[W status] Transmitter expires\n");
  if(cl31->AWS[ 4] & 0x1)fprintf(stderr,"[W status] High humidity\n");
  if(cl31->AWS[ 5] & 0x8)fprintf(stderr,"[W status] spare\n");
  if(cl31->AWS[ 5] & 0x4)fprintf(stderr,"[W status] Blower failure\n");
  if(cl31->AWS[ 5] & 0x2)fprintf(stderr,"[W status] spare\n");
  if(cl31->AWS[ 5] & 0x1)fprintf(stderr,"[W status] Humidity sensor failure\n");
  if(cl31->AWS[ 6] & 0x8)fprintf(stderr,"[W status] Heater fault\n");
  if(cl31->AWS[ 6] & 0x4)fprintf(stderr,"[W status] High background radiance\n");
  if(cl31->AWS[ 6] & 0x2)fprintf(stderr,"[W status] Ceilometer engine board failure\n");
  if(cl31->AWS[ 6] & 0x1)fprintf(stderr,"[W status] Battery failure\n");
  if(cl31->AWS[ 7] & 0x8)fprintf(stderr,"[W status] Laser monitor failure\n");
  if(cl31->AWS[ 7] & 0x4)fprintf(stderr,"[W status] Receiver warning\n");
  if(cl31->AWS[ 7] & 0x2)fprintf(stderr,"[W status] Tilt angle > 45 degrees warning\n");
  if(cl31->AWS[ 7] & 0x1)fprintf(stderr,"[W status] spare\n");
  // ************************************************************
  // Internal
  // ************************************************************
  if(cl31->AWS[ 8] & 0x8)fprintf(stderr,"[S status] Blower is on\n");
  if(cl31->AWS[ 8] & 0x4)fprintf(stderr,"[S status] Blower heater is on\n");
  if(cl31->AWS[ 8] & 0x2)fprintf(stderr,"[S status] Internal heater is on\n");
  if(cl31->AWS[ 8] & 0x1)fprintf(stderr,"[S status] Working from battery\n");
  if(cl31->AWS[ 9] & 0x8)fprintf(stderr,"[S status] Standby mode is on\n");
  if(cl31->AWS[ 9] & 0x4)fprintf(stderr,"[S status] Self test in progress\n");
  if(cl31->AWS[ 9] & 0x2)fprintf(stderr,"[S status] Manual data acquisition settings are effective\n");
  if(cl31->AWS[ 9] & 0x1)fprintf(stderr,"[S status] spare\n");
  if(cl31->AWS[10] & 0x8)fprintf(stderr,"[S status] Units are meters if on, else feet\n");
  if(cl31->AWS[10] & 0x4)fprintf(stderr,"[S status] Manual blower control\n");
  if(cl31->AWS[10] & 0x2)fprintf(stderr,"[S status] Polling mode is on\n");
  if(cl31->AWS[10] & 0x1)fprintf(stderr,"[S status] spare\n");
  if(cl31->AWS[11] & 0x8)fprintf(stderr,"[S status] Units are meters if on, else feet\n");
  if(cl31->AWS[11] & 0x4)fprintf(stderr,"[S status] Manual blower control\n");
  if(cl31->AWS[11] & 0x2)fprintf(stderr,"[S status] Polling mode is on\n");
  if(cl31->AWS[11] & 0x1)fprintf(stderr,"[S status] spare\n");

  //fprintf(stderr,"%02d:%02d:%02d %4d %4d %4d\n",ti / 3600,ti % 3600,ti % 60,height[0],height[1],height[2]);
}

void  CL31__GET_DATA   (CL31 *cl31,CDF_L1_CL31__DATA *dat){
  int n;

  dat->epoch = CDF_TT2000_from_UTC_parts((double)cl31->YYYY,
                                         (double)cl31->MM,
                                         (double)cl31->DD,
                                         (double)cl31->hh,
                                         (double)cl31->mm,
                                         (double)cl31->ss,
                                         0.0,0.0,0.0);
  for(n = 0;n < cl31->sample_length;n++){
    dat->H[n] = n * cl31->dH;
  }

  //1st line
  dat->unit_identification_char     = cl31->unit_id;
  dat->software_level               = cl31->software_level_id;
  dat->message_number               = cl31->msg_number;
  dat->subclasses_message_char      = cl31->subclass;

  //2nd line
  dat->cloud_base_status            = cl31->detection_status;
  dat->warning_alarm_info           = cl31->WA_info;
  dat->cloud_base_height[0]         = cl31->val1;
  dat->cloud_base_height[1]         = cl31->val2;
  dat->cloud_base_height[2]         = cl31->val3;
  memcpy(dat->AWS,cl31->AWS,12);

  //3rd line (of message no.2)
  for(n = 0;n < 5;n++){
    dat->cloud_amount_status[n] = cl31->cloud_amount_status[n];
    dat->cloud_layer_height [n] = cl31->cloud_layer_height [n];
  }
  
  //4th line (of message no.2)
  dat->Parameter_SCALE              = cl31->Parameter_SCALE;
  dat->dH                           = cl31->dH;
  dat->sample_length                = cl31->sample_length;
  dat->laser_pulse_energy           = cl31->laser_pulse_energy;
  dat->laser_temp                   = cl31->laser_temp;
  dat->window_transmission_estimate = cl31->window_transmission_estimate;
  dat->tilt_angle                   = cl31->tilt_angle;
  dat->background_light             = cl31->background_light;
  memcpy(dat->measurement_params,cl31->measurement_params,9);
  dat->back_scat_sum                = cl31->back_scat_sum;
  
  //5th line (of message no.2)
  for(n = 0;n < cl31->sample_length;n++){
    dat->back_scat[n] = cl31->back_scat[n];
  }
}


int   CL31__CHECK_HEAD (CL31 *cl31){
  CHAR str[6];
  int  hh,mm,ss,ti;

  if(memcmp(cl31->line1,cl31->line2,14) != 0){
    return -1;
  }
  if(cl31->line3 != NULL){
    if(memcmp(cl31->line1,cl31->line3,14) != 0){
      return -1;
    }
  }
  if(memcmp(cl31->line1,cl31->line4,14) != 0){
    return -1;
  }
  if(memcmp(cl31->line1,cl31->line5,14) != 0){
    return -1;
  }
  if(memcmp(cl31->line1,cl31->line6,14) != 0){
    return -1;
  }
  // ************************************************************
  // hh
  // ************************************************************
  str[0] = cl31->line1[ 0];
  str[1] = cl31->line1[ 1];
  str[2] = '\0';
  hh     = atoi(str);
  if((hh < 0) || (23 < hh)){
    return -1;
  }
  // ************************************************************
  //   '.'  character 
  // ************************************************************
  if(cl31->line1[ 2] != '.'){
    return -1;
  }
  // ************************************************************
  // mm
  // ************************************************************
  str[0] = cl31->line1[ 3];
  str[1] = cl31->line1[ 4];
  str[2] = '\0';
  mm     = atoi(str);
  if((mm < 0) || (59 < mm)){
    return -1;
  }
  // ************************************************************
  // ss
  // ************************************************************
  str[0] = cl31->line1[ 5];
  str[1] = cl31->line1[ 6];
  str[2] = '\0';
  ss     = atoi(str);
  if((ss < 0) || (59 < ss)){
    return -1;
  }
  // ************************************************************
  // Space character (1)
  // ************************************************************
  if(cl31->line1[ 7] != ' '){
    return -1;
  }
  // ************************************************************
  // ti
  // ************************************************************
  str[0] = cl31->line1[ 8];
  str[1] = cl31->line1[ 9];
  str[2] = cl31->line1[10];
  str[3] = cl31->line1[11];
  str[4] = cl31->line1[12];
  str[5] = '\0';
  ti     = atoi(str);
  if(ti != (3600 * hh + 60 * mm + ss)){
    return -1;
  }
  // ************************************************************
  // Space character (2)
  // ************************************************************
  if(cl31->line1[13] != ' '){
    return -1;
  }

  cl31->hh = hh;
  cl31->mm = mm;
  cl31->ss = ss;  
  
  return 0;
}

int   CL31__CHECK_LINE1(CL31 *cl31){
  CHAR  str[6];
  CHAR *ptr;
  CHAR  unit_id;
  int   software_level_id;
  int   msg_number;
  int   subclass;

  ptr = &cl31->line1[14];
  // ************************************************************
  // Ceilometers' identification string
  // ************************************************************
  if((ptr[0] != 'C') || (ptr[1] != 'L')){
    return -1;
  }
  // ************************************************************
  // Unit identification character
  // ************************************************************
  if(!((('0' <= ptr[2]) && (ptr[2] <= '9')) || (('A' <= ptr[2]) && (ptr[2] <= 'Z')))){
    return -1;
  }
  unit_id = ptr[2];
  // ************************************************************
  // Software level ID
  // ************************************************************
  str[0] = ptr[3];
  str[1] = ptr[4];
  str[2] = ptr[5];
  str[3] = '\0';
  software_level_id = atoi(str);
  if((software_level_id < 100) || (999 < software_level_id)){
    return -1;
  }
  // ************************************************************
  // Message number
  // ************************************************************
  if((ptr[6] !=  '1') && (ptr[6] != '2')){
    return -1;
  }
  msg_number = ptr[6] - '0';
  // ************************************************************
  // Subclasses of message
  // ************************************************************
  if((ptr[7]  <  '1') || ('5'  < ptr[7])){
    return -1;
  }
  subclass   = ptr[7] - '0';
  // ************************************************************
  // Termination character
  // ************************************************************
  if( ptr[8] != '\n'){
    return -1;
  }  

  cl31->unit_id           = unit_id;
  cl31->software_level_id = software_level_id;
  cl31->msg_number        = msg_number;
  cl31->subclass          = subclass;
  
  return 0;
}

int   CL31__CHECK_LINE2(CL31 *cl31){
  CHAR   str[6];
  CHAR  *ptr;
  int    detection_status;
  CHAR   WA_info;
  int    val1,val2,val3;
  UCHAR  AWS[12];
  int    n;
  
  ptr = &cl31->line2[14];
  // ************************************************************
  // First  digit of line
  // ************************************************************
  if(!((('0' <= ptr[0]) && (ptr[0] <= '5')) || (ptr[0] == '/'))){
    return -1;
  }  
  detection_status = (ptr[0] != '/') ? (ptr[0] - '0') : -1;
  // ************************************************************
  // Second digit of line
  // ************************************************************
  if((ptr[1] != '0') && (ptr[1] != 'W') && (ptr[1] != 'A')){
    return -1;
  }
  WA_info = ptr[1];
  // ************************************************************
  // Space character (1)
  // ************************************************************
  if(ptr[ 2] != ' '){
    return -1;
  }  
  // ************************************************************
  // Lowest cloud base height / Vertical Visibility as calculated
  // ************************************************************
  str[0] = ptr[ 3];
  str[1] = ptr[ 4];
  str[2] = ptr[ 5];
  str[3] = ptr[ 6];
  str[4] = ptr[ 7];
  str[5] = '\0';
  if(strcmp(str,"/////") == 0){
    if((detection_status != 0) && (detection_status != 5)){
      return -1;
    }
    val1 = -1;
  }else{
    val1 = atoi(str);
    if(val1 < 0){
      return -1;
    }
  }
  // ************************************************************
  // Space character (2) 
  // ************************************************************
  if(ptr[ 8] != ' '){
    return -1;
  }  
  // ************************************************************
  // Second lowest cloud base height / Highest signal detected
  // ************************************************************
  str[0] = ptr[ 9];
  str[1] = ptr[10];
  str[2] = ptr[11];
  str[3] = ptr[12];
  str[4] = ptr[13];
  str[5] = '\0';
  if(strcmp(str,"/////") == 0){
    if((detection_status != 0) && (detection_status != 1) && (detection_status != 5)){
      return -1;
    }
    val2 = -1;
  }else{
    val2 = atoi(str);
    if(val2 < 0){
      return -1;
    }
  }
  // ************************************************************
  // Space character (3) 
  // ************************************************************
  if(ptr[14] != ' '){
    return -1;
  }  
  // ************************************************************
  // Highest cloud base height
  // ************************************************************
  str[0] = ptr[15];
  str[1] = ptr[16];
  str[2] = ptr[17];
  str[3] = ptr[18];
  str[4] = ptr[19];
  str[5] = '\0';
  if(strcmp(str,"/////") == 0){
    if(detection_status == 3){
      return -1;
    }
    val3 = -1;
  }else{
    val3 = atoi(str);
    if(val3 < 0){
      return -1;
    }
  }
  // ************************************************************
  // Space character (4) 
  // ************************************************************
  if(ptr[20] != ' '){
    return -1;
  }  
  // ************************************************************
  // Alarm, warning, and internal status information
  // ************************************************************
  for(n = 0;n < 12;n++){
    switch(ptr[21 + n]){
    case '0':AWS[n] = 0x0;break;
    case '1':AWS[n] = 0x1;break;
    case '2':AWS[n] = 0x2;break;
    case '3':AWS[n] = 0x3;break;
    case '4':AWS[n] = 0x4;break;
    case '5':AWS[n] = 0x5;break;
    case '6':AWS[n] = 0x6;break;
    case '7':AWS[n] = 0x7;break;
    case '8':AWS[n] = 0x8;break;
    case '9':AWS[n] = 0x9;break;
    case 'A':AWS[n] = 0xA;break;
    case 'B':AWS[n] = 0xB;break;
    case 'C':AWS[n] = 0xC;break;
    case 'D':AWS[n] = 0xD;break;
    case 'E':AWS[n] = 0xE;break;
    case 'F':AWS[n] = 0xF;break;
    default:return -1;
    }
  }
  // ************************************************************
  // Termination character
  // ************************************************************
  if(ptr[33] != '\n'){
    return -1;
  }

  cl31->detection_status = detection_status;
  cl31->WA_info          = WA_info;
  cl31->val1             = val1;
  cl31->val2             = val2;
  cl31->val3             = val3;
  memcpy(cl31->AWS,AWS,12);

  return 0;
}

int   CL31__CHECK_LINE3(CL31 *cl31){
  char  str[6];
  char *ptr;
  int   detection_status;
  int   height[5];
  int   amount[5];
  int   n,m;

  if(cl31->line3 == NULL){
    return 0;
  }
  
  ptr = &cl31->line3[14];
  // ************************************************************
  // First  digit of line
  // ************************************************************
  str[0] = ptr[0];
  str[1] = ptr[1];
  str[2] = ptr[2];
  str[3] = '\0';
  detection_status = atoi(str);
  if(!(((-1 <= detection_status) && (detection_status <= 9)) || (detection_status == 99))){
    return -1;
  }
  // ************************************************************
  // Space character (1)
  // ************************************************************
  if(ptr[3] != ' '){
    return -1;
  }
  // ************************************************************
  // Second digit of line
  // ************************************************************
  str[0] = ptr[4];
  str[1] = ptr[5];
  str[2] = ptr[6];
  str[3] = '\0';
  if(strcmp(str,"///") == 0){
    height[0] = -1;
  }else{
    height[0] = atoi(str);
    if(height[0] < 0){
      return -1;
    }
  }
  // ************************************************************
  // Space character (2)
  // ************************************************************
  if((ptr[7] != ' ') || (ptr[8] != ' ')){
    return -1;
  }
  for(n = 1;n < 5;n++){
    m = 9 + 7 * (n - 1);
    // ************************************************************
    // Third digit of line
    // ************************************************************
    amount[n] = ptr[m] - '0';
    if((amount[n] < 0) || (9 < amount[n])){
      return -1;
    }
    // ************************************************************
    // Space character (3)
    // ************************************************************
    if(ptr[m + 1] != ' '){
      return -1;
    }
    // ************************************************************
    // The fourth number of line
    // ************************************************************
    str[0] = ptr[m + 2]; str[1] = ptr[m + 3]; str[2] = ptr[m + 4]; str[3] = '\0';
    if(strcmp(str,"///") == 0){
      height[n] = -1;
    }else{
      height[n] = atoi(str);
      if(height[n] < height[n]){
        return -1;
      }
    }
  }
  // ************************************************************
  // Termination character
  // ************************************************************
  if(ptr[35] != '\n'){
    return -1;
  }

  for(n = 0;n < 5;n++){
    cl31->cloud_amount_status[n] = amount[n];
    cl31->cloud_layer_height [n] = height[n];
  }
  
  return 0;
}

int   CL31__CHECK_LINE4(CL31 *cl31){
  CHAR  str[6];
  CHAR *ptr;
  int   scale;
  int   dH;
  int   len;
  int   lpe;
  int   ltd;
  int   wte;
  int   angle;
  int   bg;
  CHAR  params[9];
  int   sum;
  
  ptr = &cl31->line4[14];
  // ************************************************************
  // Parameter SCALE
  // ************************************************************
  str[0] = ptr[0];
  str[1] = ptr[1];
  str[2] = ptr[2];
  str[3] = ptr[3];
  str[4] = ptr[4];
  str[5] = '\0';
  scale  = atoi(str);
  if((scale < 0) || (99999 < scale)){
    return -1;
  }
  ptr += 5;
  // ************************************************************
  // Space character (1)
  // ************************************************************
  if(ptr[0] != ' '){
    return -1;
  }
  ptr += 1;
  // ************************************************************
  // Backscatter profile resolution in meters
  // ************************************************************
  str[0] = ptr[0];
  str[1] = ptr[1];
  str[2] = '\0';
  dH     = atoi(str);
  if((dH  < 0) || (99 < dH)){
    return -1;
  }
  ptr += 2;
  // ************************************************************
  // Space character (2)
  // ************************************************************
  if(ptr[0] != ' '){
    return -1;
  }
  ptr += 1;
  // ************************************************************
  // Length of the profile in samples 385, 770, 1400, or 1500
  // ************************************************************
  str[0] = ptr[0];
  str[1] = ptr[1];
  str[2] = ptr[2];
  str[3] = ptr[3];
  str[4] = '\0';
  len    = atoi(str);
  if((len != 385) && (len != 770) && (len !=1400) && (len != 1500)){
    return -1;
  }
  ptr += 4;
  // ************************************************************
  // Space character (3)
  // ************************************************************
  if(ptr[0] != ' '){
    return -1;
  }
  ptr += 1;
  // ************************************************************
  // Laser pulse energy, % of nominal factory setting
  // ************************************************************
  str[0] = ptr[0];
  str[1] = ptr[1];
  str[2] = ptr[2];
  str[3] = '\0';
  lpe    = atoi(str);
  if((lpe < 0) || (999 < lpe)){
    return -1;
  }
  ptr += 3;
  // ************************************************************
  // Space character (4)
  // ************************************************************
  if(ptr[0] != ' '){
    return -1;
  }
  ptr += 1;
  // ************************************************************
  // Laser temperature degrees C (-50 ... +99)
  // ************************************************************
  str[0] = ptr[0];
  str[1] = ptr[1];
  str[2] = ptr[2];
  str[3] = '\0';
  ltd    = atoi(str);
  if((ltd < -50) || (+99 < ltd)){
    return -1;
  }
  ptr += 3;  
  // ************************************************************
  // Space character (5)
  // ************************************************************
  if(ptr[0] != ' '){
    return -1;
  }
  ptr += 1;
  // ************************************************************
  // Window transmission estimate % (0 ... 100)
  // ************************************************************
  str[0] = ptr[0];
  str[1] = ptr[1];
  str[2] = ptr[2];
  str[3] = '\0';
  wte    = atoi(str);
  if((wte < 0) || (100 < wte)){
    return -1;
  }
  ptr += 3;
  // ************************************************************
  // Space character (6)
  // ************************************************************
  if(ptr[0] != ' '){
    return -1;
  }
  ptr += 1;
  // ************************************************************
  // Tilt angle, degrees from vertical (0 ... 90)
  // ************************************************************
  str[0] = ptr[0];
  str[1] = ptr[1];
  str[2] = '\0';
  angle  = atoi(str);
  if((angle < 0) || (90 < angle)){
    return -1;
  }
  ptr += 2;
  // ************************************************************
  // Space character (8)
  // ************************************************************
  if(ptr[0] != ' '){
    return -1;
  }
  ptr += 1;
  // ************************************************************
  // Background light, millivolts at internal ADC input
  // ************************************************************
  str[0] = ptr[0];
  str[1] = ptr[1];
  str[2] = ptr[2];
  str[3] = ptr[3];
  str[4] = '\0';
  bg     = atoi(str);
  if((bg < 0) || (2500 < bg)){
    return -1;
  }
  ptr += 4;
  // ************************************************************
  // Space character (9)
  // ************************************************************
  if(ptr[0] != ' '){
    return -1;
  }
  ptr += 1;
  // ************************************************************
  // Measurement parameters
  // ************************************************************
  memcpy(params,ptr,9);
  ptr += 9;
  // ************************************************************
  // Space character
  // ************************************************************
  if(ptr[0] != ' '){
    return -1;
  }
  ptr += 1;
  // ************************************************************
  // SUM of detected and normalized backscatter (0 ... 999)
  // ************************************************************
  str[0] = ptr[0];
  str[1] = ptr[1];
  str[2] = ptr[2];
  str[3] = '\0';
  sum    = atoi(str);
  if((sum < 0) || (999 < sum)){
    return -1;
  }
  ptr += 3;
  // ************************************************************
  // Termination character
  // ************************************************************
  if(ptr[0] != '\n'){
    return -1;
  }

  cl31->Parameter_SCALE              = scale;
  cl31->dH                           = dH;
  cl31->sample_length                = len;
  cl31->laser_pulse_energy           = lpe;
  cl31->laser_temp                   = ltd;
  cl31->window_transmission_estimate = wte;
  cl31->tilt_angle                   = angle;
  cl31->background_light             = bg; 
  memcpy(cl31->measurement_params,params,9);
  cl31->back_scat_sum                = sum;
  
  return 0;
}

int   CL31__CHECK_LINE5(CL31 *cl31){
  CHAR  str[8];
  CHAR *ptr;
  int   n;
  UINT4 dat;
  INT4  val;
  
  ptr = &cl31->line5[14];
  // ************************************************************
  // Backscatter coefficient
  // ************************************************************
  for(n = 0;n < cl31->sample_length;n++){
    if(!((('0' <= ptr[0]) && (ptr[0] <= '9')) || (('a' <= ptr[0]) && (ptr[0] <= 'f'))) ||
       !((('0' <= ptr[1]) && (ptr[1] <= '9')) || (('a' <= ptr[1]) && (ptr[1] <= 'f'))) ||
       !((('0' <= ptr[2]) && (ptr[2] <= '9')) || (('a' <= ptr[2]) && (ptr[2] <= 'f'))) ||
       !((('0' <= ptr[3]) && (ptr[3] <= '9')) || (('a' <= ptr[3]) && (ptr[3] <= 'f'))) ||
       !((('0' <= ptr[4]) && (ptr[4] <= '9')) || (('a' <= ptr[4]) && (ptr[4] <= 'f'))) ){
      return -1;
    }
    str[0] = '0';
    str[1] = 'x';
    str[2] = ptr[0];
    str[3] = ptr[1];
    str[4] = ptr[2];
    str[5] = ptr[3];
    str[6] = ptr[4];
    str[7] = '\0';
    dat    = strtoul(str,NULL,16);
    if(dat < 0x0007FFFF){
      val = dat;
    }else{
      val = dat - 0x00100000;
    }
    cl31->back_scat[n] = (val * (cl31->Parameter_SCALE / 100.0)) / 100000.0;
    ptr += 5;
  }
  // ************************************************************
  // Termination character
  // ************************************************************
  if(ptr[0] != '\n'){
    return -1;
  }
  return 0;
}

int   CL31__CHECK_LINE6(CL31 *cl31){
  CHAR  str[7];
  CHAR *ptr;  
  UINT2 crc;

  // ************************************************************
  // CRC check
  // ************************************************************
  ptr = &cl31->line6[14];
  str[0] = '0';
  str[1] = 'x';
  str[2] = ptr[0];
  str[3] = ptr[1];
  str[4] = ptr[2];
  str[5] = ptr[3];
  str[6] = '\0';
  crc    = strtoul(str,NULL,16);
  if(crc != CL31__CHECK_CRC16(cl31)){
    return -1;
  }
  // ************************************************************
  // Termination character
  // ************************************************************
  if(ptr[4] != '\n'){
    return -1;
  } 
  return 0;
}

int   CL31__CHECK_LINE7(CL31 *cl31){
  if(cl31->line7[0] != '\n'){
    return -1;
  }
  return 0;
}

UINT2 CL31__CHECK_CRC16(CL31 *cl31){
  UINT2  crc;
  UINT2  mask;
  UINT1 *ptr;
  int    m;

  ptr    = cl31->tmp;
  memcpy(ptr,&cl31->line1[14],CL31__LINE1_LEN - 14 - 1);
  ptr   += CL31__LINE1_LEN - 14 - 1;
  ptr[0] = 0x02;
  ptr++;
  ptr[0] = '\r';
  ptr++;
  ptr[0] = '\n';
  ptr++;
  memcpy(ptr,&cl31->line2[14],CL31__LINE2_LEN - 14 - 1);
  ptr   += CL31__LINE2_LEN - 14 - 1;
  ptr[0] = '\r';
  ptr++;
  ptr[0] = '\n';
  ptr++;
  if(cl31->line3 != NULL){
    memcpy(ptr,&cl31->line3[14],CL31__LINE3_LEN - 14 - 1);
    ptr   += CL31__LINE3_LEN - 14 - 1;
    ptr[0] = '\r';
    ptr++;
    ptr[0] = '\n';
    ptr++;
  }
  memcpy(ptr,&cl31->line4[14],CL31__LINE4_LEN - 14 - 1);
  ptr   += CL31__LINE4_LEN - 14 - 1;
  ptr[0] = '\r';
  ptr++;
  ptr[0] = '\n';
  ptr++;
  memcpy(ptr,&cl31->line5[14],CL31__LINE5_LEN - 14 - 1);
  ptr   += CL31__LINE5_LEN - 14 - 1;
  ptr[0] = '\r';
  ptr++;
  ptr[0] = '\n';
  ptr++;
  ptr[0] = 0x03;
  ptr++;
  ptr[0] = '\0';
  ptr++;
  
  crc = 0xFFFF;
  for(ptr = cl31->tmp;*ptr != '\0';ptr++){
    crc ^= *ptr << 8;
    for(m = 0;m < 8;m++){
      mask  = (crc & 0x8000) ? 0x1021 : 0x0000;
      crc <<= 1;
      crc  ^= mask;      
    }
  }
  return crc ^ 0xFFFF;
}
