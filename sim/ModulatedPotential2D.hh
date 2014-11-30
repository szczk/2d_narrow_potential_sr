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
 * 
 */
class ModulatedPotential2D : public Potential2D {
  
  
private:
  double freq_Q;
  
public:
  
  
  ModulatedPotential2D(double freq_Q);
  ~ModulatedPotential2D();
  
  
  
  
  virtual vec getValue ( double &x, double &y, long double &t );
  
  virtual void reset();
  
  virtual const char * toString() {
          return "V(x,y)= 1/4x^4-1/2x^2+1/4y^4 + x sin(2pi * Q*t)" ;
     }

};

#endif