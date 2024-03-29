#ifndef __SIMULATION_HH__
#define __SIMULATION_HH__

#include "../core/Randoms.hh"
#include "../core/Settings.hh"

#include "NarrowPotential2D.hh"
#include "ModulatedPotential2D.hh"
#include "../analysis/RunningStat.hh"
// #include "../main.hh"
// #include <map>
// #include <gsl/gsl_histogram2d.h>

#include "../tools/Datafile.hh"

using namespace std;

struct  point {

     double x;
     double y;

     point ( double x=0.0, double y=0.0 )  : x ( x ), y ( y ) {
     }

     point operator+ ( const point& a ) const {
          return point ( a.x+x, a.y+y );
     }
};



class Simulation {


private:
     Settings * settings;
     Randoms * rand;
     Potential2D * potential;


     double x0 ;
     double y0 ;


     double lastX; // previous position (x)
     bool measureTime;
     bool verbose;


     /**
      * Initialize anything that needs to be initialized
      */
     void init();

     /**
      *  Close anything that needs to be closed.
      */
     void destroy();


     /**
      * Reset all and prepare for new simulations
      */
     void reset();
     /**
      *  vectors dot product
      */
     double dotProduct ( const vec & v1, const vec & v2 );

     /**
      * get distance between points
      */

     double getDistance ( const point & p1 ,const point & p2 );

     /**
      * normalize vector
      */
     void norm ( vec & v );


     
     bool stateChanged ( double & x ) ;

public:
     Simulation ( Settings * );
     ~Simulation();


     /**
      * Simulate trajectory and store it in datafile.
      * Remember that trajectory is in 2D, so
      * datafile will contain pairs of [x(t),y(t)]
      *
      */
     void run ( Datafile *df );


     void setVerbose ( bool v ) {
          this->verbose = v;
     }



};

#endif
