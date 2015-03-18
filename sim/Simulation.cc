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
     double param_A = this->settings->get("PARAM_A");
     double param_B = this->settings->get("PARAM_B");
     double param_C = this->settings->get("PARAM_C");
     double param_A0 = this->settings->get("PARAM_A0");
     
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

//      bool dump_gnuplot = false;

     double dt = this->settings->getDt();
     long double t = this->settings->getStartTime(); //t0


     double alpha = this->settings->getJumpsParameter();
     double dL = exp ( log ( dt ) /alpha );

     double sigma = this->settings->getNoiseIntensity();
     int noiseType = settings->get ( "NOISE_TYPE" );

//   double endTime = 10.0;


     point current_point;

     current_point.x = this->settings->getX0();
     current_point.y = this->settings->getY0();


     double max_time = this->settings->get ( "max_time" );

     
     
     double x_limit = abs(this->settings->get( "VAL_X_LIMIT"));
     double y_limit = abs(this->settings->get( "VAL_Y_LIMIT"));
     
     
     double saveTfromTime = this->settings->get( "save_traj_from_time");
     
//      double timeInState = 0.0;
//      bool fileOkToSave = false;
//      if ( this->dataFile!=nullptr ) {
//           fileOkToSave = this->dataFile->ok();
//      }

     while ( t <= max_time ) {

       // save only if t >= defined time point 
	  if( t >= saveTfromTime ) {
          df->write(current_point.x);
          df->write(current_point.y);
	  }
         
//        cout << "t="<<t<<endl;
          double * v ;


          switch ( noiseType ) {
          case 1:
               v = rand->getAlphaStableVector ( alpha, sigma );
               break;
          case 2:
          default:
               v = rand->getDicreteAlphaStableVector ( alpha, sigma );
               break;
          }


          // grad V(x,y)
          vec potential = ( * ( this->potential ) ) ( current_point.x, current_point.y, t );

//           cout << "v[0] = " << v[0] << "\tv[1] = " << v[1] <<endl;

	  //cout << " t= " << t <<"\t";
	  //cout << "x,y = " << current_point.x << ","<<current_point.y<<"\t v[0] = " << v[0] << "\t v[1]=" << v[1] <<"\t"; 
	  //cout <<" V_x = " << potential.x << " \t V_y = " << potential.y << endl;
	  
          current_point.x += -potential.x*dt  + v[0]*dL;
          current_point.y += -potential.y*dt  + v[1]*dL;

	  
	  
	  
          delete[] v;
          t+= dt;

          
          bool overX = false;
          //constraints
          if( current_point.x < -x_limit) {
	    current_point.x = -x_limit;
	    overX = true; 
	  }
          else if (current_point.x > x_limit) { 
	    current_point.x = x_limit;
	    overX = true;
	  }

          if( current_point.y < -y_limit) current_point.y = -y_limit;
          else if (current_point.y > y_limit) current_point.y = y_limit;
          
          
          if(overX) {
	    
	    cout << "------------" << endl;
	    cout << " t= " << t <<"\t";
	   cout << "over limit!"<<"\t" << "x,y = " << current_point.x << ","<<current_point.y<<"\t v[0] = " << v[0] << "\t v[1]=" << v[1] <<endl; 
	   cout <<" V_x = " << potential.x << " << \t V_y = " << potential.y << endl;
	   exit(0);
	    
	  }
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


