#include "LIF_spike.h"

using namespace std;

void LIF_spike::EIF_gen_spike_matrix()
{
        int tt=0, nn=0, index=0;
        double current_time=0;
        double eta=0, eta_c=0;

        // To keep track of the number of spikes
        vector<int> num_spikes(N,0);
        // Contains the times of the last spikes
        vector<double> spike_times(N,0);
        // Initialize the voltages at the reset potential
        vector<double> V(N,VRESET), Vold(N,VRESET);

        // Calculate constants outside loop for speed
        double sqrtcorr = sqrt(DT)*sigma*sqrt(lambda)/sqrt(TAU);
        double sqrtonemcorr = sqrt(DT)*sigma*sqrt(1-lambda)/sqrt(TAU);

	double dttau = DT/TAU;
	double gamma_coeff = DT*gamma/TAU;
	double exp_coeff = dttau*DELTAT;
        //double C1 = exp(-DT/TAU);
        //double C2 = sigma*sqrt(TAU*(1-C1*C1)/2);

	double Vavg=0;

	//cout << C1 <<" "<<C2 <<endl;

        for (tt=0; tt<TOT_INT_TIME; ++tt)
        {
                current_time = tt*DT;

                // Common gaussian input to each neuron
                // Changes over only each time step
                eta_c = sqrtcorr*gsl_ran_gaussian_ziggurat(r,1);

                for (nn=0; nn<N; ++nn)
                {
                        // Independent gaussian input
                        eta = sqrtonemcorr*gsl_ran_gaussian_ziggurat(r,1);

                        if (num_spikes[nn] == 0 ||
                                ((current_time - spike_times[nn]) > AbsRefractPts))
                        {
				V[nn] = Vold[nn]-dttau*Vold[nn] + gamma_coeff +
				exp_coeff*exp((Vold[nn]-SOFT_THRESH)/DELTAT)+
				eta_c + eta;

				// Threshold crossing
                                if (V[nn] > THRESHOLD)
                                {
                                        ++num_spikes[nn];
                                        spike_times[nn] = current_time;
                                        index = (int)floor(current_time/T_BINNING);
                                        spikes(index,nn) += 1;
                                        V[nn] = VRESET;
                                }
                        }
                        else
                        {
                                V[nn] = Vold[nn];
                        }
                        Vold[nn] = V[nn];
                }
		Vavg += V[0];
		//cout << V[0] <<" "<< V[1] <<" "
		//<< V[2] <<" "<< V[3] << endl;
        }
	Vavg /= TOT_INT_TIME;
	//cout << Vavg << endl;
}
