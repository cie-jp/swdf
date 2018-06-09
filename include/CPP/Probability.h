class Multivariate_Normal_Distribution{
private:
  INT           D;
  TVector<REAL> mu;
  TMatrix<REAL> Sigma;// = L * ~L
  TMatrix<REAL> L;
  RANDOM        rnd;
public:
  Multivariate_Normal_Distribution(const TVector<REAL> &mu,
                                   const TMatrix<REAL> &Sigma){
    this->D      =  mu.get_row();
    this->mu     =  mu;
    this->Sigma  =  Sigma;
    CLDIA::choleskey(this->L,Sigma);
    RANDOM__INITIALIZE(&rnd);
  }
  
  TVector<REAL> sampling(){
    TVector<REAL> u(D);
    INT           d;

    for(d = 0;d < D;d++){
      u[d] = RANDOM__NORMAL(&rnd,0.0,1.0);
    }
    
    return mu + L * u;
  }
};

/*
  TVector<REAL> x;
  TVector<REAL> mu    = TVector<REAL>::random(5);
  TMatrix<REAL> L     = TMatrix<REAL>::random(5,5);
  TMatrix<REAL> Sigma = L * ~L;
  TVector<REAL> xbar(5);
  TMatrix<REAL> S   (5,5);
  INT           n;
  INT           N     = 100000;
  
  Multivariate_Normal_Distribution mnd(mu,Sigma);  

  for(n = 0;n < N;n++){
    x     = mnd.sampling();
    xbar +=  x;
    S    += (x - mu) * ~(x - mu);
  }

  xbar /= (REAL)N;
  S    /= (REAL)N;

  cerr << (mu | xbar) << endl;// E[x]                    = mu
  cerr << (Sigma | S) << endl;// E[(x - mu) * ~(x - mu)] = Sigma
 */

class Multivariate_Complex_Normal_Distribution{
private:
  INT           D;
  TVector<COMP> mu;
  TMatrix<COMP> Sigma;// = L * ~L
  TMatrix<COMP> L;
  RANDOM        rnd;
public:
  Multivariate_Complex_Normal_Distribution(const TVector<COMP> &mu,
                                           const TMatrix<COMP> &Sigma){
    this->D      =  mu.get_row();
    this->mu     =  mu;
    this->Sigma  =  Sigma;
    CLDIA::choleskey(this->L,Sigma);
    RANDOM__INITIALIZE(&rnd);
  }
  
  TVector<COMP> sampling(){
    TVector<COMP> u(D);
    INT           d;

    for(d = 0;d < D;d++){
      u[d] = COMPLEX__MAKE_RE_IM(RANDOM__NORMAL(&rnd,0.0,0.5),
                                 RANDOM__NORMAL(&rnd,0.0,0.5));
    }
    
    return mu + L * u;
  }
};

/*
  TVector<COMP> z;
  TVector<COMP> mu    = TVector<COMP>::random(5);
  TMatrix<COMP> L     = TMatrix<COMP>::random(5,5);
  TMatrix<COMP> Sigma = L * ~L;
  TVector<COMP> zbar(5);
  TMatrix<COMP> S   (5,5);
  INT           n;
  INT           N     = 100000;
  
  Multivariate_Complex_Normal_Distribution mcnd(mu,Sigma);  

  for(n = 0;n < N;n++){
    z     = mcnd.sampling();
    zbar +=  z;
    S    += (z - mu) * ~(z - mu);
  }

  zbar /= COMPLEX__MAKE_REAL((REAL)N);
  S    /= COMPLEX__MAKE_REAL((REAL)N);

  cerr << (mu | zbar) << endl;// E[x]                    = mu
  cerr << (Sigma | S) << endl;// E[(x - mu) * ~(x - mu)] = Sigma
 */
