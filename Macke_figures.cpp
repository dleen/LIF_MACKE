#include "LIF_spike.h"

using namespace std;

char progress_bar(int percentage)
{
	// very basic progress bar - calculate how many iterations
	// the loop contains and then call this function every time
	// the current_iteration_value%(total_iterations/100) == 0
	string prog ("1%.......10%.......20%.......\
30%.......40%.......50%.......60%.......70%\
.......80%.......90%....100%");

	return prog[percentage];
}

void figure_1a_components(const parameters_t& XIF_params, string neuron_model,
int loop_iteration)
{
	LIF_spike S(5);

	//int k=0,m=0;
	double step = (XIF_params.upper_lim-XIF_params.lower_lim)/1000;

	if(loop_iteration < 0 || loop_iteration > 99) {
		cout << "Not a valid loop number!" << endl;
		exit(0);
	}

	int lower_loop=loop_iteration*10;
	int upper_loop=loop_iteration*10+10;

	// We loop over gamma from a very negative value
	// to a positive value - this is to ensure the variable
	// mu ranges from 0 to ~0.3
	/*cout << "Starting figure 1a using values:" << endl;
	cout << "Using Model: " << neuron_model << endl;
	cout << "Lambda = " << XIF_params.lambda << endl;
	cout << "Sigma  = " << XIF_params.sigma << endl;
	cout << "Gamma lower limit= " << XIF_params.lower_lim << endl;
	cout << "Gamma upper limit= " << XIF_params.upper_lim << endl;
	*/

	for(int i=lower_loop; i<upper_loop; ++i)
	{
		// repeat each point 100 times to be averaged later
		for(int j=0; j<5; ++j)
		{
			//cout << "Loop number = " << i+j << endl;
			S.seed_ran_gen(i+j);
			S.create_XIF_data(XIF_params.lower_lim+i*step,
					  XIF_params.lambda,
					  XIF_params.sigma,
					  neuron_model);
			S.print_statistics_to_file("fig_1a_"+neuron_model+"_",
			XIF_params.lambda,loop_iteration,i,j);
			S.zero_LIF_data();

			// display progress bar
			/*if(k%(1000*100/100) == 0)
			{
				cout << progress_bar(m++) << flush;
			}
			++k;*/
		}
	}
	//cout << endl;
}

void figure_1b_components(const parameters_t& XIF_params, string neuron_model, 
double subplot, int loop_iteration)
{
	LIF_spike S(5);

	//int k=0,m=0;
	double step = (XIF_params.upper_lim-XIF_params.lower_lim)/1000;

	if(loop_iteration < 0 || loop_iteration > 99) {
		cout << "Not a valid loop number!" << endl;
		exit(0);
	}

	int lower_loop=0;
	int upper_loop=1000;
	//int lower_loop=loop_iteration*10;
	//int upper_loop=loop_iteration*10+10;

	// 500 points along x-axis
	// we loop over lambda and hence over rho, while keeping
	// gamma constant
	/*cout << "Starting figure 1b using values:" << endl;
	cout << "Using Model: " << neuron_model << endl;
	cout << "Gamma = " << XIF_params.gamma << endl;
	cout << "Sigma  = " << XIF_params.sigma << endl;
	cout << "Lambda lower limit= " << XIF_params.lower_lim << endl;
	cout << "Lambda upper limit= " << XIF_params.upper_lim << endl;
	*/

        for(int i=lower_loop; i<upper_loop; ++i)
        {
		// repeat each point 50 times to be averaged later
                for(int j=0; j<5; ++j)
                {
			S.seed_ran_gen(i+j+2123987);
                        S.create_XIF_data(XIF_params.gamma,
					  XIF_params.lower_lim+i*step,
					  XIF_params.sigma,
					  neuron_model);
			S.print_statistics_to_file("fig_1b_"+neuron_model+"_",
			subplot,loop_iteration,i,j);
                        S.zero_LIF_data();

			// display progress bar so we can keep track
			/*if(k%(100*100/100) == 0)
			{
				cout << progress_bar(m++) << flush;
			}
			++k;*/
                }
        }
	//cout << endl;
}

