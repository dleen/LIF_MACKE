#include "LIF_spike.h"

using namespace std;

int main(int argc, char* argv[])
{
	// To work with just a single LIF_spike unit:
	// Create the LIF_spike container
	//LIF_spike Y(5);
/*	LIF_spike Y(atoi(argv[5]));

	string neuron_model = argv[4];

	//int tid=0, nthreads=0;
	// Run LIF simulation and calculate statistics
	// Definition: Spike.create_LIF_data(gamma,lambda,sigma);
	//Y.create_XIF_data(-12.405,0.1,0.74,"EIF");
	Y.create_XIF_data(atof(argv[1]),atof(argv[2]),atof(argv[3]),neuron_model);
	Y.print_statistics();
*/
	string figure_name = argv[1];
	double fig_subplot = atof(argv[2]);
	string neuron_model = argv[3];
	int loop_iteration = atoi(argv[4]);

	// Run the program with the options:
	// spike.out fig1a 0.1 LIF
	figure_control(figure_name,fig_subplot,neuron_model,loop_iteration);
}
