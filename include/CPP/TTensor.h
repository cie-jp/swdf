#ifndef _TTENSOR_H_INCLUDE_
#define _TTENSOR_H_INCLUDE_

template<typename TYPE> class TTensor;
template<typename TYPE> ostream       &operator <<(ostream&             ,const TTensor<TYPE> &);

template<typename TYPE> class TTensor{
protected:
  TMatrix<TYPE> *dat;
  INT            num;
protected:
  static void initialize(TTensor<TYPE> &A,
                         const INT      num,
                         const INT      row,
                         const INT      col){
    INT i;
    
    if(num <= 0){
      ERROR__SHOW("num <= 0");
      exit(EXIT_FAILURE);
    }
    A.dat = new TMatrix<TYPE>[num];
    for(i = 0;i < num;i++){
      A.dat[i] = TMatrix<TYPE>(row,col);
    }
    A.num = num;
  }
  static void finalize  (TTensor<TYPE> &A){
    delete[] A.dat;
  }
public:
  TTensor(const INT num = 1,const INT row = 1,const INT col = 1){
    TTensor<TYPE>::initialize(*this,num,row,col);
  }
 ~TTensor(){
    TTensor<TYPE>::finalize  (*this);
  }

  TTensor(const TTensor<TYPE>  &A);

  TTensor<TYPE>  &operator  =(const TTensor<TYPE>  &);

  TMatrix<TYPE>         &operator [](const INT n)const{return this->dat[n];}

  friend ostream        &operator << <>(ostream&        os,const TTensor<TYPE> &A);

  static TTensor<TYPE> random(const INT num = 1,const INT row = 1,const INT col = 1){
    TTensor<TYPE> C(num,row,col);
    INT           i;

    for(i = 0;i < num;i++){
      C.dat[i] = TMatrix<TYPE>::random(row,col);
    }
    return C;
  }
};

template<typename TYPE> 
TTensor<TYPE>::TTensor(const TTensor<TYPE>  &A){
  INT i;

  TTensor<TYPE>::initialize(*this,A.num,A.dat[0].get_row(),A.dat[0].get_col());
  for(i = 0;i < A.num;i++){
    this->dat[i] = A.dat[i];
  }
}

template<typename TYPE> 
TTensor<TYPE> &TTensor<TYPE>::operator  =(const TTensor<TYPE>  &A){
  INT i;

  TTensor<TYPE>::finalize  (*this);
  TTensor<TYPE>::initialize(*this,A.num,A.dat[0].get_row(),A.dat[0].get_col());
  for(i = 0;i < A.num;i++){
    this->dat[i] = A.dat[i];
  }
  return *this;
}

template<typename TYPE>
ostream &operator <<(ostream &os,const TTensor<TYPE> &A){
  INT i;
  
  for(i = 0;i < A.num;i++){
    os << CLDIA::STRING("+++ (%5d / %5d) +++",i,A.num) << endl;
    os << A.dat[i] << endl;
  }
  return os;
}

#endif
