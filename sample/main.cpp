#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

int main(){
  DTIME__PRINT(DTIME__NOW_JST(),stdout);
  fprintf(stdout,"\n");
  DTIME__PRINT(DTIME__MAKE_FROM_TEXT("2017-05-03 06:30"),stdout);
  fprintf(stdout,"\n");
}
