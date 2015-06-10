#ifndef GRID_SIMD_H
#define GRID_SIMD_H

////////////////////////////////////////////////////////////////////////
// Define scalar and vector floating point types
//
// Scalar:   RealF, RealD, ComplexF, ComplexD
//
// Vector:  vRealF, vRealD, vComplexF, vComplexD
//
// Vector types are arch dependent
////////////////////////////////////////////////////////////////////////

typedef uint32_t Integer;

namespace Grid {

  typedef  float  RealF;
  typedef  double RealD;
#ifdef GRID_DEFAULT_PRECISION_DOUBLE
  typedef RealD   Real;
#else
  typedef RealF  Real;
#endif

  typedef std::complex<RealF> ComplexF;
  typedef std::complex<RealD> ComplexD;
  typedef std::complex<Real>  Complex;

  inline RealF adj(const RealF  & r){ return r; }
  inline RealF conjugate(const RealF  & r){ return r; }
  inline RealF real(const RealF  & r){ return r; }

  inline RealD adj(const RealD  & r){ return r; }
  inline RealD conjugate(const RealD  & r){ return r; }
  inline RealD real(const RealD  & r){ return r; }

  inline RealD sqrt(const RealD  & r){ return std::sqrt(r); }

  inline ComplexD conjugate(const ComplexD& r){ return(conj(r)); }
  inline ComplexD adj(const ComplexD& r){ return(conjugate(r)); }
  inline ComplexF conjugate(const ComplexF& r ){ return(conj(r)); }
  inline ComplexF adj(const ComplexF& r ){ return(conjugate(r)); }

  inline ComplexD innerProduct(const ComplexD & l, const ComplexD & r) { return conjugate(l)*r; }
  inline ComplexF innerProduct(const ComplexF & l, const ComplexF & r) { return conjugate(l)*r; }
  inline RealD innerProduct(const RealD & l, const RealD & r) { return l*r; }
  inline RealF innerProduct(const RealF & l, const RealF & r) { return l*r; }
  
  ////////////////////////////////////////////////////////////////////////////////
  //Provide support functions for basic real and complex data types required by Grid
  //Single and double precision versions. Should be able to template this once only.
  ////////////////////////////////////////////////////////////////////////////////
  inline void mac (ComplexD * __restrict__ y,const ComplexD * __restrict__ a,const ComplexD *__restrict__ x){ *y = (*a) * (*x)+(*y); };
  inline void mult(ComplexD * __restrict__ y,const ComplexD * __restrict__ l,const ComplexD *__restrict__ r){ *y = (*l) * (*r);}
  inline void sub (ComplexD * __restrict__ y,const ComplexD * __restrict__ l,const ComplexD *__restrict__ r){ *y = (*l) - (*r);}
  inline void add (ComplexD * __restrict__ y,const ComplexD * __restrict__ l,const ComplexD *__restrict__ r){ *y = (*l) + (*r);}
  // conjugate already supported for complex
  
  inline void mac (ComplexF * __restrict__ y,const ComplexF * __restrict__ a,const ComplexF *__restrict__ x){ *y = (*a) * (*x)+(*y); }
  inline void mult(ComplexF * __restrict__ y,const ComplexF * __restrict__ l,const ComplexF *__restrict__ r){ *y = (*l) * (*r); }
  inline void sub (ComplexF * __restrict__ y,const ComplexF * __restrict__ l,const ComplexF *__restrict__ r){ *y = (*l) - (*r); }
  inline void add (ComplexF * __restrict__ y,const ComplexF * __restrict__ l,const ComplexF *__restrict__ r){ *y = (*l) + (*r); }
  
  //conjugate already supported for complex
  
  inline ComplexF timesI(const ComplexF &r)     { return(r*ComplexF(0.0,1.0));}
  inline ComplexD timesI(const ComplexD &r)     { return(r*ComplexD(0.0,1.0));}
  inline ComplexF timesMinusI(const ComplexF &r){ return(r*ComplexF(0.0,-1.0));}
  inline ComplexD timesMinusI(const ComplexD &r){ return(r*ComplexD(0.0,-1.0));}
  inline void timesI(ComplexF &ret,const ComplexF &r)     { ret = timesI(r);}
  inline void timesI(ComplexD &ret,const ComplexD &r)     { ret = timesI(r);}
  inline void timesMinusI(ComplexF &ret,const ComplexF &r){ ret = timesMinusI(r);}
  inline void timesMinusI(ComplexD &ret,const ComplexD &r){ ret = timesMinusI(r);}
  
