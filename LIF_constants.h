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

#define THRESHOLD 10 //Juliana's value. Old value = 1.0
#define SIGMA 3.0 //Juliana's value. Old value = 1.0
#define TAU 5.0
#define INTTAU 5 //int version of tau
#define VRESET -10
#define AbsRefractPts 5 //previous value = 1
#define RelRefractDecay 1

#define TOTAL_TIME 200000
#define DT TAU/100
#define TOT_INT_TIME TOTAL_TIME*100/INTTAU //i.e. total_time/dt
#define T_BINNING 100*RelRefractDecay
//#define Tstop 100*total_time/(T_binning*inttau)
#define TSTOP TOTAL_TIME/T_BINNING
