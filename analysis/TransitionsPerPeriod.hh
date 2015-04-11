#ifndef __TRANSITIONS_PER_PERIOD__
#define __TRANSITIONS_PER_PERIOD__


#include "../core/Settings.hh"

using namespace std;

/**
 * calculate probabilities of N transitions per period of modulating force
 *
 * 
 * 
 * not used, see  ResidenceTimeDistribution::fill
 */



class TransitionsPerPeriod {

private:
     Settings * settings;
     double periodLength;
     double forceFreq;

public:
     TransitionsPerPeriod ( Settings * );
     ~TransitionsPerPeriod();

     /**
      * add data for a given time point t
      */
     void fill ( double t, double x, double y );


};



#endif