void figure_2a_components(const parameters_t& XIF_params, string neuron_model,
double subplot, int loop_iteration)
{
	LIF_spike S(100);

	if(loop_iteration < 0 || loop_iteration > 99) {
		cout << "Not a valid loop number!" << endl;
		exit(0);
	}

	int lower_loop=loop_iteration*10;
	int upper_loop=loop_iteration*10+10;

	/*cout << "Starting figure 2a using values:" << endl;
	cout << "Using Model: " << neuron_model << endl;
	cout << "Lambda = " << XIF_params.lambda << endl;
	cout << "Sigma  = " << XIF_params.sigma << endl;
	*/
	// Varying lambda variable.

	for(int i=lower_loop; i<upper_loop; ++i)
	{
		S.seed_ran_gen(i+9872349);
                S.create_XIF_data(XIF_params.gamma,
				  XIF_params.lambda,
				  XIF_params.sigma,
				  neuron_model);
		S.print_statistics_to_file("fig_2a_"+neuron_model+"_",
		subplot,loop_iteration,i,0);
		S.zero_LIF_data();
		// display progress bar
		//cout << progress_bar(i) << flush;
	}
}

void create_figure_1a(double subplot, string neuron_model, int loop_iteration)
{
	parameters_t XIF_params = {0,0,0,0,0};

	double sigma_LIF = 4.38;
	double sigma_EIF = 4.149;

	if(subplot == 0.1) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){0,0.1,sigma_LIF,-57,-65};
			figure_1a_components(XIF_params,neuron_model,loop_iteration);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){0,0.1,sigma_EIF,-58,-65};
			figure_1a_components(XIF_params,neuron_model,loop_iteration);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){0,0.1,7.45,-10,-31};
			figure_1a_components(XIF_params,neuron_model,loop_iteration);
		}
	}
	else if(subplot == 0.3) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){0,0.3,sigma_LIF,-57,-65};
			figure_1a_components(XIF_params,neuron_model,loop_iteration);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){0,0.3,sigma_EIF,-58,-65};
			figure_1a_components(XIF_params,neuron_model,loop_iteration);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){0,0.3,7.45,-10,-31};
			figure_1a_components(XIF_params,neuron_model,loop_iteration);
		}
	}
	else if(subplot == 0.5) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){0,0.5,sigma_LIF,-57,-65};
			figure_1a_components(XIF_params,neuron_model,loop_iteration);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){0,0.5,sigma_EIF,-58,-65};
			figure_1a_components(XIF_params,neuron_model,loop_iteration);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){0,0.5,7.45,-10,-31};
			figure_1a_components(XIF_params,neuron_model,loop_iteration);
		}
	}
	else {
		cout << "Not a valid subplot value!" << endl;
	}
}

