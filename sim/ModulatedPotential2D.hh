#ifndef __MODULATED_POTENTIAL_2D__
#define __MODULATED_POTENTIAL_2D__

#include "Potential2D.hh"
#include <cmath>

using namespace std; 

/*
 * modulated potential 
 * V(x,y,t )= 1/4x^4-1/2x^2+1/4y^4 + x* sin( Q * t) 
 * 
 * 
 * -a/2 x^2 + b/4 x^4 + c/4 y^4 + A0 x cos(Q t)
 * 
 * 
 * dV/dx = -A x + b x^3 - A0 sin(Qt)
 * dV/dy = c x^3
 */
class ModulatedPotential2D : public Potential2D {
  
  
private:
  double freq_Q;
  double param_A;
  double param_B;
  double param_C;
  double param_A0;
  
public:
  
  
  ModulatedPotential2D(double,double,double,double,double freq_Q);
  ~ModulatedPotential2D();
  
  
  
  
  virtual vec getValue ( double &x, double &y, long double &t );
  
  virtual void reset();
  
  virtual const char * toString() {
          return "V(x,y)= 1/4 x^4 - 1/2 x^2 + 1/4y^4 + x sin(2pi * Q*t)" ;
     }
     
  virtual vec getAnalyticValue(double &x, double &y, double &dt);

};

#endif