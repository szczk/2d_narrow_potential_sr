#include "main.hh"



// tmp: /mnt/lustre/scratch/people/ufszczep/";
// storage: /storage/ufszczep/
char filePrefix[200] = "";

int main ( int argc, char **argv )
{
     cout << endl << endl;

     System& sys = System::getInstance();
     sys.start();

     sys.printInfo();

     Settings& settings = Settings:: getInstance ( "settings.dat" );
     settings.readCommandLineParameters ( argc,argv );
     settings.printParameters();


     double num = settings.getNtrajectories();
     int tenPerc = ( num>10 ) ? ( int ) ( num*0.1 ) : 1;

     double alpha = settings.getJumpsParameter();



     cout << "entering loop"<<endl;

     Simulation * sim = new Simulation ( &settings );


     char buffer[200];
     sprintf ( buffer,"%s/%s_mean_escape_time.txt", settings.getStoragePath(), settings.getFullOutputFilesPrefix().c_str() );

     ofstream output ( buffer );

     
     for ( int i =0; i < num ; i++ ) {
          if ( i%tenPerc==0 ) {
               cout << i<<"/"<<num<<endl;
          }
          sim->run ( );
     }

     RunningStat * meanEscape = sim->getMeanEscapeTime();
     double meanEscapeTime = meanEscape->Mean();
     int count = meanEscape->NumDataValues();
     meanEscape->Clear();

     output << alpha << "\t" << meanEscapeTime << "\t" << count << "\n" << flush;



     output.close();

     delete sim;

     sys.finish();
     sys.printTimeSummary();

     return 0;
}


