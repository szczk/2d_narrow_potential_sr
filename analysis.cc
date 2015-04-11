#include "main.hh"

#include <cstdlib>
#include <cmath>
#include <sys/stat.h>
#include "tools/Datafile.hh"
#include "analysis/Analysis.hh"

int main ( int argc , char ** argv )
{

     cout << endl << endl;

     System& sys = System::getInstance();
     sys.start();


     Settings& settings = Settings:: getInstance ( );

     // override parameters from command line
     settings.readCommandLineParameters ( argc,argv );
     settings.printParameters();


     // analysis
     Analysis * analysis = new Analysis ( &settings );

     double ntrajectories = settings.getNtrajectories();
     int tenPerc = ( ntrajectories>10 ) ? ( int ) ( ntrajectories*0.1 ) : 1;
     cout << "opening trajectories files"<<endl;

     if ( settings.multipleOutputs() ) {
          int maxNum = settings.getMultipleOutputFilenum();
          bool first = true;
          for ( int filenum = 1; filenum <= maxNum ; filenum++ ) {
               for ( int nt =0; nt < ntrajectories ; nt++ ) {
                    if ( nt%tenPerc==0 ) {
                         cout << nt<<"/"<<ntrajectories<<endl;
                    }
                    string outputFile = settings.getMultiDatafileName ( settings.getDataPath(), filenum,  nt );
                    cout << "opening " << outputFile << "...";

                    Datafile * datafile = Datafile::open ( outputFile.c_str() );
                    if ( datafile->ok() ) {
                         cout << "ok"<<endl;
                         analysis->fillFromFile ( datafile );
                    }
                    delete datafile;
               }
          }
     } else {
          for ( int nt =0; nt < ntrajectories ; nt++ ) {

               if ( nt%tenPerc==0 ) {
                    cout << nt<<"/"<<ntrajectories<<endl;
               }

               string outputFile = settings.getDatafileName ( settings.getDataPath(), nt );
               cout << "opening " << outputFile << endl;
               Datafile * datafile = Datafile::open ( outputFile.c_str() );
               if ( datafile->ok() ) {
                    analysis->fillFromFile ( datafile );
               } else {
                    delete datafile;
               }
          }
     }


     analysis->calculate();

     analysis->save();

     analysis->close();
     delete analysis;


     sys.finish();
     sys.printTimeSummary();


     return 0;
}

