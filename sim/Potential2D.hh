#ifndef __POTENTIAL2D__CC__
#define __POTENTIAL2D__CC__

#include "Randoms.hh"
#include "Settings.hh"

using namespace std;


/**
 *  Represents 2D potential
 *
 *  V(x,y)
 *
 *  operator(x,y)
 *  actually returns f(x,y) = - grad V(x,y)
 */


class Potential2D {


public:
     Potential2D();
     virtual ~Potential2D();
     

     /**
      * Return the value of V(x, y,t)
      */
     virtual vec getValue ( double &x, double &y, long double &t ) = 0 ;

     // overloaded operator() for convinience
     virtual vec operator() ( double &x, double &y,  long double &t ) {
          return this->getValue ( x,y,t );
     }


     /**
      *
      * reset potential state if it has any
      */
     virtual void reset() = 0;


     /**
      * Get some text description of the potential
      */
     virtual const char * toString() {
          return "abstract Potential2D class! ";
     }


};


#endif
