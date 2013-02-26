#include "LIF_spike.h"

using namespace std;

int main(int argc, char* argv[])
{
	string figure_name = argv[1];
	double fig_subplot = atof(argv[2]);
	string neuron_model = argv[3];
	int loop_iteration = atoi(argv[4]);
	int num_neurons = atoi(argv[5]);

	figure_control(figure_name,fig_subplot,neuron_model,loop_iteration);
	// paper_figure_control(figure_name,fig_subplot,neuron_model,loop_iteration,num_neurons);
}
