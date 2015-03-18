#ifndef __NARROW_POTENTIAL_2D__
#define __NARROW_POTENTIAL_2D__

#include "Potential2D.hh"


using namespace std; 

/*
 * 
 * V(x,y)= 1/4x^4-1/2x^2+1/4y^4
 * 
 * 
 * 
 */
class NarrowPotential2D : public Potential2D {
  
  
private:
    double param_A;
  double param_B;
  double param_C;
  double param_A0;
  
public:
  
  
  NarrowPotential2D(double,double,double,double);
  ~NarrowPotential2D();
  
  
  
  
  virtual vec getValue ( double &x, double &y, long double &t );
  
  virtual void reset();
  
  virtual const char * toString() {
          return "V(x,y)= 1/4x^4-1/2x^2+1/4y^4";
     }
     
  virtual vec getAnalyticValue(double &x, double &y, double &dt);

};

#endif