#include "MeanRsquared.hh"




MeanRsquared::MeanRsquared (  ) : runningAverage(nullptr)
{
  this->runningAverage = new RunningStat();
  //this->t = t;
}


MeanRsquared::~MeanRsquared()
{
  delete this->runningAverage;
}


void MeanRsquared::add ( double x, double y )
{
  double rsqrd = x*x  + y*y;
  this->runningAverage->Push(rsqrd);
}
