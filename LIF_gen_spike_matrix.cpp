#include "LIF_spike.h"

using namespace std;

void LIF_spike::generate_spike_matrix()
{
        int tt=0, nn=0, index=0;
        double current_time=0;
        double eta=0, eta_c=0;

        // To keep track of the number of spikes
        vector<int> num_spikes(N,0);
        // Contains the times of the last spikes
        vector<double> spike_times(N,0);
        // Contains the voltages
        vector<double> V(N,0), Vold(N,0);

        // Calculate constants outside loop for speed
        double sqrtcorr = sqrt(lambda);
        double sqrtonemcorr = sqrt(1-lambda);
        double C1 = exp(-dt/tau);
        double C2 = SIGMA*sqrt(tau*(1-C1*C1)/2);

        for (tt=0; tt<TOT_INT_TIME; ++tt)
        {
                current_time = tt*dt;

                // Common gaussian input to each neuron
                // Changes over only each time step
                eta_c = gsl_ran_gaussian_ziggurat(r,1);

                for (nn=0; nn<N; ++nn)
                {
                        // Independent gaussian input
                        eta = gsl_ran_gaussian_ziggurat(r,1);

                        if (num_spikes[nn] == 0 ||
                                ((current_time - spike_times[nn]) > AbsRefractPts))
                        {
                                // Exact update algorithm
                                V[nn] = Vold[nn]*C1 + C2*sqrtcorr*eta_c +
                                C2*sqrtonemcorr*eta + (1-C1)*gamma;

                                if (V[nn] > THRESHOLD)
                                {
                                        ++num_spikes[nn];
                                        spike_times[nn] = current_time;
                                        index = ceil(current_time/T_binning)-1;
                                        //index = ceil((double)tt/T_binning)-1;
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
        }

        // Check how many bins have more than one spike
        int count=0;
        for(int i=0; i<Tstop; ++i)
        {
                for(int j=0; j<N; ++j)
                {
                        if(spikes(i,j)>1)
                        {
                                ++count;
                                spikes(i,j) = 1;
                        }
                }
        }
        cout <<"Percent of spikes > 1 = "<< (double)100*count/(Tstop*N) <<endl;
}
