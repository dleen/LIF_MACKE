#include "LIF_spike.h"

using namespace std;

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
        //double C1 = exp(-DT/TAU);
        //double C2 = sigma*sqrt(TAU*(1-C1*C1)/2);

	//double Vavg=0;

	//cout << C1 <<" "<<C2 <<endl;

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
		//Vavg += V[0];
		//cout << V[0] << endl;
        }
	//Vavg /= TOT_INT_TIME;
	//cout << Vavg << endl;
}
