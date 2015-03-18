#include "ModulatedPotential2D.hh"




ModulatedPotential2D:: ModulatedPotential2D(double a, double b, double c, double a0, double freq)
{
 this->freq_Q = freq;
 this->param_A = a;
 this->param_B = b;
 this->param_C = c;
 this->param_A0 = a0;
}

ModulatedPotential2D::~ModulatedPotential2D()
{

}

vec ModulatedPotential2D::getValue ( double& x, double& y, long double& t )
{
    vec vp;
    // d/dx V(x,y) = B x^3 - A x + A0 sin ( Q t)
    // d/dy V(x,y) = y^3 
    
    vp.x = param_B *x*x*x - param_A * x + param_A0 * sin( 2.0 * M_PI* freq_Q * t);
    vp.y = param_C * y*y*y;   
    return vp;
}

void ModulatedPotential2D::reset()
{
  //no state, so nothing to do here
}


vec getAnalyticValue(double &x, double &y, double &dt) 
{
  
  
}

