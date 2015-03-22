#include "Simulation.hh"

inline ostream& operator<< ( ostream &out, point &cPoint )
{
     // Since operator<< is a friend of the Point class, we can access
     // Point's members directly.
     out << "(" << cPoint.x << ", " <<  cPoint.y << ")";
     return out;
}



Simulation::Simulation ( Settings * set )  : rand ( nullptr ), potential ( nullptr ),  x0 ( 0.0 ), y0 ( 0.0 ),  lastX ( 0.0 ), measureTime ( false ), verbose ( false )
{

     this->settings = set;

     this->init();
}


Simulation::~Simulation()
{
     this->destroy();
}



void Simulation::destroy()
{
     cout << "destroying simulation"<<endl;

     if ( rand!=nullptr ) delete rand;
     if ( potential!=nullptr ) delete potential;
}


void Simulation::init()
{
     cout << "initializing simulation"<<endl;
     this->rand = new Randoms();


     //double beta = settings.getWaitingTimesParameter();

     //this->meanEscapeTime = new RunningStat();

     //this->reset();
}


void Simulation::reset()
{
     //this->rand->reset();

     if ( potential!=nullptr ) delete potential;

     int potentialType = this->settings->get ( "POTENTIAL_TYPE" );
     double param_A = this->settings->get ( "PARAM_A" );
     double param_B = this->settings->get ( "PARAM_B" );
     double param_C = this->settings->get ( "PARAM_C" );
     double param_A0 = this->settings->get ( "PARAM_A0" );

     switch ( potentialType ) {
     case 2:
          //modulated potential
          this->potential = new ModulatedPotential2D ( param_A,param_B, param_C,param_A0, this->settings->getFrequency() );
          break;
     case 1:
     default:
          this->potential = new NarrowPotential2D ( param_A,param_B, param_C,param_A0 );
          break;
     }


     this->measureTime = false;
     this->lastX = 0.0;

     this->rand->reset();
//      cout << this->potential->toString() <<endl;

}




void Simulation::run ( Datafile *df )
{

     this->reset();

     double dt = this->settings->getDt();
     long double t = this->settings->getStartTime(); //t0


     double alpha = this->settings->getJumpsParameter();
     double dL = exp ( log ( dt ) /alpha );

     double D = this->settings->getNoiseIntensity();
     double sigma = exp( log(2.0* D)/alpha );
     
     
     
     int noiseType = settings->get ( "NOISE_TYPE" );


     point current_point;
     current_point.x = this->settings->getX0();
     current_point.y = this->settings->getY0();


     double max_time = this->settings->get ( "max_time" );


     //thresholds to switch to analytic solution
     double x_an_tr = abs ( this->settings->get ( "ANALYTIC_THRESHOLD_X" ) );
     double y_an_tr = abs ( this->settings->get ( "ANALYTIC_THRESHOLD_Y" ) );

     // hard limit to prevent escape to infinity
     double x_limit = abs ( this->settings->get ( "VAL_X_LIMIT" ) );
     double y_limit = abs ( this->settings->get ( "VAL_Y_LIMIT" ) );


     double saveTfromTime = this->settings->get ( "save_traj_from_time" );




     while ( t <= max_time ) {

          // save only if t >= defined time point
          if ( t >= saveTfromTime ) {
               df->write ( current_point.x );
               df->write ( current_point.y );
          }

//        cout << "t="<<t<<endl;
          double * v ;


          switch ( noiseType ) {
          case 1:
               v = rand->getAlphaStableVector ( alpha);
               break;
          case 2:
          default:
               v = rand->getDicreteAlphaStableVector ( alpha, sigma );
               break;
          }


          // ====================================
          // X value

          if ( abs ( current_point.x ) > x_an_tr ) {
               // above threshold, switch to analytical solution (approx)
	       //cout << "t = "<< t << " x = " << current_point.x << " => ";
               current_point.x = this->potential->getXanalytic ( current_point.x, current_point.y, t,  dt ) + sigma * v[0]*dL;
	       
	       //cout <<  current_point.x << endl;
          } else {
               // below threshold, do numerical integration
               double forcex = - ( this->potential->getXderiv ( current_point.x, current_point.y, t  ) );
               current_point.x += forcex*dt  + sigma * v[0]*dL;
	       
// 	       cout << "t = "<< t << " x = " << current_point.x << " \t numerical x" << endl;
          }

          // hard boundaries
          if ( current_point.x < -x_limit ) current_point.x = -x_limit;
          else if ( current_point.x > x_limit ) current_point.x = x_limit;


          // ====================================
          // Y value

          if ( abs ( current_point.y ) > y_an_tr ) {
               // above threshold, switch to analytical solution (approx)
               current_point.y = this->potential->getYanalytic ( current_point.x, current_point.y, t, dt ) + sigma * v[1]*dL;

          } else {
               // below threshold, do numerical integration
               double forcey = - ( this->potential->getYderiv ( current_point.x, current_point.y, t ) );
               current_point.y += forcey*dt  + sigma * v[1]*dL;
          }

          // hard boundaries
          if ( current_point.y < -y_limit ) current_point.y = -y_limit;
          else if ( current_point.y > y_limit ) current_point.y = y_limit;

          //===================================================

          // remember to delete vector
          delete[] v;
          t+= dt;
     }

}



double Simulation::dotProduct ( const vec & v1, const vec & v2 )
{
     return v1.x*v2.x + v1.y*v2.y;

}


double Simulation::getDistance ( const point & p1, const point & p2 )
{
     return sqrt ( pow ( p2.x-p1.x,2.0 ) + pow ( p2.y-p1.y,2.0 ) );
}



void Simulation::norm ( vec & v )
{
     double d = sqrt ( pow ( v.x,2.0 ) + pow ( v.y,2.0 ) );
     v.x = v.x/d;
     v.y = v.y/d;
}


bool Simulation::stateChanged ( double& x )
{
     return ( x > 0.0 && lastX < 0.0 ) || ( x < 0.0 && lastX > 0.0 );
}


