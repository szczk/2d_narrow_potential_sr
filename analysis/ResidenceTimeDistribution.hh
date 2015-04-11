#ifndef __RESIDENCE_TIME_DISTIBUTION_HH__
#define __RESIDENCE_TIME_DISTIBUTION_HH__

#include <iostream>
#include <map>
#include "../core/Settings.hh"
#include "gsl/gsl_histogram.h"


using namespace std;


/**
 * tools class to calculate residence time distributions
 * for p(t_left), p(t_right), p(t)
 *
 * Analysis class just passes the current (x,t)(t) so we have to
 * manually calcualte residence times here. Fortunately
 * analysis is iterating over every trajectory lineary from start to end,
 * so values coming to fill(t,x,y) will be consequent and not random.
 * Also, receiving t=0.0 will mean starting new trajectory
 */

class ResidenceTimeDistribution {


private:
     Settings * settings;
     gsl_histogram * p_left;
     gsl_histogram * p_right;
     gsl_histogram * p_total;

     int nBins;
     double tMin;
     double tMax;

     //
     double statesBorderX;
     double stateThresholdAbs;
     double residenceTimeStart ;
     double lastPosition ;

     double period;
     double periodStartTime;
     int numberOfTransitions;
     double x0;

     void init();
     void cleanUp();

     
     /**
      * counters for transitions per period
      * key = number of transitions per period
      * value = counter of  occurences with [key] transitions per  period
      */
     map<int,int*> * number_of_transitions_per_period ;

     gsl_histogram * initHisto ( gsl_histogram * );
     void deleteHisto ( gsl_histogram * );

     void saveHisto ( gsl_histogram *, const char * );

public:

     ResidenceTimeDistribution ( Settings * );
     ~ResidenceTimeDistribution();


     void fill ( double t, double x, double y );
     void save();


};

#endif
