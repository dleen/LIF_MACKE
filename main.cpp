#include "LIF_constants.h"
#include "LIF_spike.h"

using namespace std;

int main(int argc, char* argv[])
{
	// To create the figures:
	// Probably best to run just one at a time
	// Usually takes 30mins per figure
	//create_figure_1a();
	//create_figure_1b();
	//create_figure_2a("LIF");

	// To work with just a single LIF_spike unit:
	// Create the LIF_spike container
	//LIF_spike Y(5);

	//string neuron_model = argv[3];

	// Run LIF simulation and calculate statistics
	// Definition: Spike.create_LIF_data(gamma,lambda,sigma);
	//Y.create_XIF_data(atof(argv[1]),0.3,atof(argv[2]),neuron_model);
	//Y.create_QIF_data(-15,0.2,7.25);

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
