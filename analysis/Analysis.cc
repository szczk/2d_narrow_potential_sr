#include "Analysis.hh"



Analysis::Analysis ( Settings*s ) : settings ( s ),  calculated ( false )
{


     this->initAnalysis();
}

Analysis:: ~Analysis()
{
}



void Analysis::save()
{
     if ( !calculated ) {
          cout << "Analysis::calculate() not called!"<<endl;
          return;
     }

     cout << "Analysis::save()"<<endl;



     // do save
//      if ( this->meanR!=nullptr ) {
//           cout << "saving meanR"<<endl;
// 
//           this->saveMeanRTestResults();
//      }
// 
// 
//      if ( this->marginalDistributions!=nullptr ) {
// 
//           cout << "saving marginalDistributions"<<endl;
// 
// //           double deltaT = this->settings->get ( "KSTEST_DELTA_T" ); //time interval between two distibutions
// 
// 
//           this->saveKolmogorovTestResults ( 0.02 );
//           this->saveKolmogorovTestResults ( 0.04 );
//           this->saveKolmogorovTestResults ( 0.06 );
//           this->saveKolmogorovTestResults ( 0.08 );
//           this->saveKolmogorovTestResults ( 0.1 );
//           this->saveKolmogorovTestResults ( 0.15 );
//           this->saveKolmogorovTestResults ( 0.2 );
//           this->saveKolmogorovTestResults ( 0.3 );
//      }



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
          double maxT = settings->get ( "maxT" );
          double dt = settings->get ( "dt" );
          double starttime = settings->get ( "starttime" );
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

//      auto amr = this->meanR->find ( t );
//      auto amg = this->marginalDistributions->find ( t );
// 
//      auto mrEnd = this->meanR->end();
//      auto mgEnd = this->marginalDistributions->end();
// 
// 
//      MeanRsquared * mr ;
//      MarginalDistributions * marginalDistr;
// 
//      if ( amr==mrEnd ) {
//           mr = new MeanRsquared();
//           this->meanR->insert ( std::make_pair ( t, mr ) );
//      } else {
//           mr = amr->second;
//      }
// 
//      if ( amg==mgEnd ) {
//           marginalDistr = new MarginalDistributions ( t );
//           this->marginalDistributions->insert ( std::make_pair ( t, marginalDistr ) );
//      } else {
//           marginalDistr = amg->second;
//      }
// 
// 
//      mr->add ( x,y );
//      marginalDistr->add ( x,y );
// 
//      
//      
//      if(false) {
//          
//         auto ahp = this->histogramProducers->find ( t );
//         auto aedf = this->edfProducers->find ( t );
// 
//         auto hpEnd = this->histogramProducers->end();
//         auto edfEnd = this->edfProducers->end(); 
//          
//         
//         
//         HistogramsProducer * producer ;
//         EDFProducer * edfProducer;
// 
//         if( ahp == hpEnd) {
//             cout << " new HP for t= " << t <<endl;
//             producer = new HistogramsProducer ( settings );
//             producer->setTime ( t );
//             this->histogramProducers->insert( std::make_pair(t, producer) ) ;
//         } else {
//             producer = ahp->second;
//         }
//         
//         if( aedf == edfEnd ) {
//             edfProducer = new EDFProducer ( settings );
//             edfProducer->setTime ( t );
//             this->edfProducers->insert( std::make_pair(t,edfProducer));
//         } else {
//             edfProducer = aedf->second;
//         }
// 
//         
//         producer->fill(x,y);
//         edfProducer->fill(x,y);
// 
//      }
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
     
     
     
     
//      histogramProducers = new map<double, HistogramsProducer *>(); ;
//      edfProducers = new map<double, EDFProducer *>();
          
     
}

