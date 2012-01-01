#include "LIF_constants.h"
#include "LIF_spike.h"

int main()
{
	// Each of the lines in figure_1b
	//0.65 for 0.2
	//0.18 for 0.1
	//-0.07 for 0.05
	//-0.3 for 0.02
	LIF_spike X(5);
	cout << "0.65 Figure starting:" << endl;
	X.create_figure_1b(0.65);
	cout << "0.18 Figure starting:" << endl;
	X.create_figure_1b(0.18);
	cout << "-0.07 Figure starting:" << endl;
	X.create_figure_1b(-0.07);
	cout << "-0.3 Figure starting:" << endl;
	X.create_figure_1b(-0.3);

//	LIF_spike X(5);
//	X.create_figure_1b(0.65);
/*
	LIF_spike Y(7);
	Y.create_LIF_data(-0.3,0.002);
	Y.print_statistics();
	Y.zero_LIF_data();
	Y.print_statistics();
*/
}
