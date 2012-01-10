#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <time.h>

#include <gsl/gsl_statistics_int.h>
#include <gsl/gsl_statistics.h>

#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#define THRESHOLD 4.5 //Juliana's value. Old value = 1.0
#define SIGMA 3.0 //Juliana's value. Old value = 1.0
#define tau 5.0
#define inttau 5 //int version of tau
#define VRESET -1.0
#define AbsRefractPts 70 //previous value = 1
#define RelRefractDecay 1

#define total_time 200000
#define dt tau/100
#define TOT_INT_TIME total_time*100/inttau //i.e. total_time/dt
#define T_binning 100*RelRefractDecay
//#define Tstop 100*total_time/(T_binning*inttau)
#define Tstop total_time/T_binning
