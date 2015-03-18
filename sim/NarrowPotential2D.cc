#include "NarrowPotential2D.hh"




NarrowPotential2D:: NarrowPotential2D(double a, double b, double c, double a0)
{
 this->param_A = a;
 this->param_B = b;
 this->param_C = c;
 this->param_A0 = a0;
}

NarrowPotential2D::~NarrowPotential2D()
{

}

vec NarrowPotential2D::getValue ( double& x, double& y, long double& t )
{
    vec vp;
    // d/dx V(x,y) = x^3 - x
    // d/dy V(x,y) = y^3
//     vp.x = x*x*x -x;
//     vp.y = y*y*y;   
    vp.x = param_B *x*x*x - param_A * x ;
    vp.y = param_C * y*y*y;   
    
    return vp;
}

void NarrowPotential2D::reset()
{
  //no state, so nothing to do here
}


vec getAnalyticValue(double &x, double &y, double &dt) 
{
  throw "implement me!";
}
