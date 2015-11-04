#include "Settings.h"
#include "SphericalFFT.h"
#include "Grid1DRISM.h"
#include "ArrayOperations.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "writeDoubleArrayToFile.h"

#include "ParseString.h"
#include "StringParser.h"

#include "Matrix.h"
#include "SolutionRISM.h"
#include "Grid.h"
#include "Grid1DRISM.h"

#include "ParseParameter.h"
#include "ParsePair.h"
#include "ParseKeyValuePair.h"
#include "ParseArray.h"
#include "Parameters.h"
#include "ParseParameters.h"

#include "readFile.h"
#include "ParametersAdaptor1DRISM.h"

//class OZ1D_Solution : public Solution
//{
//public:
 //  int nspec;
 //  double *raw_data
//

//};

#include <map>


using namespace std;

class A
{
public:
  int X;
 
   A(const A & a ) 
   {
      this->X = a.X;
      printf("COPY ME: %d\n",this->X);
   } 

   A(int x) {X=x;}

   bool operator<(const A& b) const
   {
      return this->X < b.X;
   }

};


template<class T>
class CleverMatrix  : public Matrix<T>
{

public:
  int m_zsize, m_zshift;
  int m_m,m_n;

  Real *m_data;
  
  CleverMatrix() {}

  CleverMatrix( Real *raw_data,  
             int zsize,
             int zshift,
             int m,
             int n
           )
 {
    init(raw_data,zsize,zshift,m,n); 
 }

 void init( Real *raw_data,  
             int zsize,
             int zshift,
             int m,
             int n
           )
 { 
   m_m = m;
   m_n = n;
   m_zsize = zsize; 
   m_zshift = zshift;
   m_data = raw_data;
 }

 ~CleverMatrix()
 {}

  virtual Integer getNumRows() { return m_m;}
  virtual Integer getNumCols() { return m_n;}

  virtual T getAt(Integer row,Integer col)
  {
     return m_data[ m_zshift + (row * m_n + col) *  m_zsize ];
  }

  virtual void setAt(Integer row,Integer col,T x)
  {
     m_data[  m_zshift + (row * m_n + col) *  m_zsize ] = x;
  }

}; 

//1 1 2 2   2 3 4 5 
//1 1 2 2

//M1:  x[1]  x[N+1]   ..  x[N*n+1]
 //    x[N*(n+1) +1] ...  x[N*2n+1]
 //    ..
 //    x[N*((m-1)n+1) +1 ] ...  x[ N*mn + 1]

//Z-size
//Z-shift

//0 

//M[ij] =  M[ Z-shift + ( i * n + j ) * Z-size ] 
//
//     x[2N+1] x[3N+1]
//
//M2:  x[2]    x[N+2] ... 
//     x[2N+2] 

//}


class Solution_RISM_Bulk : public SolutionRISM<Real>
{
public:
    CleverMatrix<Real> *m_matrix_list;

    Solution_RISM_Bulk( Grid *grid, int nsites )
    : SolutionRISM<Real>( grid, nsites * nsites )
    { Grid1DRISM *grd = (Grid1DRISM *)grid;
         
      m_matrix_list = new CleverMatrix<Real> [ grd->getN() ];
      int i;
      for(i=0;i<grd->getN(); i++)
      {
          m_matrix_list[i].init( this->getRawData(), // Real *raw_data,  
                                 this->getSizeOfOneGamma(), //   int zsize,
                                 i, //    int zshift,
                                 nsites, //  int m,
                                 nsites  //  int n
                                 );
      }
     
    }
/*
    void matrix_inv(SolutionOZ1D *result = NULL)
    {
        if(result == NULL) result = this;

        SimpleMatrix<Real> R(nspec,nspec)
        for(i=0; i< this->getSizeOfOneGamma(); i++)
        {
            inverse_matrix( &m_matrix_list[i], &R);
            R.copy( &(result->m_matrix_list[i]) );
        }
    }

    void matrix_mul(SolutionOZ1D *other,SolutionOZ1D *result = NULL)
    {
        if(result == NULL) result = this;

        SimpleMatrix<Real> R(nspec,nspec)
        for(i=0; i< this->getSizeOfOneGamma(); i++)
        {
            mul_matrix( &m_matrix_list[i], &result->m_matrix_list[i],&R);
            R.copy( &(result->m_matrix_list[i]) );
        }
    }
*/
//    void mul_by_diag(


};

//
//class ParametersAdaptor_RISM_Bulk : public ParametersAdaptor {

//GET_LIST_PARAMETER("sites")

//GET_STRING_PARAMETER("sites",SiteLabels)
//GET_STRING_PARAMETER

//};

