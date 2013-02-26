#include "LIF_spike.h"

using namespace std;

/*
	Split 100 runs of simulation into 10 chunks
	of 10.
*/
void fig_2mu_comps(const parameters_t& XIF_params, string neuron_model,
double subplot, int loop_iteration, int num_neurons=100)
{
	// Create spike container. Not necessarily LIF.
	LIF_spike S(num_neurons);

	if(loop_iteration < 0 || loop_iteration > 10) {
		cout << "Not a valid loop number!" << endl;
		exit(0);
	}

	int lower_loop=loop_iteration*10;
	int upper_loop=loop_iteration*10+10;

	// For printing the N value used in the file name
	stringstream ss;
	ss << num_neurons;

	// Main loop.
	for(int i=lower_loop; i<upper_loop; ++i)
	{
		// Change seed
		S.seed_ran_gen(i+9872349);
       	S.create_XIF_data(XIF_params.gamma,
				  XIF_params.lambda,
				  XIF_params.sigma,
				  neuron_model);
		S.print_statistics_to_file("fig_2mu_"+ss.str()+"_",
		subplot,loop_iteration,i,num_neurons);
		S.zero_LIF_data();
	}
}

void paper_fig_2_const_mu(double subplot, std::string neuron_model,
	int loop_iteration, int num_neurons)
{
	double sigma_LIF = 6.23;

	if(subplot == 0.05) {
		if(neuron_model == "EIF") {
			parameters_t LIF_params = {-60,0.17,sigma_LIF,0,0};
			fig_2mu_comps(LIF_params,neuron_model,subplot,
			loop_iteration,num_neurons);
		}
	}
	else if(subplot == 0.1) {
		if(neuron_model == "EIF") {
			parameters_t LIF_params = {-60,0.305,sigma_LIF,0,0};
			fig_2mu_comps(LIF_params,neuron_model,subplot,
			loop_iteration,num_neurons);
		}
	}
	else if(subplot == 0.25) {
		if(neuron_model == "EIF") {
			parameters_t LIF_params = {-60.02,0.599,sigma_LIF,0,0};
			fig_2mu_comps(LIF_params,neuron_model,subplot,
			loop_iteration,num_neurons);
		}
	}
	else {
		cout << "Not a valid subplot value!" << endl;
	}
}

void paper_fig_2_const_rho(double subplot, std::string neuron_model,
	int loop_iteration, int num_neurons)
{
	double sigma_LIF = 6.23;

	if(subplot == 0.1) {
		if(neuron_model == "EIF") {
			parameters_t LIF_params = {-60,0.305,sigma_LIF,0,0};
			fig_2mu_comps(LIF_params,neuron_model,subplot,
			loop_iteration,num_neurons);
		}
	}
	else if(subplot == 0.2) {
		if(neuron_model == "EIF") {
			parameters_t LIF_params = {-58.21,0.256,sigma_LIF,0,0};
			fig_2mu_comps(LIF_params,neuron_model,subplot,
			loop_iteration,num_neurons);
		}
	}
	else if(subplot == 0.3) {
		if(neuron_model == "EIF") {
			parameters_t LIF_params = {-56.8,0.237,sigma_LIF,0,0};
			fig_2mu_comps(LIF_params,neuron_model,subplot,
			loop_iteration,num_neurons);
		}
	}
	else {
		cout << "Not a valid subplot value!" << endl;
	}
}

void paper_figure_control(string figure_name, double subplot,
	string neuron_model, int loop_iteration, int num_neurons)
{
	if(figure_name == "paper2mu") {
		paper_fig_2_const_mu(subplot,neuron_model,loop_iteration,num_neurons);
	}
	else if(figure_name == "paper2rho") {
		paper_fig_2_const_rho(subplot,neuron_model,loop_iteration,num_neurons);
	}
	else {
		cout << "Not a valid figure name!" << endl;
	}
}