void Analysis::deleteAnalysis()
{
//      if ( this->meanR!=nullptr ) {
//           cout << "deleting meanR"<<endl;
// 
//           for ( auto it = meanR->begin(); it!= meanR->end(); ++it ) {
//                MeanRsquared * mr = ( it->second );
// 
//                //cout << "t = " << it->first  << "\t < r^2 >  = " << mr->getMeanValue() <<endl;
//                delete mr;
//           }
// 
//           delete this->meanR;
//           this->meanR = nullptr;
//      }
// 
//      if ( this->marginalDistributions!=nullptr ) {
//           cout << "deleting marginalDistributions"<<endl;
//           for ( auto it = marginalDistributions->begin(); it!= marginalDistributions->end(); ++it ) {
//                MarginalDistributions * distributions = ( it->second );
// 
//                // cout << "t = " << meanR->getT() << "\t < r^2 >  = " << meanR->getMeanValue() <<endl;
// 
//                //test << meanR->getT() << "\t" << meanR->getMeanValue() << endl;
// 
//                delete distributions;
//           }
//           delete marginalDistributions;
//      }
//      
//      
//      
//      if( histogramProducers!=nullptr) {
//      for(auto it = this->histogramProducers->begin(); it!=histogramProducers->end(); ++it) {
//        HistogramsProducer * hp = ( it->second );
//        hp->close();
//        delete hp;
//      }
//      cout << "delete histogramProducers"<<endl;
//      delete histogramProducers;
//      
//      }
//      
//      if( edfProducers!=nullptr) {
//          
//       for(auto it = this->edfProducers->begin(); it!=edfProducers->end(); ++it) {
//        EDFProducer * hp = ( it->second );
//        hp->close();
//        delete hp;
//      }
//      cout << "delete edfProducers"<<endl;
//      delete edfProducers;
//      
//      }
     
     cout << "all deleted"<<endl;
}



