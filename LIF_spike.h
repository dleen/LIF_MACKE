#include "LIF_constants.h"

class LIF_spike {
public:
	 LIF_spike(int N = 5);
	~LIF_spike();

	// Create a matrix of spikes of size Tstop*N
	// where N corresponds to the number of neurons	
	// and Tstop corresponds to the time/time_bins
	void create_LIF_data(double gamma, double lambda);

	// Zeros all data. This needs to be called each time when you are 
	// intending to re-use a LIF_spike.
	void zero_LIF_data();

	void print_statistics();
	void print_statistics_to_file(std::string preamble, double identifier);

private:
	void num_of_neurons(int N);

	void generate_spike_matrix();

	void count_double_spikes();

	void calculate_spike_statistics();
	void calculate_probability_dist();

	// Number of neurons.
	int N;
	// Input statistics:
	// gamma = mean of input
	// lambda = correlation strength of gaussian.
	double gamma, lambda;
	// Output statistics:
	// mu = mean firing rate of output
	// rho = correlation coefficient of output
	double mu, rho;
	// To keep track of times when there are multiple
	// spikes in the same bin.
	double double_spike_count;
	// The probability distribution P(x).
	std::vector<double> *P;
	// The matrix to hold the spikes.
	// It will have TSTOP rows and N columns.
	boost::numeric::ublas::matrix<int> spikes;	
	// For the GSL random number generator.
	gsl_rng *r;
};

// Helper functions:
char progress_bar(int percentage);

// Each of these gives ones of the curves in the Macke figures.
void figure_1a_components(LIF_spike* S, double lambda);
void figure_1b_components(LIF_spike* S, double gamma);
void figure_2a_components(LIF_spike* S, double lambda);

// Each of these creates the figures in Macke 2011.
void create_figure_1a();
void create_figure_1b();
void create_figure_2a();
