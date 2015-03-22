#ifndef __POTENTIAL2D__CC__
#define __POTENTIAL2D__CC__

#include "../core/Randoms.hh"
#include "../core/Settings.hh"

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
      * Get analitic values of x(t) and y(t)
      * 
      * if x(t) == x(0)
      * then x(t+dt) == x(dt)
      * 
      * value of dt should be used as time, so 
      * we take x(t) as a starting point and move to t+dt
      * 
      * returned values should be used INSTEAD OF (x,y), NOT ADDED to old x,y
      */
     
     virtual vec getAnalyticValue(double &x, double &y, double &dt) = 0;
       

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


     
     virtual double getXderiv(double &x, double &y, long double &t) = 0;
     virtual double getYderiv(double &x, double &y, long double &t) = 0;
     
     virtual double getXanalytic(double &x, double &y, long double &t, double &dt) = 0;
     virtual double getYanalytic(double &x, double &y, long double &t, double &dt) = 0;
};


#endif