  inline void mac (RealD * __restrict__ y,const RealD * __restrict__ a,const RealD *__restrict__ x){  *y = (*a) * (*x)+(*y);}
  inline void mult(RealD * __restrict__ y,const RealD * __restrict__ l,const RealD *__restrict__ r){ *y = (*l) * (*r);}
  inline void sub (RealD * __restrict__ y,const RealD * __restrict__ l,const RealD *__restrict__ r){ *y = (*l) - (*r);}
  inline void add (RealD * __restrict__ y,const RealD * __restrict__ l,const RealD *__restrict__ r){ *y = (*l) + (*r);}
  
  inline void mac (RealF * __restrict__ y,const RealF * __restrict__ a,const RealF *__restrict__ x){  *y = (*a) * (*x)+(*y); }
  inline void mult(RealF * __restrict__ y,const RealF * __restrict__ l,const RealF *__restrict__ r){ *y = (*l) * (*r); }
  inline void sub (RealF * __restrict__ y,const RealF * __restrict__ l,const RealF *__restrict__ r){ *y = (*l) - (*r); }
  inline void add (RealF * __restrict__ y,const RealF * __restrict__ l,const RealF *__restrict__ r){ *y = (*l) + (*r); }
  
  inline void vstream(ComplexF &l, const ComplexF &r){ l=r;}
  inline void vstream(ComplexD &l, const ComplexD &r){ l=r;}
  inline void vstream(RealF &l, const RealF &r){ l=r;}
  inline void vstream(RealD &l, const RealD &r){ l=r;}
  
  
  class Zero{};
  static Zero zero;
  template<class itype> inline void zeroit(itype &arg){ arg=zero;};
  template<>            inline void zeroit(ComplexF &arg){ arg=0; };
  template<>            inline void zeroit(ComplexD &arg){ arg=0; };
  template<>            inline void zeroit(RealF &arg){ arg=0; };
  template<>            inline void zeroit(RealD &arg){ arg=0; };
  

  //////////////////////////////////////////////////////////
  // Permute
  // Permute 0 every ABCDEFGH -> BA DC FE HG
  // Permute 1 every ABCDEFGH -> CD AB GH EF
  // Permute 2 every ABCDEFGH -> EFGH ABCD
  // Permute 3 possible on longer iVector lengths (512bit = 8 double = 16 single)
  // Permute 4 possible on half precision @512bit vectors.
  //
  // Defined inside SIMD specialization files
  //////////////////////////////////////////////////////////
  template<class VectorSIMD>
    inline void Gpermute(VectorSIMD &y,const VectorSIMD &b,int perm);

};

#include <simd/Grid_vector_types.h>
#include <simd/Grid_vector_unops.h>

namespace Grid {
  // Default precision
#ifdef GRID_DEFAULT_PRECISION_DOUBLE
  typedef vRealD vReal;
  typedef vComplexD vComplex;
#else
  typedef vRealF vReal;
  typedef vComplexF vComplex;
#endif

 
  inline std::ostream& operator<< (std::ostream& stream, const vComplexF &o){
    int nn=vComplexF::Nsimd();
    std::vector<ComplexF,alignedAllocator<ComplexF> > buf(nn);
    vstore(o,&buf[0]);
    stream<<"<";
    for(int i=0;i<nn;i++){
      stream<<buf[i];
      if(i<nn-1) stream<<",";
    }
    stream<<">";
    return stream;
  }
 
  inline std::ostream& operator<< (std::ostream& stream, const vComplexD &o){
    int nn=vComplexD::Nsimd();
    std::vector<ComplexD,alignedAllocator<ComplexD> > buf(nn);
    vstore(o,&buf[0]);
    stream<<"<";
    for(int i=0;i<nn;i++){
      stream<<buf[i];
      if(i<nn-1) stream<<",";
    }
    stream<<">";
    return stream;
  }

  inline std::ostream& operator<< (std::ostream& stream, const vRealF &o){
    int nn=vRealF::Nsimd();
    std::vector<RealF,alignedAllocator<RealF> > buf(nn);
    vstore(o,&buf[0]);
    stream<<"<";
    for(int i=0;i<nn;i++){
      stream<<buf[i];
      if(i<nn-1) stream<<",";
    }
    stream<<">";
    return stream;
  }

  inline std::ostream& operator<< (std::ostream& stream, const vRealD &o){
    int nn=vRealD::Nsimd();
    std::vector<RealD,alignedAllocator<RealD> > buf(nn);
    vstore(o,&buf[0]);
    stream<<"<";
    for(int i=0;i<nn;i++){
      stream<<buf[i];
      if(i<nn-1) stream<<",";
    }
    stream<<">";
    return stream;
  }


}
#endif