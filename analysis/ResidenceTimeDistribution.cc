#include "ResidenceTimeDistribution.hh"

ResidenceTimeDistribution::ResidenceTimeDistribution ( Settings * s ) : settings ( s ), p_left ( nullptr ), p_right ( nullptr ), p_total ( nullptr )
{

     nBins = 100;
     tMin = 0.0;
     tMax = 1.0;

     //


     this->init();
}



ResidenceTimeDistribution::~ResidenceTimeDistribution()
{
     this->cleanUp();
}



void ResidenceTimeDistribution::init()
{
     this->tMin = this->settings->get ( "RTD_MIN" );
     this->tMax = this->settings->get ( "RTD_MAX" );
     this->nBins = this->settings->get ( "RTD_NBINS" );

     this->x0 = this->settings->getX0();
     this->stateThresholdAbs = this->settings->get ( "STATE_THRESHOLD_ABS" );
     this->numberOfTransitions = 0;
     this->period = 1.0/this->settings->getFrequency();
     this->dt = this->settings->getDt();

     this->p_left = this->initHisto ( this->p_left );
     this->p_right = this->initHisto ( this->p_right );
     this->p_total = this->initHisto ( this->p_total );

     if ( this->p_left==nullptr ) {
          cout << " p_left null again!"<<endl;
     }


     this->statesBorderX = 0.0;
     this->residenceTimeStart = 0.0;
     this->state = 1.0;

     this->periodStartTime = 0.0;
     this->number_of_transitions_per_period = new map<int,int*>();
}


void ResidenceTimeDistribution::cleanUp()
{
     cout << "deleting ResidenceTimeDistribution"<<endl;
     this->deleteHisto ( this->p_left );
     this->deleteHisto ( this->p_right );
     this->deleteHisto ( this->p_total );

     cout << "deleting map"<<endl;
     if(number_of_transitions_per_period!=nullptr) {
       
      for ( auto it = number_of_transitions_per_period->begin(); it!= number_of_transitions_per_period->end(); ++it ) {
               int * elem = ( it->second );
               delete elem;
          } 
       delete this->number_of_transitions_per_period;
     }
}


gsl_histogram* ResidenceTimeDistribution::initHisto ( gsl_histogram*  h )
{
     if ( h==nullptr ) {
          h = gsl_histogram_alloc ( this->nBins );
          gsl_histogram_set_ranges_uniform ( h, this->tMin, this->tMax );
          return h;
     } else {
          cout << " not null histogram pointer passed!"<<endl;
          return h;
     }
}

void ResidenceTimeDistribution::deleteHisto ( gsl_histogram* h )
{
     if ( h!=nullptr ) {
          gsl_histogram_free ( h );
     } else {
          cout << "null histogram passed"<<endl;
     }
}


void ResidenceTimeDistribution::save()
{
     cout << "saving residence time distributions" <<endl;
     this->saveHisto ( this->p_left, "left" );
     this->saveHisto ( this->p_right, "right" );
     this->saveHisto ( this->p_total, "total" );
     
     this->saveTransitionsPerPeriod();
}


void ResidenceTimeDistribution::saveHisto ( gsl_histogram * histogram, const char * variable )
{
     if ( histogram==nullptr ) {
          cout << "NULL HISTOGRAM!!!"<<endl;
          return;
     }


     char datafileName[200];
     char dataFullPath[200];
     char datafileNamePlot[200];

     sprintf ( datafileName,"%s_residence_time_distr_%s.txt", this->settings->getFullOutputFilesPrefix().c_str() , variable );
     sprintf ( dataFullPath,"%s/%s", this->settings->getStoragePath() , datafileName );
     sprintf ( datafileNamePlot,"%s/%s_residence_time_distr_%s.plt",this->settings->getStoragePath(), this->settings->getFullOutputFilesPrefix().c_str() , variable );




     ofstream plotScript ( datafileNamePlot ,ios_base::out );

     plotScript << "reset\n";
//      plotScript << "set term png enhanced \n";

     plotScript << "set title '{/Symbol a} = " << this->settings->getJumpsParameter();
     plotScript << " D = " << this->settings->getNoiseIntensity();
     plotScript << "'\n";

     plotScript << "set terminal post eps size 12,7 enhanced color font 'Helvetica,35' linewidth 2;\n";
     plotScript << "set output \""<< this->settings->getFullOutputFilesPrefix() << "_residence_time_distr_"<< variable <<".eps\"\n";

     plotScript << "set xrange ["<< this->tMin <<":"<< this->tMax << "]\n";
//      plotScript << "set yrange [0:1]\n";

     plotScript << "set xlabel 't_{"<< variable << "}/T_{(/Symbol O)}'\n";
     plotScript << "set ylabel 'P(t_{"<< variable << "}/T_{(/Symbol O)})'\n";


     double dt = ( tMax-tMin ) / this->nBins;
     cout << "dt = " << dt << endl;
     double scale = 1.0/ ( gsl_histogram_sum ( histogram ) );
     cout << "scale: "<< scale << endl;
     gsl_histogram_scale ( histogram,  scale );



     FILE * pFile = fopen ( dataFullPath,"w" );

     gsl_histogram_fprintf ( pFile,  histogram, "%g", "%g" );

     fclose ( pFile );


     plotScript<< "plot '"<<datafileName <<"' using ($1+ ($2-$1)/2):3 with linespoints title 'p(t_{"<< variable << "})' lc rgbcolor 'red' lw 2\n";


     plotScript.close();


}