void create_figure_1b(double subplot, string neuron_model, int loop_iteration)
{
	parameters_t XIF_params = {0,0,0,0,0};

	double sigma_LIF = 4.38;
	double sigma_EIF = 4.149;

	if(subplot == 0.02) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){-61.53,0,sigma_LIF,0.9,0};
			figure_1b_components(XIF_params,neuron_model,subplot,
			loop_iteration);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){-61.74,0,sigma_EIF,0.9,0};
			figure_1b_components(XIF_params,neuron_model,subplot,
			loop_iteration);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){-21,0,7.45,0.9,0};
			figure_1b_components(XIF_params,neuron_model,subplot,
			loop_iteration);
		}
		else if(neuron_model == "DG") {
			XIF_params = (parameters_t){-2.05,0,0,0.9,0};
			figure_1b_components(XIF_params,neuron_model,subplot,
			loop_iteration);
		}
	}
	else if(subplot == 0.05) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){-60.67,0,sigma_LIF,0.9,0};
			figure_1b_components(XIF_params,neuron_model,subplot,
			loop_iteration);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){-61.05,0,sigma_EIF,0.9,0};
			figure_1b_components(XIF_params,neuron_model,subplot,
			loop_iteration);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){-18.4,0,7.45,0.94,0};
			figure_1b_components(XIF_params,neuron_model,subplot,
			loop_iteration);
		}
		else if(neuron_model == "DG") {
			XIF_params = (parameters_t){-1.64,0,0,0.9,0};
			figure_1b_components(XIF_params,neuron_model,subplot,
			loop_iteration);
		}
	}
	else if(subplot == 0.1) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){-59.945,0,sigma_LIF,0.9,0};
			figure_1b_components(XIF_params,neuron_model,subplot,
			loop_iteration);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){-60.48,0,sigma_EIF,0.9,0};
			figure_1b_components(XIF_params,neuron_model,subplot,
			loop_iteration);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){-16.05,0,7.45,0.9,0};
			figure_1b_components(XIF_params,neuron_model,subplot,
			loop_iteration);
		}
		else if(neuron_model == "DG") {
			XIF_params = (parameters_t){-1.25,0,0,0.9,0};
			figure_1b_components(XIF_params,neuron_model,subplot,
			loop_iteration);
		}

	}
	else if(subplot == 0.2) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){-59.06,0,sigma_LIF,0.9,0};
			figure_1b_components(XIF_params,neuron_model,subplot,
			loop_iteration);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){-59.8,0,sigma_EIF,0.9,0};
			figure_1b_components(XIF_params,neuron_model,subplot,
			loop_iteration);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){-13.8,0,7.45,0.9,0};
			figure_1b_components(XIF_params,neuron_model,subplot,
			loop_iteration);
		}
		else if(neuron_model == "DG") {
			XIF_params = (parameters_t){-0.84,0,0,0.9,0};
			figure_1b_components(XIF_params,neuron_model,subplot,
			loop_iteration);
		}
	}
	else {
		cout << "Not a valid subplot value!" << endl;
	}
}

void create_figure_2a(double subplot, std::string neuron_model, int loop_iteration)
{
	parameters_t XIF_params = {0,0,0,0,0};

	double sigma_LIF = 4.38;
	double sigma_EIF = 4.149;

	if(subplot == 0.05) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){-59.945,0.345,sigma_LIF,0,0};
			figure_2a_components(XIF_params,neuron_model,subplot,
			loop_iteration);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){-60.48,0.27,sigma_EIF,0,0};
			figure_2a_components(XIF_params,neuron_model,subplot,
			loop_iteration);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){-16.05,0,7.45,0,0};
			figure_2a_components(XIF_params,neuron_model,subplot,
			loop_iteration);
		}
	}
	else if(subplot == 0.1) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){-59.945,0.48,sigma_LIF,0,0};
			figure_2a_components(XIF_params,neuron_model,subplot,
			loop_iteration);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){-60.48,0.42,sigma_EIF,0,0};
			figure_2a_components(XIF_params,neuron_model,subplot,
			loop_iteration);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){-16.05,0,7.45,0,0};
			figure_2a_components(XIF_params,neuron_model,subplot,
			loop_iteration);
		}
	}
	else if(subplot == 0.25) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){-59.945,0.72,sigma_LIF,0,0};
			figure_2a_components(XIF_params,neuron_model,subplot,
			loop_iteration);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){-60.48,0.68,sigma_EIF,0,0};
			figure_2a_components(XIF_params,neuron_model,subplot,
			loop_iteration);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){-16.05,0,7.45,0,0};
			figure_2a_components(XIF_params,neuron_model,subplot,
			loop_iteration);
		}
	}
	else {
		cout << "Not a valid subplot value!" << endl;
	}
}

void figure_control(string figure_name, double subplot, string neuron_model,
int loop_iteration)
{
	if(figure_name == "fig1a") {
		create_figure_1a(subplot,neuron_model,loop_iteration);
	}
	else if(figure_name == "fig1b") {
		create_figure_1b(subplot,neuron_model,loop_iteration);
	}
	else if(figure_name == "fig2a") {
		create_figure_2a(subplot,neuron_model,loop_iteration);
	}
	else if(figure_name == "fig3") {

	}
	else {
		cout << "Not a valid figure name!" << endl;
	}
}
