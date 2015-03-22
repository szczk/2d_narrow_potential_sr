#include "NarrowPotential2D.hh"




NarrowPotential2D:: NarrowPotential2D ( double a, double b, double c, double a0 )
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
     vp.x = this->getXderiv ( x,y,t );
     vp.y = this->getYderiv ( x,y,t );
     return vp;
}

void NarrowPotential2D::reset()
{
     //no state, so nothing to do here
}


vec NarrowPotential2D::getAnalyticValue ( double &x, double &y, double &dt )
{
     throw "implement me!";
}

double NarrowPotential2D::getXderiv ( double &x, double &y, long double &t )
{
     // d/dx V(x,y) = x^3 - x
     // vp.x = x*x*x -x;
     return param_B *x*x*x - param_A * x;
}

double NarrowPotential2D::getYderiv ( double &x, double &y, long double &t )
{
     // d/dy V(x,y) = y^3
     // vp.y = y*y*y;
     return param_C * y*y*y;
}


double NarrowPotential2D::getXanalytic ( double &x, double &y, double &t )
{
     return ( sqrt ( param_A ) *exp ( param_A * t ) *x ) / ( sqrt ( param_A + param_B*x*x* ( exp ( 2.0*param_A*t ) - 1.0 ) ) );
}

double NarrowPotential2D::getYanalytic ( double &x, double &y, double &t )
{
     return ( y/ ( sqrt ( 1.0 + ( 2.0*param_B*t*y*y ) ) ) );
}
