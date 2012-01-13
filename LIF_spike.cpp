#include "LIF_spike.h"

using namespace std;

LIF_spike::LIF_spike(int N)
{
	// Set the number of neurons:
	num_of_neurons(N);

	// Initialise probability distribution P:
	P = new vector<double>(N+1);

	// Initialise the data and set to zero:
	zero_LIF_data();

	// Set up the random number generator:
        gsl_rng_env_setup();
        r = gsl_rng_alloc(gsl_rng_taus);
        //gsl_rng_set(r,time(NULL));
}

LIF_spike::~LIF_spike()
{
	// Destructor for LIF_spike class
	spikes.clear();
	gsl_rng_free(r);
	// Free pointer P
	delete P;
}

void LIF_spike::num_of_neurons(int N)
{
	this->N = N;
}

void LIF_spike::calculate_spike_statistics()
{
        int i,j,k;
	int covariant_1[TSTOP],covariant_2[TSTOP];

	// These are not vectors since GSL libraries want arrays
        double *mmu = new double[N];
        double *cov = new double[N*N];

	double *temp = new double[N];
	double *temp1 = new double[N*(N-1)/2];

	double mudiag=0, meancov=0;

	// Initialise to zero
	for(i=0; i<N; ++i)
	{
		mmu[i] = 0;
		temp[i] = 0;
	}
	for(i=0; i<N*N; ++i)
	{
		cov[i] = 0;
	}
	for(i=0; i<N*(N-1)/2; ++i)
	{
		temp1[i] = 0;
	}
	for(i=0; i<TSTOP; ++i)
	{
		covariant_1[i] = 0;
		covariant_2[i] = 0;
	}

	// Calculate the mean firing rate for each neuron
	// and calculate the covariance matrix
	for(k=0; k<N; ++k)
	{
		// Put each column of the matrix spikes into an array
		// Need to do this as GSL only works with arrays
        	for(j=0; j<TSTOP; ++j)
        	{
                	covariant_1[j]  = spikes(j,k);
        	}
		// Calculate mean of each column
                mmu[k] = gsl_stats_int_mean(covariant_1,1,TSTOP);

        	for(i=k; i<N; ++i)
        	{
			// Take another column of the matrix spikes
                	for(j=0; j<TSTOP; ++j)
                	{
                	        covariant_2[j] = spikes(j,i);
                	}
			// and calculate the covariance between this column and the one 
			// chosen previously
                	cov[k*N+i]  = gsl_stats_int_covariance(covariant_1,1,covariant_2,1,TSTOP);
        	}
	}

	// Take the mean value of the mean of each column
        mu = gsl_stats_mean(mmu,1,N);

	// Find mean value of the diagonal of covariance matrix
	for(i=0; i<N; ++i)
	{
		temp[i] = cov[i*N+i];
	}

	mudiag = gsl_stats_mean(temp,1,N);

	// Find mean value of the off diagonal elements of cov matrix
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

	// Value defined in Macke paper
        rho = meancov/mudiag;

	// Free pointers
	delete [] mmu;
	delete [] cov;
	delete [] temp;
	delete [] temp1;
}

void LIF_spike::calculate_probability_dist()
{
        int i=0,j=0,total=0;

	vector<int> temp_sum(TSTOP,0);
	vector<int> temp_prob(N+1,0);

	vector<int>::iterator it; 

	// Sum across the matrix of spikes
	// i.e collapse the matrix: Tstop*N -> Tstop
        for(i=0; i<TSTOP; ++i)
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
                while(j<TSTOP && temp_sum[j] == i)
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
	for(vector<double>::iterator dit=P->begin(); dit<P->end(); ++dit)
	{
		cout << *dit << " ";
	}
	cout <<"\n"<< endl;
}

void LIF_spike::print_statistics_to_file(string preamble, double identifier)
{
	ofstream fig_out;

	string mean_name, filename, end_name (".dat");

	stringstream temp;
	temp << identifier;
	mean_name = temp.str();

	filename = preamble+mean_name+end_name;

	fig_out.open(filename.c_str(),ios::app);

	for(vector<double>::iterator dit=P->begin(); dit<P->end(); ++dit)
	{
		fig_out << *dit <<" ";
	}
	fig_out << mu <<" "<< rho <<" ";
	fig_out << gamma <<" "<< lambda << endl;

	fig_out.close();
}

void LIF_spike::create_LIF_data(double gamma, double lambda)
{
	this->gamma = gamma;
	this->lambda = lambda;
	
	generate_spike_matrix();

	count_double_spikes();

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

	spikes = boost::numeric::ublas::zero_matrix<int>(TSTOP,N);
}

void LIF_spike::count_double_spikes()
{
        int count=0;

        for(int i=0; i<TSTOP; ++i)
        {
                for(int j=0; j<N; ++j)
                {
                        if(spikes(i,j)>1) {
                        	++count;
				spikes(i,j) = 1;
                        }
                }
        }
        cout <<"Percent of spikes > 1 = "<< (double)100*count/(TSTOP*N) <<endl;
}
