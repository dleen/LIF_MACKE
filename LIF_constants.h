#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>

#include <time.h>

#include <gsl/gsl_statistics_int.h>
#include <gsl/gsl_statistics.h>

#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#define total_time 5000
#define dt 1
#define Tstop 5000

#define THRESHOLD 1.0
#define SIGMA 1.0
#define tau 5.0

#define VRESET -1.0
#define AbsRefractPts 1.0

using namespace std;
