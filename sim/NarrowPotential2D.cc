#include "NarrowPotential2D.hh"




NarrowPotential2D:: NarrowPotential2D()
{

}

NarrowPotential2D::~NarrowPotential2D()
{

}

vec NarrowPotential2D::getValue ( double& x, double& y, long double& t )
{
    vec vp;
    // d/dx V(x,y) = x^3 - x
    // d/dy V(x,y) = y^3
    vp.x = x*x*x -x;
    vp.y = y*y*y;   
    return vp;
}

void NarrowPotential2D::reset()
{
  //no state, so nothing to do here
}



