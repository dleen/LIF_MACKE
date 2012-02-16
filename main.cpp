#include "LIF_constants.h"
#include "LIF_spike.h"

using namespace std;

int main(int argc, char* argv[])
{
	// To work with just a single LIF_spike unit:
	// Create the LIF_spike container
	//LIF_spike Y(5);

	//string neuron_model = argv[4];

	// Run LIF simulation and calculate statistics
	// Definition: Spike.create_LIF_data(gamma,lambda,sigma);
	//Y.create_XIF_data(atof(argv[1]),atof(argv[2]),atof(argv[3]),neuron_model);

	// Print the data to terminal
	//Y.print_statistics();

	// Reset the data to zero, ready for reuse
	//Y.zero_LIF_data();

	//cout << "argc = " << argc << endl; 
	//for(int i = 0; i < argc; ++i) 
	//{
	//	cout << "argv[" << i << "] = " << argv[i] << endl; 
	//}

	string figure_name = argv[1];
	double fig_subplot = atof(argv[2]);
	string neuron_model = argv[3];
	//cout << figure_name << endl;
	//cout << fig_subplot << endl;
	//cout << neuron_model << endl;

	// Run the program with the options:
	// spike.out fig1a 0.1 LIF
	figure_control(figure_name,fig_subplot,neuron_model);

}
