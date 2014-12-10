#ifndef __MEAN_R__
#define __MEAN_R__

#include "RunningStat.hh"



using namespace std;

/**
 * mean r^2 =  x^2 + y^2
 * for a single time t
 */


class MeanRsquared {

private:
     RunningStat * runningAverage;
     //double t;

public:

     MeanRsquared ( );
     ~MeanRsquared();


     void add ( double x, double y );


     double getMeanValue() {
          return this->runningAverage->Mean();
     }

     
     //double getT() { return this->t;}
};

#endif
