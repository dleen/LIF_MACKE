#include "LIF_spike.h"

using namespace std;

/* Generates spikes according to the
   Dichotomized Gaussian model.
   Very simple idea. Generate Gaussian
   noise inputs, and compare to a threshold.
   See Macke 2011 for details.
*/
void LIF_spike::DG_gen_spike_matrix()
{
        int tt=0, nn=0;
        double eta=0, eta_c=0;

        // To keep track of the number of spikes
        // Contains the times of the last spikes
        // Initialize the voltages at the reset potential
        vector<double> V(N,0);

        // Calculate constants outside loop for speed
        double sqrtcorr = sqrt(lambda);
        double sqrtonemcorr = sqrt(1-lambda);

        for (tt=0; tt<TSTOP; ++tt)
        {
                // Common gaussian input to each neuron
                // Changes over only each time step
                eta_c = gsl_ran_gaussian_ziggurat(r,1);

                for (nn=0; nn<N; ++nn)
                {
                        // Independent gaussian input
                        eta = gsl_ran_gaussian_ziggurat(r,1);

			V[nn] = gamma + sqrtcorr*eta_c + sqrtonemcorr*eta;

			// Threshold crossing
                        if (V[nn] > 0) {
				spikes(tt,nn) = 1;
                        }
                }
        }
}