/*
GridIndependent_RISM_Bulk
{
  nxn Matrix<Real> *W;
  1xn : densities ;

  Parameters

  GridIndependent_RISM_Bulk( ParametersAdaptor  )

  
};


GridDependent1DRISM 
{
  Solution1DRISM *bridge
  Solution1DRISM *U;
  Solution1DRISM *CL;
};



Operator1DRISM
     
//  Matrix<Real> *W; Gamma = H - CS  --> H = Gamma + CS
  H = CS + CL +G = WC(W+R(G+C)) 

1)  H = W(CS + CL)(W+RH)
2)  Gamma = H - CS
3)  H + 1 = Gamma + CS + 1 = exp( (-beta U - CL) + Gamma  + B)     --> -beta (U + CL/beta)
   H - C = Gamma                                                        CL = -beta U_L => CL/beta = -UL

    Gamma + CS +1 = exp ( - beta US + Gamma + B) 
3)  CS - exp( - beta US + Gamma + B ) - Gamma - 1
 ==> In this case we do not deal with W^-1 (potentially degenerate)! 



  Gamma + C + 1 = exp(-beta U + Gamma  + B) ==> 
  C = exp(-beta U + Gamma + B) - Gamma - 1

  H = WC(W+RH)
  WC = H(W+RH)^-1
  C = W^-1 H (W+RH)^-1  
   ---
   H = W(CS+CL)(W+RH) = WCS(W+RH) + W CL (W+RH)
   W(CS + CL) =  H ( W+RH)^-1
   W CS =  H (W+RH)^-1 - W*CL
   CS = W^-1 H (W+RH)^-1 - CL

   h + 1 
};


class Operator1DRISM_HNCplus : public Operator
{
protected:
//	GridIndependentData *m_gridIndependent;
//	GridDependentData *m_gridDependent;

public:

	Operator1DRISM_HNCplus()
	{
		m_gridIndependent = NULL;
		m_gridDependent = NULL;
	}

	virtual GridDependentData *getGridDependent()
	{
		return m_gridDependent;
	}

	virtual GridIndependentData *getGridIndependent()
	{
		return m_gridIndependent;
	}

	Operator(GridIndependentData *gridIndependent, GridDependentData *gridDependent)
	{
		m_gridIndependent = gridIndependent;
		m_gridDependent = gridDependent;
	}

	virtual void F(Solution *x,Solution *result)=0;		// result = F(x)
        {
             (SolutionRISM *)

           step 1:

               
              -------------- OZ
              H = C + R*C*H
              C*(I+R*H) = H
              C = H*(I+RH)^-1
              
              
    
              C = CS + CL
              H = CS + CL + R*H*(CS + CL) 
              ( I + RH) CS + (I+RH)*CL = H
              CS = (I+RH)^-1 * (H - (I+RH)*CL) 
 
              -------------- RISM
              H = WC( W + R*H)
              WC = H*(W+RH)^-1
              C = W^-1 *H*(W+RH)^-1   W --> I

           step 2:
             g = exp( -beta U + h - c + B)             

        }

};

class OperatorFactory : public Object
{
public:
	
	virtual Operator *createOperator(GridIndependentData *,GridDependentData *)=0;
};

*/

struct lessA {

bool operator()(const A* a, const A* b) const
{
  return a->X < b->X;
}

};

template<class X>
struct lessPtr
{
 bool operator()(const X* a,const X*b) const
 {
    return *a < *b;
 }
};


main(int argc,const char **argv)
{
  typedef  map<A*,A*,lessPtr<A> > MAP;
  typedef  MAP::iterator IT;

  MAP m;

  A aa(1);
  A bb(2);
  A cc(3);

  m[&aa] = &bb;
  m[&bb] = &cc;
  m[&cc] = &aa; 

  IT it;
  for(it=m.begin(); it!=m.end(); it++)
  {
     pair<A*,A*> dat = *it;
     printf("%d --> %d\n",dat.first->X,dat.second->X);
  }

//  return 0;

   const char *fname = (argc>1) ? argv[1] : "rismmol1d.prm"; 
   const char *str = readFile(fname); //distances = {(O,H1) : 1 [Angstr], (O,H2) : 1 [Angstr], (H1,H2) : 1.63[Angstr] };";
   StringParser sp(str);

   Parameters prm;
   ParseParameters pp("Bohr","Hartree",&prm);

   pp.parse(&sp);

   printf("%s\n",prm.toString());
   

   ParametersAdaptor1DRISM pa(&prm);
   pa.init();

   Matrix<Real> *dd =pa.getDistances();
   int ii,jj;
   for(ii=0;ii<dd->getNumRows();ii++)
   {
      for(jj=0;jj<dd->getNumCols();jj++)
      {
          printf("%lf ",dd->getAt(ii,jj));
      }
      printf("\n");
   }

   free((void *)str);
   return 0;

   int N = 4096;
   double dR = 0.05;
   SphericalFFT *fft = SphericalFFT::getInstance(); 
   Grid1DRISM grd(N,dR);

   Real *a = new Real[N]; 
   Real *fa = new Real[N];
   Real *b = new Real[N];
   Real *fb = new Real[N];
   Real *c = new Real[N];
   Real *fc = new Real[N];

   int i;
   for(i=0;i<N;i++) 
   { 
     a[i] = i % 20; 
     b[i] = exp(-(i*dR)*(i*dR));
   }
   
   fft->d3fft(a,fa,&grd); 
   fft->d3fft(b,fb,&grd);

   copyArray(fc,fa,N); // fc=fa
   mulArray(fc,fb,N);  // fc=fa*fb
   
   fft->d3ifft(fc,c,&grd);
   
   writeDoubleArrayToFile("a.dat",a,N);
   writeDoubleArrayToFile("fa.dat",fa,N);

   writeDoubleArrayToFile("b.dat",b,N);
   writeDoubleArrayToFile("fb.dat",fb,N);

   writeDoubleArrayToFile("c.dat",c,N);
   writeDoubleArrayToFile("fc.dat",fc,N);

   delete [] a;
   delete [] b;
   delete [] c;
   delete [] fa;
   delete [] fb;
   delete [] fc;
   

}
