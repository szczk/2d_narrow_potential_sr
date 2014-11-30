#include "main.hh"

#include <cstdlib>
#include <cmath>
#include <sys/stat.h>
#include "tools/Datafile.hh"


int main ( int argc , char ** argv )
{

     cout << endl << endl;

     System& sys = System::getInstance();
     sys.start();


     Settings& settings = Settings:: getInstance ( );

     // override parameters from command line
     settings.readCommandLineParameters ( argc,argv );

     settings.printParameters();
     settings.dumpToFile ( "params.txt" );

     double alpha = settings.getJumpsParameter();


     cout << "entering loop"<<endl;





     

     

     sys.finish();
     sys.printTimeSummary();


     return 0;
}

