#include "LIF_spike.h"

using namespace boost::numeric::ublas;

LIF_spike::LIF_spike(int N)
{
	// Constructor for LIF_spike class.

	num_of_neurons(N);

	// Initialise probability distribution P.
	P = new std::vector<double>(N+1);

	// Initialise the data and set to zero. 
	zero_LIF_data();

	// Set up the random number generator.
        gsl_rng_env_setup();
        r = gsl_rng_alloc (gsl_rng_default);
        gsl_rng_set(r,time(NULL));
}

LIF_spike::~LIF_spike()
{
	// Destructor for LIF_spike class.
	spikes.clear();
	gsl_rng_free(r);
	delete P;
}

void LIF_spike::num_of_neurons(int N)
{
	this->N = N;
}

void LIF_spike::generate_spike_matrix()
{
        int tt, nn;

	std::vector<int> spike_times(N,0), num_spikes(N,0);
	std::vector<double> V(N,0), Vold(N,0);

	std::vector<double> X2(Tstop*N,gsl_ran_gaussian(r,SIGMA)),\
			    X1(Tstop,gsl_ran_gaussian(r,SIGMA));

	std::vector<double>::iterator dit;

        double sqrtcorr = sqrt(lambda);
        double sqrtonemcorr = sqrt(1-lambda);
        double C1 = exp(-1*dt/tau);
        double C2 = sqrt(SIGMA*SIGMA*tau*(1-C1*C1)/2);

        for (tt=0; tt<Tstop; tt++)
        {
                for (nn=0; nn<N; nn++)
                {
                        if (num_spikes[nn] == 0 || \
                                ((tt - spike_times[nn]) > AbsRefractPts))
                        {
                                V[nn] = Vold[nn]*C1 + C2*sqrtcorr*X1[tt] + \
                                C2*sqrtonemcorr*X2[tt*N+nn] + C2*gamma;

                                if (V[nn] > THRESHOLD)
                                {
                                        num_spikes[nn]++;
                                        spike_times[nn] = tt;
                                        spikes(tt,nn) = 1;
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
}

void LIF_spike::calculate_spike_statistics()
{
        int i,j,k;
	int covariant_1[Tstop],covariant_2[Tstop];

        double *mmu = new double[N];
        double *cov = new double[N*N];

	double *temp = new double[N];
	double *temp1 = new double[N*(N-1)/2];

	double mudiag=0, meancov=0;

	for(i=0; i<N; ++i)
	{
		for(j=0; j<N; ++j)
		{
			cov[i*N+j] = 0;
		}
		mmu[i] = 0;
	}

	for(k=0; k<N; ++k)
	{
        	for(j=0; j<Tstop; ++j)
        	{
                	covariant_1[j]  = spikes(j,k);
        	}
                mmu[k] = gsl_stats_int_mean(covariant_1,1,Tstop);

        	for(i=k; i<N; ++i)
        	{
                	for(j=0; j<Tstop; ++j)
                	{
                	        covariant_2[j] = spikes(j,i);
                	}
                	cov[k*N+i]  = gsl_stats_int_covariance(covariant_1,1,covariant_2,1,Tstop);
        	}
	}

        mu = gsl_stats_mean(mmu,1,N);

	for(i=0; i<N; ++i)
	{
		temp[i] = cov[i*N+i];
	}

	mudiag = gsl_stats_mean(temp,1,N);

	k=0;
	for(i=0; i<N; ++i)
	{
		for(j=i+1; j<N; ++j)
		{
			temp1[k] = cov[i*N+j];
			++k;
		}
	}

	meancov = gsl_stats_mean(temp1,1,N*(N-1)/2);

        rho = meancov/mudiag;

	delete [] mmu;
	delete [] cov;
	delete [] temp;
	delete [] temp1;
}

void LIF_spike::calculate_probability_dist()
{
        int i,j,total=0;

	std::vector<int> temp_sum(Tstop,0);
	std::vector<int> temp_prob(N+1,0);

	std::vector<int>::iterator it; 

        for(i=0; i<Tstop; ++i)
        {
                for(j=0; j<N; ++j)
                {
                        temp_sum[i] += spikes(i,j);
                }
        }

	sort(temp_sum.begin(),temp_sum.end());

	j=0;
        for(i=0; i<N+1; ++i)
        {
                while(j<Tstop && temp_sum[j] == i)
                {
                        temp_prob[i] += 1;
                        ++j;
                }
        }

	for(it=temp_prob.begin(); it<temp_prob.end(); ++it)
        {
                total += *it;
        }

        for(i=0; i<N+1; ++i)
        {
                P->at(i) = (double)temp_prob[i]/total;
        }
}

void LIF_spike::print_statistics()
{
	cout <<"gamma = "<< gamma <<"\t lambda = "<< lambda << endl;
	cout <<"mu = "<< mu <<"\t rho = "<< rho << endl;
	cout << endl;
	cout <<"P = ";
	//for(int i=0; i<N+1; ++i)
	for(std::vector<double>::iterator dit=P->begin(); dit<P->end(); ++dit)
	{
		cout << *dit << " ";
		//cout << P->at(i) << " ";
	}
	cout <<"\n"<< endl;
}

void LIF_spike::print_statistics_to_file()
{
	ofstream fig_out;

	string preamble ("figure_1b_");
	string mean_name, filename, end_name (".dat");

	stringstream temp;
	temp << gamma;
	mean_name = temp.str();

	filename = preamble+mean_name+end_name;

	fig_out.open(filename.c_str(),ios::app);

	for(std::vector<double>::iterator dit=P->begin(); dit<P->end(); ++dit)
	{
		fig_out << *dit <<" ";
	}
	fig_out << mu <<" "<< rho << endl;

	fig_out.close();
}

void LIF_spike::create_LIF_data(double gamma, double lambda)
{
	this->gamma = gamma;
	this->lambda = lambda;
	
	generate_spike_matrix();

	calculate_spike_statistics();

	calculate_probability_dist();
}

void LIF_spike::zero_LIF_data()
{
	gamma = 0;
	lambda = 0;
	mu = 0;
	rho = 0;

	P->assign(N+1,0);

	spikes = zero_matrix<int>(Tstop,N);
}