void ResidenceTimeDistribution::saveTransitionsPerPeriod()
{


     char datafileName[200];
     char dataFullPath[200];
//      char datafileNamePlot[200];
     int max_transitions_to_save = 5; //from 0 to max_transitions_to_save inclusive
     
     sprintf ( datafileName,"%s_transitions_per_period.txt", this->settings->getFullOutputFilesPrefix().c_str()  );
     sprintf ( dataFullPath,"%s/%s", this->settings->getStoragePath() , datafileName );
     ofstream output ( dataFullPath );
     
     output << "# alpha\tnoise_intensity";
     for( int t = 0; t < max_transitions_to_save; t++){
       output <<"\tp_" << t ;
     }
     
     output << "\t\t # P_n = probability of n transitions per period\n";
     output << this->settings->getJumpsParameter() << "\t" <<  this->settings->getNoiseIntensity() ;
	  
     cout << " saving transitions per period "<< endl;


     double norm = 0.0;
     //calculate norm
     for ( auto it=number_of_transitions_per_period->begin(); it!=number_of_transitions_per_period->end(); ++it) {
       int i =  (it->first);
       int c =  *(it->second);
       cout << " norm = " << norm << ", c("<<i<<") = " << c << endl;
       norm += c;
       
     }
     
     cout << " norm = " << norm << endl;
     
     for( int transitions = 0; transitions < max_transitions_to_save; transitions++){
       double prob = 0.0;
       if( this->number_of_transitions_per_period->find(transitions) != this->number_of_transitions_per_period->end() ) {
	 
	 prob = (  (*(this->number_of_transitions_per_period->at(transitions)))/norm );
	 cout << "p(transitions) = "<< (*(this->number_of_transitions_per_period->at(transitions))) << "/" << norm << " = " <<  prob << endl;
       }
      
       output << "\t" << prob;
       
     }
     
     output << "\n";
//      for ( auto it=number_of_transitions_per_period->begin(); it!=number_of_transitions_per_period->end(); ++it) {
//        std::cout << it->first << " => " << *(it->second) << " (" << (*(it->second))/norm  <<")\n";
//      }




     output.close();

}




void ResidenceTimeDistribution::fill ( double t, double x, double y )
{

     if ( t==0.0 ) {
          //reset

          residenceTimeStart = 0.0;
          state = (this->x0 > 0.0) ? 1.0 : -1.0;
          this->numberOfTransitions = 0;

          this->periodStartTime = t;

//     cout << "new traj"<<endl;
     } else {



          if ( ( x * state < 0.0 ) && ( abs ( x ) > this->stateThresholdAbs ) ) {
               //state changed
	       state = (-1.0)*state;
               double residenceTime = t - residenceTimeStart;

//        cout << " state changed, old pos:" << state << " new pos: " << x << " residenceTime = " << residenceTime <<endl;
               if ( x > statesBorderX ) {
                    // now is in right, so was in left
                    gsl_histogram_increment ( this->p_left ,  residenceTime/period );
               } else if ( x < statesBorderX ) {
                    //now is in left so was in right
                    gsl_histogram_increment ( this->p_right ,  residenceTime/period );
               }

               //save summarized also
               gsl_histogram_increment ( this->p_total ,  residenceTime/period );

               residenceTimeStart = t;

               ++ ( this->numberOfTransitions );
          } else {
               // state not changed
          }


          


     }

     //detect new force period
     if ( t + dt > ( periodStartTime + period ) ) {
          //new period!
//            cout << "new period! t = " << t << " periodStartTime = " << periodStartTime << " period = " << period << endl;
          periodStartTime = t;

//            cout << "liczba przejsc w okresie: " << numberOfTransitions << endl;

          if ( this->number_of_transitions_per_period->find ( numberOfTransitions ) == this->number_of_transitions_per_period->end() ) {
               this->number_of_transitions_per_period->operator[] ( numberOfTransitions ) = new int(1);
          } else {
               (*( this->number_of_transitions_per_period->operator[] ( numberOfTransitions ) )) ++;
          }

          numberOfTransitions = 0;
     }
}

