// *************************************************
// 代入演算子
// *************************************************
CMatrix  &CMatrix::operator  =(const CMatrix &A){
  CMatrix::resize    (*this,A.row,A.col);
  CMatrix::datacopy  (*this,A.dat);
  return *this;
}

// *************************************************
// 配列演算子
// *************************************************
COMP     *CMatrix::operator [](const INT n)const{
  return &this->dat[n * this->col];
}

// *************************************************
// 加算演算子(行列)
// *************************************************
CMatrix  &CMatrix::operator +=(const CMatrix &A){
  return *this = *this + A;
}

// *************************************************
// 加算演算子(実数)
// *************************************************
CMatrix  &CMatrix::operator +=(const COMP     k){
  return *this = *this + k;
}
/*
// *************************************************
// 減算演算子(行列)
// *************************************************
CMatrix  &CMatrix::operator -=(const CMatrix &A){
  return *this = *this - A;
}

// *************************************************
// 減算演算子(実数)
// *************************************************
CMatrix  &CMatrix::operator -=(const COMP     k){
  return *this = *this - k;
}

// *************************************************
// 乗算演算子(行列)
// *************************************************
CMatrix  &CMatrix::operator *=(const CMatrix &A){
  return *this = *this * A;
}

// *************************************************
// 乗算演算子(実数)
// *************************************************
CMatrix  &CMatrix::operator *=(const COMP     b){
  return *this = *this * b;
}

// *************************************************
// 乗算演算子(行列) (成分同士の乗算)
// *************************************************
CMatrix  &CMatrix::operator %=(const CMatrix &A){
  return *this = *this % A;
}

// *************************************************
// 除算演算子(実数)
// *************************************************
CMatrix  &CMatrix::operator /=(const COMP     b){
  return *this = *this / b;
}

// *************************************************
// 除算演算子(行列) (成分同士の除算)
// *************************************************
CMatrix  &CMatrix::operator /=(const CMatrix &A){
  return *this = *this / A;
}

// *************************************************
// 縦結合演算子
// *************************************************
CMatrix  &CMatrix::operator &=(const CMatrix &A){
  return *this = *this & A;
}

// *************************************************
// 横結合演算子
// *************************************************
CMatrix  &CMatrix::operator |=(const CMatrix &A){
  return *this = *this | A;
}
*/
// *************************************************
// 出力
// *************************************************
ostream &operator <<(ostream     &os,const CMatrix &A){
  CHAR str[256];
  INT  i,j;

  os << "=============(" << A.row << "," << A.col << ")=============" << endl;  
  for(i = 0;i < A.row;i++){
    os << "| "; 
    for(j = 0;j < A.col;j++){
      sprintf(str,"(%10.5lf,%10.5lf) ",COMPLEX__REAL(A.dat[i * A.col + j]),COMPLEX__IMAG(A.dat[i * A.col + j]));
      os << str;
    }
    os << "|" << endl;
  }
  
  return os;
}
