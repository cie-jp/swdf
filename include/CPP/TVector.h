#ifndef _TVECTOR_H_INCLUDE_
#define _TVECTOR_H_INCLUDE_

template<typename TYPE> class TVector : public TMatrix<TYPE>{
 public:
  //   1次元  ベクトル(スカラー)を作成
  TVector()                   : TMatrix<TYPE>(  1,1){}
  // dim次元縦ベクトル          を作成  
  TVector(int dim)            : TMatrix<TYPE>(dim,1){}
  // TMatrix<TYPE>クラスから初期化(名前ありインスタンス)
  TVector(const TMatrix<TYPE>  &A){
    INT row = A.get_row();
    INT col = A.get_col();
    
    if((row != 1) && (col != 1)){
      ERROR__SHOW("(row != 1) && (col != 1)");
      exit(EXIT_FAILURE);
    }
    TMatrix<TYPE>::initialize(*this,row,col);
    TMatrix<TYPE>::datacopy  (*this,A.get_dat());    
  }  
  // TMatrix<TYPE>クラスから初期化(名前なしインスタンス)
  TVector(      TMatrix<TYPE> &&A){
    INT   row = A.get_row();
    INT   col = A.get_col();
    TYPE *dat = A.get_dat();

    this->dat = ((row == 1) && (col == 1)) ? &this->scl : dat;
    this->scl = dat[0];
    this->row = row;
    this->col = col;
    TMatrix<TYPE>::release(A);
  }  

  // ベクトルの次元を取得
  INT get_dim()const{return MACRO_MAX(this->row,this->col);}

  // **********************************************************************************
  // 演算子のオーバーロード
  // **********************************************************************************
  // 添え字演算子
  TYPE          &operator [](const int n)const{return this->dat[n];}
  //   代入演算子(名前ありインスタンス)
  TVector<TYPE> &operator  =(const TMatrix<TYPE>  &A){
    INT row = A.get_row();
    INT col = A.get_col();
    
    if((row != 1) && (col != 1)){
      ERROR__SHOW("(row != 1) && (col != 1)");
      exit(EXIT_FAILURE);
    }
    TMatrix<TYPE>::initialize(*this,row,col);
    TMatrix<TYPE>::datacopy  (*this,A.get_dat());    
    return *this;    
  }
  //   代入演算子(名前なしインスタンス)
  TVector<TYPE> &operator  =(      TMatrix<TYPE> &&A){
    INT   row = A.get_row();
    INT   col = A.get_col();
    TYPE *dat = A.get_dat();
        
    TMatrix<TYPE>::finalize(*this);
    this->dat = ((row == 1) && (col == 1)) ? &this->scl : dat;
    this->scl = dat[0];
    this->row = A.get_row();
    this->col = A.get_col();
    TMatrix<TYPE>::release (A);
    return *this;    
  }
  
  // 正規乱数で初期化されたdim次元縦ベクトルを生成
  static TVector<TYPE> random(const INT dim){return TMatrix<TYPE>::random(dim,1);}
};

#endif
