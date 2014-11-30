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
  
  
public:
  
  
  NarrowPotential2D();
  ~NarrowPotential2D();
  
  
  
  
  virtual vec getValue ( double &x, double &y, long double &t );
  
  virtual void reset();
  
  virtual const char * toString() {
          return "V(x,y)= 1/4x^4-1/2x^2+1/4y^4";
     }

};

#endif