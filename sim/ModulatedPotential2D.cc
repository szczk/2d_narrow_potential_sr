#include "ModulatedPotential2D.hh"




ModulatedPotential2D:: ModulatedPotential2D(double freq)
{
 this->freq_Q = freq;
}

ModulatedPotential2D::~ModulatedPotential2D()
{

}

vec ModulatedPotential2D::getValue ( double& x, double& y, long double& t )
{
    vec vp;
    // d/dx V(x,y) = x^3 - x + sin ( Q t)
    // d/dy V(x,y) = y^3 
    
    vp.x = x*x*x - x + sin( 2.0 * M_PI* freq_Q * t);
    vp.y = y*y*y;   
    return vp;
}

void ModulatedPotential2D::reset()
{
  //no state, so nothing to do here
}



