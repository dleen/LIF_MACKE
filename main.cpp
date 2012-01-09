#include "LIF_constants.h"
#include "LIF_spike.h"

#include "Macke_figures.h"

using namespace std;

int main()
{

//	create_figure_1b();

	LIF_spike Y(5);
	Y.create_LIF_data(-2.25,0.7);
	Y.print_statistics();

}