// void Analysis::saveKolmogorovTestResults ( double deltaT )
// {
// 
//      char datafileNameX[200];
//      char datafileNameY[200];
// 
//      char dataFullPathX[200];
//      char dataFullPathY[200];
// 
//      char datafileNameXplot[200];
//      char datafileNameYplot[200];
// 
//      double dt = this->settings->getDt();
// 
//      if ( deltaT< dt ) {
//           deltaT= 0.02;
//           cout << "deltaT not set in settings, defaulting to " << deltaT <<endl;
//      }
// 
//      double deltaN = deltaT/dt;
//      cout << " DELTA_T = " << deltaT << "\t delta N = " << deltaN << endl;
// 
// //        cout << "storagepath="  << storagePath <<endl;
// //        cout << "filePrefix="<< filePrefix <<endl;
// 
//      sprintf ( datafileNameX,"%s_KStest_X_deltaT_%2.3f.txt", this->settings->getFullOutputFilesPrefix().c_str(), deltaT );
//      sprintf ( dataFullPathX,"%s/%s",this->settings->getStoragePath(), datafileNameX );
//      ofstream ksXout ( dataFullPathX );
// 
//      sprintf ( datafileNameXplot,"%s/%s_KStest_X_deltaT_%2.3f.plt",this->settings->getStoragePath(), this->settings->getFullOutputFilesPrefix().c_str(), deltaT );
//      ofstream ksXplt ( datafileNameXplot );
// 
// 
//      cout << "datafileNameX:" << datafileNameX<<"\n ksXout:" << dataFullPathX << "\nksXplt:"<< datafileNameXplot << endl;
// 
// 
//      ksXplt << "reset\n";
// 
//      ksXplt << "set title ' marg. distr. X  {/Symbol a} = " << this->settings->getJumpsParameter();
//      ksXplt << " {/Symbol b} = " << this->settings->getWaitingTimesParameter();
//      ksXplt << " {/Symbol D}t = " << deltaT << "'\n";
// 
//      ksXplt << "set terminal post eps size 12,7 enhanced color font 'Helvetica,35' linewidth 2;\n";
//      ksXplt << "set output \""<< this->settings->getFullOutputFilesPrefix() << "_KStest_X_deltaT_"<< deltaT <<".eps\"\n";
// 
//      ksXplt << "set xlabel \"t\"\n";
//      ksXplt << "set ylabel \"K-S D\"\n";
// 
//      ksXplt << "plot './"<< datafileNameX <<"' using 1:2 w lp notitle\n";
// 
// 
// //          cout << "storagepath="  << storagePath <<endl;
// //          cout << "filePrefix="<< filePrefix <<endl;
//      sprintf ( datafileNameY,"%s_KStest_Y_deltaT_%2.3f.txt", this->settings->getFullOutputFilesPrefix().c_str(), deltaT );
//      sprintf ( dataFullPathY,"%s/%s",this->settings->getStoragePath(), datafileNameY );
//      ofstream ksYout ( dataFullPathY );
// 
//      sprintf ( datafileNameYplot,"%s/%s_KStest_Y_deltaT_%2.3f.plt",this->settings->getStoragePath(), this->settings->getFullOutputFilesPrefix().c_str(), deltaT );
//      ofstream ksYplt ( datafileNameYplot );
// 
//      cout << "datafileNameY:" << datafileNameY<<"\n ksYout:" << dataFullPathY << "\nksYplt:"<< datafileNameYplot << endl;
// 
// 
//      ksYplt << "reset\n";
// 
//      ksYplt << "set title ' marg. distr. Y  {/Symbol a} = " << this->settings->getJumpsParameter();
//      ksYplt << " {/Symbol b} = " << this->settings->getWaitingTimesParameter();
//      ksYplt << " {/Symbol D}t = " << deltaT << "'\n";
// 
//      ksYplt << "set terminal post eps size 12,7 enhanced color font 'Helvetica,35' linewidth 2;\n";
//      ksYplt << "set output \""<< this->settings->getFullOutputFilesPrefix() << "_KStest_Y_deltaT_"<< deltaT <<".eps\"\n";
// 
//      ksYplt << "set xlabel \"t\"\n";
//      ksYplt << "set ylabel \"K-S D\"\n";
// 
//      ksYplt << "plot './"<< datafileNameY <<"' using 1:2 w lp notitle\n";
// 
// 
// 
// 
// 
// 
// 
// 
//      ksXout <<"# t \t K-S test D (marginal X distr, delta T = " << deltaT<<")\n";
//      ksYout <<"# t \t K-S test D (marginal Y distr, delta T = " << deltaT<<")\n";
// 
//      int size = this->marginalDistributions->size() - deltaN;
// 
// 
//      //get the vector of keys from map
//      // this is done because simply calculating new double may not match the map keys (due to double being floating point)
//      // but if we get keys directly from map and use vector index it will always work
//      vector<double>* keys = new vector<double>();
//      for ( auto it = this->marginalDistributions->begin(); it != marginalDistributions->end(); ++it ) {
//           keys->push_back ( ( it )->first );
//      }
// 
// 
// 
//      for ( int c = 0; c < size ; c++ ) {
// 
//           double keyT = keys->at ( c );
//           MarginalDistributions * distributions = this->marginalDistributions->at ( keyT );
// 
//           double t = distributions->getT();
// 
// //           double secondT = t + deltaT;
//           double keySecondT = keys->at ( c + deltaN );
//           //bool secondTexists = ( this->marginalDistributions->count( secondT) == 1 );
//           MarginalDistributions * secondDist = this->marginalDistributions->at ( keySecondT );
// 
// //        double secondT = secondDist->getT();
// //        cout << "t = " << t << "\t second t  = " << secondT ;
// 
//           //test << meanR->getT() << "\t" << meanR->getMeanValue() << endl;
// 
//           double KStestX = KolmogorovTest::calculate ( distributions->getXedf(), secondDist->getXedf() );
//           double KStestY = KolmogorovTest::calculate ( distributions->getYedf(), secondDist->getYedf() );
// 
//           ksXout << t <<"\t" << KStestX <<"\n";
//           ksYout << t <<"\t" << KStestY <<"\n";
//      }
// 
//      delete keys;
// 
// 
//      ksXout.close();
//      ksYout.close();
// 
//      ksXplt.close();
//      ksYplt.close();
// }
// 
// 
// 
// void Analysis::saveMeanRTestResults()
// {
// 
//      char datafileName[200];
//      char dataFullPath[200];
//      char datafileNamePlot[200];
// 
// 
// 
//      sprintf ( datafileName,"%s_mean_r_squared.txt", this->settings->getFullOutputFilesPrefix().c_str() );
//      sprintf ( dataFullPath,"%s/%s", this->settings->getStoragePath() , datafileName );
//      ofstream output ( dataFullPath );
//      output << "# t\t<x^2 + y^2>\n";
// 
// 
//      sprintf ( datafileNamePlot,"%s/%s_mean_r_squared.plt",this->settings->getStoragePath(), this->settings->getFullOutputFilesPrefix().c_str() );
//      ofstream meanRplt ( datafileNamePlot );
// 
// 
//      meanRplt << "reset\n";
// 
//      meanRplt << "set title ' <r^2>  {/Symbol a} = " << this->settings->getJumpsParameter();
//      meanRplt << " {/Symbol b} = " << this->settings->getWaitingTimesParameter();
//      meanRplt << "'\n";
// 
//      meanRplt << "set terminal post eps size 12,7 enhanced color font 'Helvetica,35' linewidth 2;\n";
//      meanRplt << "set output \""<< this->settings->getFullOutputFilesPrefix() << "_mean_r_squared.eps\"\n";
// 
//      meanRplt << "set xlabel \"t\"\n";
//      meanRplt << "set ylabel \"<r^2>\"\n";
// 
//      meanRplt << "plot './"<< datafileName <<"' using 1:2 w lp notitle\n";
//      meanRplt.close();
// 
//      //calculate derivative at the same time 
//      
//      // f'(x) = (f(x-h) + f(x+h))/(2h) 
//      // backward derivative
//      // f'(x) = (f(x) - f(x-h))/(h) 
//      
//      //double previousValue = 0.0;
//      //double h = this->settings->getDt();
//      
//      double previousValue = 0.0;
//      
//      size_t meanRs = meanR->size();
//      int fitCount = meanRs > 50 ? 50 : meanRs;
//      double x[fitCount], y[fitCount];
//      
//      int ind = 0;
//      int c = 0;
//      for ( auto it = meanR->begin(); it!= meanR->end(); ++it ) {
//          
//           double t = it->first;
//           MeanRsquared * mr = ( it->second );
// //                cout << "t = " << it->first  << "\t < r^2 >  = " << mr->getMeanValue() <<endl;
// 	  double mean = mr->getMeanValue();
// 	  
// 	  //double deriv = (mean - previousValue)/h;
// 	  
// 	  // skip extreme values
// 	  //if( mean < 2.0* previousValue) {
//           output << it->first << "\t" << mean << "\t" << "\n";
// 	  //}
// 	  
// 	  
// 	  if( c > meanRs - fitCount) {
//           y[ind] = mean;
//           x[ind] = t;
//           
//           ind++;
//       }
// 	  
// 	  
// 	  
// 	  previousValue = mean;
//       ++c;
//      }
//     // output.flush();
//      output.close();
// 
//      
//      double c0, c1;
//      int code = Utility::linearRegression(  x, y, fitCount-1, &c0, &c1 );
// 
//      
//      cout << " fit code: " << code << endl;
//      cout << " c0: " << c0 << "\tc1:" << c1<<endl;
//      cout << "x[0] = " << x[0] << "\t x[count-2] = " << x[fitCount-2] << "\t x[count-1] =" << x[fitCount-1] <<endl;
//      cout << "y[0] = " << y[0] << "\t y[count-2] = " << y[fitCount-2] << "\t y[count-1] =" << y[fitCount-1] <<endl;
//      
//      cout << "set arrow from "<<x[0]<<","<< (c1 * x[0] + c0)<< " to "<< x[fitCount-2]<<","<< (x[fitCount-2]* c1 + c0) <<" nohead lt 1 lw 3"<<endl;
// 
// }
