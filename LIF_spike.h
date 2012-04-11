#ifndef LIF_SPIKE_H
#define LIF_SPIKE_H

#include "LIF_constants.h"

class LIF_spike {
public:
	 LIF_spike(int N = 5);
	~LIF_spike();

	// Create a matrix of spikes of size Tstop*N
	// where N corresponds to the number of neurons	
	// and Tstop corresponds to the time/time_bins
	void create_XIF_data(double gamma, double lambda, double sigma,
		std::string neuron_model);

	void seed_ran_gen(int seed);

	// Zeros all data. This needs to be called each time when you are 
	// intending to re-use a LIF_spike.
	void zero_LIF_data();

	void print_statistics();
	void print_statistics_to_file(std::string preamble, double identifier,
	int loop_iteration, int i, int j);

private:
	void num_of_neurons(int N);

	void DG_gen_spike_matrix();
	void LIF_gen_spike_matrix();
	void EIF_gen_spike_matrix();

	void count_double_spikes();

	void calculate_spike_statistics();
	void calculate_probability_dist();
	void calc_coeff_of_var();

	// Number of neurons.
	int N;
	// Input statistics:
	// gamma = mean of input
	// lambda = correlation strength of gaussian.
	double gamma, lambda, sigma;
	// Output statistics:
	// mu = mean firing rate of output
	// rho = correlation coefficient of output
	// cv = coefficient of variation
	double mu, rho, cv;
	// To keep track of times when there are multiple
	// spikes in the same bin.
	double double_count;
	// The probability distribution P(x).
	std::vector<double> *P;
	// The matrix to hold the spikes.
	// It will have TSTOP rows and N columns.
	boost::numeric::ublas::matrix<int> spikes;	
	// For the GSL random number generator.
	gsl_rng *r;
};

typedef struct {
	double gamma;
	double lambda;
	double sigma;
	double upper_lim;
	double lower_lim;
} parameters_t;

// Helper functions:
char progress_bar(int percentage);

// Each of these gives ones of the curves in the Macke figures.
void figure_1a_components(const parameters_t& XIF_params, 
std::string neuron_model, int loop_iteration);
void figure_1b_components(const parameters_t& XIF_params,
std::string neuron_model, double subplot, int loop_iteration);
void figure_2a_components(const parameters_t& XIF_params,
std::string neuron_model, double subplot, int loop_iteration, int num_neurons);

// Each of these creates the figures in Macke 2011.
void create_figure_1a(double subplot, std::string neuron_model,
int loop_iteration);
void create_figure_1b(double subplot, std::string neuron_model,
int loop_iteration);
void create_figure_2a(double subplot, std::string neuron_model,
int loop_iteration);
void create_custom(double subplot, std::string neuron_model,
int loop_iteration);

void figure_control(std::string figure_name, double subplot, 
std::string neuron_model, int loop_iteration);

#endif
