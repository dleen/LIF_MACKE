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
        gsl_rng_set(r,time(NULL));
}

void LIF_spike::seed_ran_gen(int seed)
{
	gsl_rng_set(r,seed);
}

void LIF_spike::num_of_neurons(int N)
{
	// Set the number of neurons.
	this->N = N;
}

void LIF_spike::create_XIF_data(double gamma, double lambda, double sigma, string neuron_model)
{
	// Calls the operations in the correct order.
	this->gamma = gamma;
	this->lambda = lambda;
	this->sigma = sigma;
	
	// Generate the spikes.
	// This function is the meat of the code and can be found in a separate file.
	if(neuron_model == "LIF") {
		LIF_gen_spike_matrix();
	}
	else if(neuron_model == "EIF") {
		EIF_gen_spike_matrix();
	}
	else if(neuron_model == "QIF") {
		QIF_gen_spike_matrix();
	}
	else if(neuron_model == "DG") {
		DG_gen_spike_matrix();
	}
	else
	{
		cout << "Not a valid model" << endl;
	}

	// Check for more than 1 spike per bin and set to 1 spike per bin.
	count_double_spikes();

	// Calculate the mean firing rate mu and the correlation coefficient rho.
	calculate_spike_statistics();

	// Calculate P(x).
	calculate_probability_dist();
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
				// Reset double spikes back to zero as we
				// dont want more than 1 spike per bin.
				spikes(i,j) = 1;
                        }
                }
        }
        //cout <<"Percent of spikes > 1 = "<< (double)100*count/(TSTOP*N) <<endl;
	double_count = (double)100*count/(TSTOP*N);
}

void LIF_spike::calculate_spike_statistics()
{
	// The columns of 'spikes' are different neurons and the rows are 
	// observations.
	double mean_of_cov = 0;
	double mean_of_var = 0;
	double* means = new double[N];
	double* temp_matrix = new double[TSTOP*N];
	double* cov = new double[N*N];

	// Find the mean of each column.
	for(int i=0; i<N; ++i)
	{
		means[i] = 0;
		for(int j=0; j<TSTOP; ++j)
		{
			means[i] += spikes(j,i);
		}
		means[i] /= TSTOP;
	}

	// In this particular problem the neurons are identical so take the
	// mean of the means.
	for(int i=0; i<N; ++i)
	{
		mu += means[i];
	}

	// Important variable:
	// mu = mean firing rate.
	mu /= N;

	// Initial step to calculate the covariance matrix, subtract the mean of
	// each column from each element in that column.
	for(int i=0; i<N; ++i)
	{
		for(int j=0; j<TSTOP; ++j)
		{
			temp_matrix[j*N+i] = spikes(j,i) - means[i];
		}
	}

	// Multiply temp_matrix^T temp_matrix and divide by length-1 
	// for unbiased cov.
	for(int i=0; i<N; ++i)
	{
		for(int j=0; j<N; ++j)
		{
			cov[i*N+j] = 0;
			for(int k=0; k<TSTOP; ++k)
			{
				cov[i*N+j] += temp_matrix[k*N+i]*temp_matrix[k*N+j];
			}
			cov[i*N+j] /= TSTOP-1;
		}
	}
	
	// Neurons are identical so take mean of the covs (off diagonal terms).
	for(int i=0; i<N; ++i)
	{
		for(int j=i+1; j<N; ++j)
		{
			mean_of_cov += cov[i*N+j];
		}
	}	
	mean_of_cov /= N*(N-1)/2;

	// Mean of diagonal will give mean of the variance.
	for(int i=0; i<N; ++i)
	{
		mean_of_var += cov[i*N+i];
	}
	mean_of_var /= N;
	
	// Calculate coefficient of variation.
	cv = sqrt(mean_of_var)/mu;

	// Important variable:
	// rho = correlation coefficient as defined in Macke 2011.
	rho = mean_of_cov/mean_of_var;

	delete [] means;
	delete [] temp_matrix;
	delete [] cov;
}

void LIF_spike::calculate_probability_dist()
{
	// The probability distribution P(x) is the probability distribution
	// across the possible states of the neurons. i.e for 5 neurons
	// P(01100) is the probability of the 2nd and 3rd neurons firing and the 
	// rest not firing. Since our neurons are identical we know that
	// P(01100) = P(10010) = ... This means that each state is uniquely
	// identified by the population spike count i.e P(01100) = P(2).
	// For 5 neurons the possible population spike counts are simply
	// 0, 1, 2, 3, 4, 5. This function calculates P(0), P(1),...
        int i=0,j=0,total=0;

	vector<int> temp_sum(TSTOP,0);
	vector<int> temp_prob(N+1,0);

	vector<int>::iterator it; 

	// Sum up the rows of spikes to get the population spike counts.
	// If we have a row 01100 we sum to get the number 2.
	// i.e collapse the matrix: TSTOP*N -> TSTOP
        for(i=0; i<TSTOP; ++i)
        {
                for(j=0; j<N; ++j)
                {
                        temp_sum[i] += spikes(i,j);
                }
        }

	// Sort the resulting vector.
	sort(temp_sum.begin(),temp_sum.end());

	// Count the number of occurrences of each value of the population spike count.
	// This is made easier as we have ordered them from 0 to N.
	j=0;
        for(i=0; i<N+1; ++i)
        {
                while(j<TSTOP && temp_sum[j] == i)
                {
                        temp_prob[i] += 1;
                        ++j;
                }
        }

	// Count the total number of spikes.
	for(it=temp_prob.begin(); it<temp_prob.end(); ++it)
        {
                total += *it;
        }

	// Divide by the total to get the probability distribution.
        for(i=0; i<N+1; ++i)
        {
                P->at(i) = (double)temp_prob[i]/total;
        }
}

void LIF_spike::zero_LIF_data()
{
	// Set all variables to zero.
	gamma = 0;
	lambda = 0;
	mu = 0;
	rho = 0;

	P->assign(N+1,0);

	// This is especially important as we assume "spikes" contains
	// only zeros when we run "generate_spike_matrix". Otherwise
	// each call to generate_spike_matrix will keep adding more
	// 1's to spikes until it is saturated.
	spikes = boost::numeric::ublas::zero_matrix<int>(TSTOP,N);
}

void LIF_spike::print_statistics()
{
	// Does what it says.
	cout <<"sigma = "<< sigma << endl;
	cout <<"CV = "<< cv << endl;
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

void LIF_spike::print_statistics_to_file(string preamble, double identifier,
int loop_iteration, int i, int j)
{
	// Does what it says.
	ofstream fig_out;

	string mean_name, mean2_name, filename;

	stringstream temp1;
	temp1 << identifier;
	mean_name = temp1.str();

	stringstream temp2;
	temp2 << loop_iteration;
	mean2_name = temp2.str();

	filename = preamble+mean_name+"_"+"loop_"+mean2_name+".dat";

	fig_out.open(filename.c_str(),ios::app);

	fig_out << i <<" "<< j <<" ";
	for(vector<double>::iterator dit=P->begin(); dit<P->end(); ++dit)
	{
		// Print out probability distribution P:
		fig_out << *dit <<" ";
	}
	// Print out the rest of the statistics:
	fig_out << mu <<" "<< rho <<" ";
	fig_out << gamma <<" "<< lambda <<" ";
	fig_out << double_count << endl;

	fig_out.close();
}

LIF_spike::~LIF_spike()
{
	// Destructor for LIF_spike class.
	spikes.clear();
	gsl_rng_free(r);
	// Free pointer P.
	delete P;
}
