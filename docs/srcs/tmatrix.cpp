#include<iostream>
#include<CLDIA>

using namespace std;
using namespace CLDIA;

int main(void){
  TMatrix<STRING> dat;

  dat = TMatrix<STRING>::fetch("input.csv", // 入力ファイル名
                               ", \t",      // セパレータリスト
                               "#");        // コメント行識別子

  cout << dat << endl;

  return 0;
}
