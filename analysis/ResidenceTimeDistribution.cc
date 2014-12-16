#include "ResidenceTimeDistribution.hh"

ResidenceTimeDistribution::ResidenceTimeDistribution(Settings * s) : settings(s), p_left ( nullptr ), p_right ( nullptr ), p_total ( nullptr )
{
    
   nBins = 100;
   tMin = 0.0;
   tMax = 1.0;
  
  // 
   statesBorderX = 0.0;
   residenceTimeStart = 0.0;
   lastPosition = 0.0;
  
   this->init();
}



ResidenceTimeDistribution::~ResidenceTimeDistribution()
{
     this->cleanUp();
}



void ResidenceTimeDistribution::init()
{ 
     this->tMin = this->settings->get("RTD_MIN");
     this->tMax = this->settings->get("RTD_MAX");
     this->nBins = this->settings->get("RTD_NBINS");
     
     
     
     
  
     this->p_left = this->initHisto ( this->p_left );
     this->p_right = this->initHisto ( this->p_right );
     this->p_total = this->initHisto ( this->p_total );

     if ( this->p_left==nullptr ) {
          cout << " p_left null again!"<<endl;
     }
}


void ResidenceTimeDistribution::cleanUp()
{
     cout << "deleting ResidenceTimeDistribution"<<endl;
     this->deleteHisto ( this->p_left );
     this->deleteHisto ( this->p_right );
     this->deleteHisto ( this->p_total );
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
}


void ResidenceTimeDistribution::saveHisto(gsl_histogram * histogram, const char * variable)
{
     if(histogram==nullptr) {
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

     plotScript << "set title ' p(t_{"<< variable << "})  {/Symbol a} = " << this->settings->getJumpsParameter();
     plotScript << " D = " << this->settings->getNoiseIntensity();
     plotScript << "'\n";

     plotScript << "set terminal post eps size 12,7 enhanced color font 'Helvetica,35' linewidth 2;\n";
     plotScript << "set output \""<< this->settings->getFullOutputFilesPrefix() << "_residence_time_distr_"<< variable <<".eps\"\n";

     plotScript << "set xrange ["<< this->tMin <<":"<< this->tMax << "]\n";
     plotScript << "set yrange [0:1]\n";

     plotScript << "set xlabel 'residence time'\n";
     plotScript << "set ylabel 'p(t_{"<< variable << "})'\n";


     double dt = ( tMax-tMin ) / this->nBins;
     cout << "dt = " << dt << endl;
     double scale = 1.0/ ( gsl_histogram_sum ( histogram ) );
     cout << "scale: "<< scale << endl;
     gsl_histogram_scale (histogram,  scale );

    
     
     FILE * pFile = fopen ( dataFullPath,"w" );

     gsl_histogram_fprintf ( pFile,  histogram, "%g", "%g" );

     fclose ( pFile );


     plotScript<< "plot '"<<datafileName <<"' using ($1+ ($2-$1)/2):3 with linespoints title 'p(t_{"<< variable << "})' lc rgbcolor 'red' lw 2\n";


     plotScript.close();


}





void ResidenceTimeDistribution::fill ( double t, double x, double y )
{

  if( t==0.0 ) {
   //reset 
    
    residenceTimeStart = 0.0;
    lastPosition = 0.0;
//     cout << "new traj"<<endl;
  }
  else {
    if( x * lastPosition < 0.0 ) {
     //state changed 
      
      double residenceTime = t - residenceTimeStart;
      
//       cout << " state changed, old pos:" << lastPosition << " new pos: " << x << " residenceTime = " << residenceTime <<endl;
      if( x > statesBorderX ) {
	// now is in right, so was in left
        gsl_histogram_increment (this->p_left ,  residenceTime);
      }
      else if( x < statesBorderX ) {
	//now is in left so was in right
	gsl_histogram_increment (this->p_right ,  residenceTime);
      }
      
      //save summarized also
      gsl_histogram_increment (this->p_total ,  residenceTime);
      
      residenceTimeStart = t;
    }
    else {
     // state not changed 
    }
    
    
    lastPosition = x;
  }
  // we need to calculate residence time
  
  
}

