#ifndef __ANALYSIS_HH__
#define __ANALYSIS_HH__

#include <map>
#include <vector>

#include "../core/Settings.hh"
#include "../tools/Datafile.hh"

#include <typeinfo>

// #include "MeanRsquared.hh"
// #include "MarginalDistributions.hh"

#include "RunningStat.hh"
#include "ResidenceTimeDistribution.hh"

//delete when not needed
// #include "HistogramsProducer.hh"
// #include "EDFProducer.hh"


using namespace std;


/**
 * over-all analysis interface
 *
 * uses trajectories datafiles iterator to iterate over
 * trajectories and over t
 * and fills all the analysis classes working on a single t
 * and so on
 */

class Analysis {

private:
     Settings * settings;

//      TrajectoriesDatafilesIterator * trajIterator;

     // analysis modules mapped by time
     map<double, RunningStat *> * meanXs;
     map<double, RunningStat *> * meanYs;


     // counters of walker in left/right potential minima
     map<double, int*> * inLeftCounter;
     map<double, int*> * inRightCounter;



     ResidenceTimeDistribution * rtd;


     void initAnalysis();
     void deleteAnalysis();


     bool calculated;
     //save x(t), var(x)(t) y(t) var(y)(t)
     void saveMean ( std::map< double, RunningStat* >* meanPos, const char * variable );
     // save p(left)(t) p(right)(t);
     void savePositions();

public:
     Analysis ( Settings * );

     ~Analysis();


     /**
      * Pass an open datafile to be iterated over t and filled from
      */
     void fillFromFile ( Datafile * );

     /**
      * add data for a given time point t
      */
     void fill ( double t, double x, double y );

     /**
      * Calculate everything that needs to be calculated
      */
     void calculate();




     /**
      * Save everything that needs to be saved.
      * calculate() should be manually called first
      * as it is not called automatically
      *
      */
     void save();

     /**
      * close everything and delete objects
      */
     void close();

     template <typename T> T*  init ( T * );

     template <typename T>  T* get ( double t, map<double,T*>* );

     template <typename T> void deleteMap ( map<double, T*> * map );
};

#endif
