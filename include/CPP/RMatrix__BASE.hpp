// *************************************************
// コンストラクタ
// *************************************************
RMatrix::RMatrix(INT row,INT col){
  RMatrix::initialize(*this,row,col);
  RMatrix::zerofill  (*this);
}

// *************************************************
// コピーコンストラクタ
// *************************************************
RMatrix::RMatrix(const RMatrix &A){
  RMatrix::initialize(*this,A.row,A.col);
  RMatrix::datacopy  (*this,A.dat);
}

// *************************************************
// デストラクタ
// *************************************************
RMatrix::~RMatrix(){
  RMatrix::finalize(*this);
}
