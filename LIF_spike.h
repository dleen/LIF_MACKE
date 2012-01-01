#include "LIF_constants.h"

using namespace boost::numeric::ublas;

class LIF_spike {
public:
	 LIF_spike(int N);
	~LIF_spike();

	void create_LIF_data(double gamma, double lambda);
	void zero_LIF_data();

	void print_statistics();
	void print_statistics_to_file();

	void create_figure_1b(double gamma);
	void create_figure_2a(double gamma);

private:
	void num_of_neurons(int N);

	void generate_spike_matrix();

	void calculate_spike_statistics();
	void calculate_probability_dist();

	char progress_bar(int percentage);

	int N;
	double gamma, lambda, mu, rho;
	std::vector<double> *P;
	matrix<int> spikes;	

	gsl_rng *r;
};
