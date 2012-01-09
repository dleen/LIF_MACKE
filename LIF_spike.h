#include "LIF_constants.h"

class LIF_spike {
public:
	 LIF_spike(int N);
	~LIF_spike();

	// Create a matrix of spikes of size Tstop*N
	// where N corresponds to the number of neurons	
	// and Tstop corresponds to the time/time_bins
	void create_LIF_data(double gamma, double lambda);

	// Zeros all data. This needs to be called when you are 
	// intending to re-use a LIF_spike 
	void zero_LIF_data();

	void print_statistics();
	void print_statistics_to_file(std::string preamble, double identifier);

private:
	void num_of_neurons(int N);

	void generate_spike_matrix();

	void calculate_spike_statistics();
	void calculate_probability_dist();

	int N;
	double gamma, lambda;
	double mu, rho;
	double double_spike_count;
	std::vector<double> *P;
	boost::numeric::ublas::matrix<int> spikes;	

	gsl_rng *r;
};

// Helper functions:
char progress_bar(int percentage);

void figure_1a_components(LIF_spike* S, double lambda);
void figure_1b_components(LIF_spike* S, double gamma);
void figure_2a_components(LIF_spike* S, double lambda);

void create_figure_1a();
void create_figure_1b();
void create_figure_2a();
