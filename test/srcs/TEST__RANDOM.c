/*****************************************************************
 *
 * 乱数検証プログラム
 * 
 *
 *                           Created  by Mamoru Ota (2018/03/05)
 * 
 *****************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<RANDOM.h>

#define DAT_DIR "./test/dat/"

#define NUM     (90000)

int main(void){
  FILE   *fp;
  RANDOM  rnd;
  int     n;
  double  pi[5] = {10.0,20.0,50.0,5.0,15.0};
  double  theta0;
  double  phi0;
  double  kappa;
  double  theta;
  double  phi;
  
  RANDOM__INITIALIZE(&rnd);

  if((fp = fopen(DAT_DIR "random_uniform.dat","w")) == NULL){
    exit(EXIT_FAILURE);
  }
  
  for(n = 0;n < NUM;n++){
    fprintf(fp,"%f\n",RANDOM__UNIFORM(&rnd,-1.0,3.0));
  }

  fclose(fp);

  // =============================================================

  if((fp = fopen(DAT_DIR "random_normal.dat","w")) == NULL){
    exit(EXIT_FAILURE);
  }
  
  for(n = 0;n < NUM;n++){
    fprintf(fp,"%f\n",RANDOM__NORMAL(&rnd,-5.0,3.0));
  }

  fclose(fp);

  // =============================================================

  if((fp = fopen(DAT_DIR "random_log_normal.dat","w")) == NULL){
    exit(EXIT_FAILURE);
  }
  
  for(n = 0;n < NUM;n++){
    fprintf(fp,"%f\n",RANDOM__LOG_NORMAL(&rnd,-5.0,3.0));
  }

  fclose(fp);

  // =============================================================

  if((fp = fopen(DAT_DIR "random_exponential.dat","w")) == NULL){
    exit(EXIT_FAILURE);
  }
  
  for(n = 0;n < NUM;n++){
    fprintf(fp,"%f\n",RANDOM__EXPONENTIAL(&rnd,3.0));
  }

  fclose(fp);
  
  // =============================================================

  if((fp = fopen(DAT_DIR "random_gamma.dat","w")) == NULL){
    exit(EXIT_FAILURE);
  }
  
  for(n = 0;n < NUM;n++){
    fprintf(fp,"%f\n",RANDOM__GAMMA(&rnd,5.0,2.0));
  }

  fclose(fp);

  // =============================================================

  if((fp = fopen(DAT_DIR "random_invgamma.dat","w")) == NULL){
    exit(EXIT_FAILURE);
  }
  
  for(n = 0;n < NUM;n++){
    fprintf(fp,"%f\n",RANDOM__INV_GAMMA(&rnd,5.0,2.0));
  }

  fclose(fp);

  // =============================================================
  
  if((fp = fopen(DAT_DIR "random_gig3_1.dat","w")) == NULL){
    exit(EXIT_FAILURE);
  }
  
  for(n = 0;n < NUM;n++){
    fprintf(fp,"%f\n",RANDOM__GIG3(&rnd,3.0,2.0,4.0));
  }

  fclose(fp);

  // =============================================================
  
  if((fp = fopen(DAT_DIR "random_gig3_2.dat","w")) == NULL){
    exit(EXIT_FAILURE);
  }
  
  for(n = 0;n < NUM;n++){
    fprintf(fp,"%f\n",RANDOM__GIG3(&rnd,3.0,2.0,-4.0));
  }

  fclose(fp);

  // =============================================================
  
  if((fp = fopen(DAT_DIR "random_multinomial.dat","w")) == NULL){
    exit(EXIT_FAILURE);
  }
  
  
  for(n = 0;n < NUM;n++){
    fprintf(fp,"%d\n",RANDOM__MULTINOMIAL(&rnd,pi,5));
  }

  fclose(fp);

  // =============================================================
  
  if((fp = fopen(DAT_DIR "random_truncated_normal.dat","w")) == NULL){
    exit(EXIT_FAILURE);
  }
  
  
  for(n = 0;n < NUM;n++){
    fprintf(fp,"%f\n",RANDOM__TRUNCATED_NORMAL(&rnd,0.1,2.0));
  }

  fclose(fp);

  // =============================================================
  
  if((fp = fopen(DAT_DIR "random_von_mises_fisher.dat","w")) == NULL){
    exit(EXIT_FAILURE);
  }
  
  theta0 = 45.0 / 180.0 * M_PI;
  phi0   = 15.0 / 180.0 * M_PI;
  kappa  = 20.0;
  
  for(n = 0;n < NUM;n++){
    RANDOM__VON_MISES_FISHER(&rnd,&theta,&phi,theta0,phi0,kappa);
    fprintf(fp,"%f %f\n",theta / M_PI * 180.0,phi / M_PI * 180.0);
  }

  fclose(fp);
  
  return 0;
}
