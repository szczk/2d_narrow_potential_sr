#include "Analysis.hh"



Analysis::Analysis ( Settings*s ) : settings ( s ), meanXs ( nullptr ), meanYs ( nullptr ), inLeftCounter ( nullptr ), inRightCounter ( nullptr ), rtd(nullptr),  calculated ( false )
{


     this->initAnalysis();
}

Analysis:: ~Analysis()
{
  cout << "delete Analysis"<<endl;
}



void Analysis::save()
{
     if ( !calculated ) {
          cout << "Analysis::calculate() not called!"<<endl;
          return;
     }

     cout << "Analysis::save()"<<endl;


     // do save
     this->saveMean ( this->meanXs, "X" );
     this->saveMean ( this->meanYs, "Y" );

     this->savePositions();
     
     this->rtd->save();

}


void Analysis::calculate()
{
     if ( calculated ) {
          return;
     }


     calculated = true;
}


void Analysis::fillFromFile ( Datafile* f )
{
     if ( f==nullptr ) {
          cout << "passed datafile is null!"<<endl;
          throw -1;
     }
     if ( f->ok() ) {

          // iterate over time
          double maxT = settings->get ( "max_time" );
          double dt = settings->get ( "dt" );
          double starttime = settings->get ( "starttime" );

// 	  cout << "maxt : " << maxT << "\t dt = " << dt << "\t start time = " << starttime << endl;
          for ( double t = starttime; t <= maxT;  t+=dt ) {
//           cout << " t = " << t << endl;
               double x = f->read();
               double y = f->read();
//           cout << "(" << x << ","<<y<<")"<<endl;
               this->fill ( t,x,y );
          }


     } else {
          cout << "passed datafile not ok!"<<endl;
     }
}


void Analysis::fill ( double t, double x, double y )
{
//    cout << "filling " <<endl;

     RunningStat * meanX  = this->get ( t, this->meanXs );
     RunningStat * meanY  = this->get ( t, this->meanYs );


     meanX->Push ( x );
     meanY->Push ( y );


     int * leftCount = this->get ( t, this->inLeftCounter );
     int * rightCount = this->get ( t, this->inRightCounter );

     if ( x > 0.0 ) {
          ++ ( *rightCount );
     }
     if ( x < 0.0 ) {
          ++ ( *leftCount );
     }

     
     
    
     
     this->rtd->fill(t, x,y);
}




void Analysis::close()
{
     cout << "Analysis::close()"<<endl;
     this->deleteAnalysis();
}


void Analysis::initAnalysis()
{
//      this->meanR = new map<double, MeanRsquared*>();
//      this->marginalDistributions = new map<double, MarginalDistributions*>();

     this->meanXs = init ( this->meanXs );
     this->meanYs = init ( this->meanYs );

     if ( this->meanXs==nullptr ) {
          cout << "null again!"<<endl;
     }


     this->inLeftCounter = init ( this->inLeftCounter );
     this->inRightCounter = init ( this->inRightCounter );


     this->rtd = new ResidenceTimeDistribution(this->settings);

}

void Analysis::deleteAnalysis()
{
     cout << "deleting " << endl;

     this->deleteMap(this->meanXs);
     this->deleteMap(this->meanYs);

     delete this->inLeftCounter;
     delete this->inRightCounter;
     
     delete this->rtd;
     
     

     cout << "all deleted"<<endl;
}




