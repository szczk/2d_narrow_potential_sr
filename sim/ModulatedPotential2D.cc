#include "ModulatedPotential2D.hh"




ModulatedPotential2D:: ModulatedPotential2D ( double a, double b, double c, double a0, double freq )
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
     vp.x = this->getXderiv ( x,y,t );
     vp.y = this->getYderiv ( x,y,t );
     return vp;
}

void ModulatedPotential2D::reset()
{
     //no state, so nothing to do here
}


vec ModulatedPotential2D::getAnalyticValue ( double &x, double &y, double &dt )
{
     throw "implement me!";
}

double ModulatedPotential2D::getXderiv ( double &x, double &y, long double &t )
{
     // d/dx V(x,y) = B x^3 - A x + A0 sin ( Q t)
     return param_B *x*x*x - param_A * x + param_A0 * sin ( 2.0 * M_PI* freq_Q * t );
}

double ModulatedPotential2D::getYderiv ( double &x, double &y, long double &t )
{
     // d/dy V(x,y) = y^3
     return param_C * y*y*y;
}

double ModulatedPotential2D::getXanalytic ( double &x, double &y, double &t )
{
  //just an approximation, since solving dx/dx = -b x^3 + a x - A sin(omega t)  is not so easy,
  // so we solve without modulation and just add modulation part later
     return ( sqrt ( param_A ) *exp ( param_A * t ) *x ) / ( sqrt ( param_A + param_B*x*x* ( exp ( 2.0*param_A*t ) - 1.0 ) ) ) + param_A0 * sin ( 2.0 * M_PI* freq_Q * t );
}

double ModulatedPotential2D::getYanalytic ( double &x, double &y, double &t )
{
     return ( y/ ( sqrt ( 1.0 + ( 2.0*param_B*t*y*y ) ) ) );
}
