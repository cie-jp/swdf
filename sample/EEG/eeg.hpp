RMatrix EEG__READ_X(){
  RMatrix dat;
  RVector ch[8];
  RMatrix X(45 * 3,4 * 3 * 8);
  INT4    n,k,l,t;
  REAL    ave;
  REAL    re[250];
  REAL    im[250];
  REAL    sum_all,sum_1,sum_2,sum_3;

  dat   = RMatrix__fetch_csv("./EEG_DATA.txt"," ","");
  ch[0] = (dat |  4);
  ch[1] = (dat |  5);
  ch[2] = (dat |  6);
  ch[3] = (dat |  7);
  ch[4] = (dat |  8);
  ch[5] = (dat |  9);
  ch[6] = (dat | 10);
  ch[7] = (dat | 11);

  for(n = 0;n < 45 * 3;n++){
    for(k = 0;k < 8;k++){
      for(t = 0;t < 4;t++){
	ave  = 0.0;
	for(l = 0;l < 250;l++){
	  re[l]  = ch[k][n * 250 * 4 + t * 250 + l];
	  im[l]  = 0.0;
	  ave   += re[l];
	}
	ave /= (REAL)250;
	for(l = 0;l < 250;l++){
	  re[l] -= ave; 
	}
	for(l = 0;l < 250;l++){
	  re[l] *= 0.54 - 0.46 * cos(2.0 * M_PI * l / (REAL)250);
	}
	FFT(re,im,250);
	sum_all = 0.0;
	for(l =  3;l <  32;l++){
	  sum_all += re[l] * re[l] + im[l] * im[l];
	}
	sum_1 = 0.0;
	for(l =  4;l <   8;l++){
	  sum_1   += re[l] * re[l] + im[l] * im[l];
	}
	sum_2 = 0.0;
	for(l =  8;l <  13;l++){
	  sum_2   += re[l] * re[l] + im[l] * im[l];
	}
	sum_3 = 0.0;
	for(l = 13;l <  20;l++){
	  sum_3   += re[l] * re[l] + im[l] * im[l];
	}
	X[n][k * 3 * 4 + t * 3 + 0] = sqrt(sum_1 / sum_all);
	X[n][k * 3 * 4 + t * 3 + 1] = sqrt(sum_2 / sum_all);
	X[n][k * 3 * 4 + t * 3 + 2] = sqrt(sum_3 / sum_all);
      }
    }
  }  

  return X;
}

RMatrix EEG__READ_Z(){
  RMatrix Z  (45 * 3,3);
  INT4    n;
  INT4    ans[45 * 3] = {
    1,2,0,1,1,0,2,1,2,1,2,0,2,1,0,1,2,0,1,2,1,0,1,0,2,1,0,1,2,1,0,0,1,2,1,0,2,1,0,2,1,2,0,2,1,
    1,2,0,0,2,1,2,1,2,1,0,0,2,1,2,1,2,0,2,1,0,2,1,0,1,2,0,1,0,1,2,1,0,1,0,1,2,1,2,0,0,2,0,1,0,
    1,0,2,1,0,2,2,1,2,0,1,2,0,1,2,1,0,1,0,2,1,0,2,2,1,1,0,0,1,0,2,2,0,1,2,1,2,0,1,2,0,1,2,0,1
  };
  for(n = 0;n < 45 * 3;n++){
    Z[n][ans[n]] = 1.0;
  }  

  return Z;
}

