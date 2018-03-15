// *************************************************
// コンストラクタ
// *************************************************
CMatrix::CMatrix(INT row,INT col){
  CMatrix::initialize(*this,row,col);
  CMatrix::zerofill  (*this);
}

// *************************************************
// コピーコンストラクタ
// *************************************************
CMatrix::CMatrix(const CMatrix &A){
  CMatrix::initialize(*this,A.row,A.col);
  CMatrix::datacopy  (*this,A.dat);
}

// *************************************************
// デストラクタ
// *************************************************
CMatrix::~CMatrix(){
  CMatrix::finalize(*this);
}
