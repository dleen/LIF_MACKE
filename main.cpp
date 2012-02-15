#include "LIF_constants.h"
#include "LIF_spike.h"

using namespace std;

int main()
{
	// To create the figures:
	// Probably best to run just one at a time
	// Usually takes 30mins per figure
	//create_figure_1a();
	//create_figure_1b();
	//create_figure_2a("LIF");

	// To work with just a single LIF_spike unit:
	// Create the LIF_spike container
	LIF_spike Y(5);

	// Run LIF simulation and calculate statistics
	// Definition: Spike.create_LIF_data(gamma,lambda,sigma);
	//Y.create_LIF_data(-60.5,0.5,2.08);
	Y.create_QIF_data(-15,0.2,7.25);

	// Print the data to terminal
	Y.print_statistics();

	// Reset the data to zero, ready for reuse
	//Y.zero_LIF_data();
}