void Analysis::saveMean ( std::map< double, RunningStat* >* meanPos, const char * variable )
{
     if ( meanPos==nullptr ) {
          cout << "NULL MAP!!!"<<endl;
          return;
     }


     char datafileName[200];
     char dataFullPath[200];
     char datafileNamePlot[200];


     cout << " saving mean " << variable << endl;

     sprintf ( datafileName,"%s_mean_%s.txt", this->settings->getFullOutputFilesPrefix().c_str() , variable );
     sprintf ( dataFullPath,"%s/%s", this->settings->getStoragePath() , datafileName );
     ofstream output ( dataFullPath );
     output << "# t\t<"<< variable <<">\t<"<< variable <<">_err\tvar("<< variable <<")\n";


     sprintf ( datafileNamePlot,"%s/%s_mean_%s.plt",this->settings->getStoragePath(), this->settings->getFullOutputFilesPrefix().c_str() , variable );
     ofstream meanRplt ( datafileNamePlot );


     // plot mean
     meanRplt << "reset\n";
     meanRplt << "set title ' <"<< variable << ">  {/Symbol a} = " << this->settings->getJumpsParameter();
     meanRplt << " D = " << this->settings->getNoiseIntensity();
     meanRplt << "'\n";

     meanRplt << "set terminal post eps size 12,7 enhanced color font 'Helvetica,35' linewidth 2;\n";
     meanRplt << "set output \""<< this->settings->getFullOutputFilesPrefix() << "_mean_"<< variable <<".eps\"\n";

     meanRplt << "set xlabel \"t\"\n";
     meanRplt << "set ylabel \"<"<< variable << ">\"\n";

     meanRplt << "plot './"<< datafileName <<"' using 1:2 w lp notitle\n";

     // plot variance

     meanRplt << "reset\n";

     meanRplt << "set title ' var("<< variable << ")  {/Symbol a} = " << this->settings->getJumpsParameter();
     meanRplt << " {/Symbol b} = " << this->settings->getWaitingTimesParameter();
     meanRplt << "'\n";

     meanRplt << "set terminal post eps size 12,7 enhanced color font 'Helvetica,35' linewidth 2;\n";
     meanRplt << "set output \""<< this->settings->getFullOutputFilesPrefix() << "_var_"<< variable <<".eps\"\n";

     meanRplt << "set xlabel \"t\"\n";
     meanRplt << "set ylabel \"var("<< variable << ")\"\n";

     meanRplt << "plot './"<< datafileName <<"' using 1:4 w lp notitle\n";


     meanRplt.close();



//      double previousValue = 0.0;

//      size_t meanRs = meanPos->size();
//      int fitCount = meanRs > 50 ? 50 : meanRs;
//      double x[fitCount], y[fitCount];

     int se = this->settings->get ( "SAVE_EVERY" );
     int saveEvery = se;

     for ( auto it = meanPos->begin(); it!= meanPos->end(); ++it ) {

          if ( ( saveEvery-- ) >0 ) {
               continue;
          }
          saveEvery = se;

          double t = it->first;
          RunningStat * mr = ( it->second );
//                cout << "t = " << it->first  << "\t < r^2 >  = " << mr->getMeanValue() <<endl;
          double mean = mr->Mean();
          double variance = mr->Variance();
          double mean_err = mr->StandardDeviationOfMean();

          //double deriv = (mean - previousValue)/h;

          // skip extreme values
          //if( mean < 2.0* previousValue) {
          output << t << "\t" << mean << "\t" << mean_err << "\t" << variance<< "\n";
          //}

     }

     // output.flush();

     output.close();

}




