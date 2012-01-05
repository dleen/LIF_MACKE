#include "LIF_constants.h"

class LIF_spike {
public:
	 LIF_spike(int N);
	~LIF_spike();

	void create_LIF_data(double gamma, double lambda);
	void zero_LIF_data();

	void print_statistics();
	void print_statistics_to_file(std::string preamble, double identifier);

	void figure_1a_components(double lambda);
	void figure_1b_components(double gamma);
	void figure_2a_components(double lambda);

	char progress_bar(int percentage);

private:
	void num_of_neurons(int N);

	void generate_spike_matrix();

	void calculate_spike_statistics();
	void calculate_probability_dist();

	int N;
	double gamma, lambda, mu, rho;
	std::vector<double> *P;
	boost::numeric::ublas::matrix<int> spikes;	

	gsl_rng *r;
};
