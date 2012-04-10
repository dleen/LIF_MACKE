#ifndef LIF_CONSTANTS_H
#define LIF_CONSTANTS_H

#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <ctime>

#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#define THRESHOLD -50.0 //Juliana's value. Old value = 1.0
#define SOFT_THRESH -53.0
#define DELTAT 3.0
#define TAU 5.0
#define INTTAU 5 //int version of tau
#define VRESET -60.0
#define AbsRefractPts 3 //previous value = 1
#define RelRefractDecay 1

#define TOTAL_TIME 500000
#define DT TAU/100
#define TOT_INT_TIME TOTAL_TIME*100/INTTAU //i.e. total_time/dt
#define T_BINNING 10
#define TSTOP TOTAL_TIME/T_BINNING

#endif