void Analysis::savePositions()
{
     if ( this->inLeftCounter==nullptr || this->inRightCounter==nullptr ) {
          cout << "NULL MAP!!!"<<endl;
          return;
     }


     char datafileName[200];
     char dataFullPath[200];
     char datafileNamePlot[200];


     cout << " saving p(left) & p(right) " << endl;

     sprintf ( datafileName,"%s_position_distr.txt", this->settings->getFullOutputFilesPrefix().c_str() );
     sprintf ( dataFullPath,"%s/%s", this->settings->getStoragePath() , datafileName );
     ofstream output ( dataFullPath );
     output << "# t\tp(left)\tp(right)\t1-p(left)\n";


     sprintf ( datafileNamePlot,"%s/%s_position_distr.plt",this->settings->getStoragePath(), this->settings->getFullOutputFilesPrefix().c_str() );
     ofstream meanRplt ( datafileNamePlot );


     // plot mean
     meanRplt << "reset\n";
     meanRplt << "set title ' p(left) p(right)  {/Symbol a} = " << this->settings->getJumpsParameter();
     meanRplt << " D = " << this->settings->getNoiseIntensity();
     meanRplt << "'\n";

     meanRplt << "set terminal post eps size 12,7 enhanced color font 'Helvetica,35' linewidth 2;\n";
     meanRplt << "set output \""<< this->settings->getFullOutputFilesPrefix() << "_position_distr.eps\"\n";

     meanRplt << "set xlabel \"t\"\n";
     meanRplt << "set ylabel \"p\"\n";

     meanRplt << "plot './"<< datafileName <<"' using 1:2 w lp title 'p(left)',\\\n";
     meanRplt << "'./"<< datafileName <<"' using 1:3 w lp title 'p(right)'\n";
     //meanRplt << "'./"<< datafileName <<"' using 1:4 w lp title '1-p(left)'\n";

     meanRplt.close();



//      double previousValue = 0.0;

//      size_t meanRs = meanPos->size();
//      int fitCount = meanRs > 50 ? 50 : meanRs;
//      double x[fitCount], y[fitCount];

     int se = this->settings->get ( "ANALYSIS_SAVE_EVERY" );
     int saveEvery = se;


     size_t leftSize = this->inLeftCounter->size();
     size_t rightSize = this->inRightCounter->size();

     if ( leftSize!=rightSize ) {
          cout << "different sizes!!!!!!!"<<endl;
          return;
     }

     int totalParticlesLeft = * ( this->inLeftCounter->begin()->second );
     int totalParticlesRight = * ( this->inRightCounter->begin()->second );
     int totalParticles = totalParticlesLeft + totalParticlesRight;
     int count = this->settings->getNtrajectories();

     cout << "counts: from settings: " << count << " from map: " << totalParticles << endl;

     auto itRight = inRightCounter->begin();
     for ( auto itLeft = inLeftCounter->begin(); itLeft!= inLeftCounter->end(); ++itLeft, ++itRight ) {

          if ( ( saveEvery-- ) >0 ) {
               continue;
          }
          saveEvery = se;

          double t = itLeft->first;
          int leftCount = * ( itLeft->second );
          int rightCount = * ( itRight->second );

          double p_left = ( ( double ) leftCount/ ( ( double ) totalParticles ) );
          double p_right = ( ( double ) rightCount/ ( ( double ) totalParticles ) );

          output << t << "\t" << p_left << "\t" << p_right << "\t" << ( 1.0 - p_left ) << "\n";
     }

     // output.flush();

     output.close();

}



template <typename T> T* Analysis:: get ( double t, map< double,T* > * m )
{
     if ( m!=nullptr ) {
          auto p = m->find ( t );
          auto pEnd = m->end();
          T * mr ;
//         cout << "t = "<< t <<  ",get " << typeid(*mr).name() << endl;
          if ( p==pEnd ) {
//             cout << " new obj" << endl;
               mr = new T();
               m->insert ( std::make_pair ( t, mr ) );
          } else {
               mr = p->second;
//             cout << "retrieve"<<endl;
          }
          return mr;

     } else {
          cout << "null map passed!"<<endl;
          return nullptr;
     }

}

template <typename T> T*  Analysis::init ( T * map )
{

     if ( map!=nullptr ) {
          cout << " " << typeid ( T ).name() << " not null!" << endl;
          return map;
     } else {
          cout << "initializing  " << typeid ( T ).name()  << endl;
          return new T();
     }


}

template <typename T> void Analysis::deleteMap ( map<double, T*> * map )
{

     if ( map!=nullptr ) {
          cout << "deleting " << typeid ( *map ).name() << endl;
          for ( auto it = map->begin(); it!= map->end(); ++it ) {
               T * elem = ( it->second );
               delete elem;
          }
          delete map;
     }


}
