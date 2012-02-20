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

void figure_1a_components(const parameters_t& XIF_params, string neuron_model)
//void figure_1a_components(LIF_spike& S,double lambda, double sigma, double gam_low, 
//double gam_upp, string neuron_model)
{
	LIF_spike S(5);

	int k=0,m=0;
	double step = (XIF_params.upper_lim-XIF_params.lower_lim)/1000;

	// We loop over gamma from a very negative value
	// to a positive value - this is to ensure the variable
	// mu ranges from 0 to ~0.3
	cout << "Starting figure 1a using values:" << endl;
	cout << "Using Model: " << neuron_model << endl;
	cout << "Lambda = " << XIF_params.lambda << endl;
	cout << "Sigma  = " << XIF_params.sigma << endl;
	cout << "Gamma lower limit= " << XIF_params.lower_lim << endl;
	cout << "Gamma upper limit= " << XIF_params.upper_lim << endl;

	#pragma omp parallel for private(S) //shared(k,m)
	for(int i=0; i<1000; ++i)
	{
		// repeat each point 100 times to be averaged later
		for(int j=0; j<50; ++j)
		{
			//cout << "Loop number = " << i+j << endl;
			S.seed_ran_gen(i+j);
			S.create_XIF_data(XIF_params.lower_lim+i*step,
					  XIF_params.lambda,
					  XIF_params.sigma,
					  neuron_model);
			S.print_statistics_to_file("figure_1a_"+neuron_model+"_",
						   XIF_params.lambda);
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

void figure_1b_components(const parameters_t& XIF_params,
string neuron_model, double subplot)
{
	LIF_spike S(5);

	int k=0,m=0;
	double step = (XIF_params.upper_lim-XIF_params.lower_lim)/1000;

	// 500 points along x-axis
	// we loop over lambda and hence over rho, while keeping
	// gamma constant
	cout << "Starting figure 1b using values:" << endl;
	cout << "Using Model: " << neuron_model << endl;
	cout << "Gamma = " << XIF_params.gamma << endl;
	cout << "Sigma  = " << XIF_params.sigma << endl;
	cout << "Lambda lower limit= " << XIF_params.lower_lim << endl;
	cout << "Lambda upper limit= " << XIF_params.upper_lim << endl;

	#pragma omp parallel for private(S) //shared(k,m)
        for(int i=0; i<1000; ++i)
        {
		// repeat each point 50 times to be averaged later
                for(int j=0; j<50; ++j)
                {
			S.seed_ran_gen(i+j+2123987);
                        S.create_XIF_data(XIF_params.gamma,
					  XIF_params.lower_lim+i*step,
					  XIF_params.sigma,
					  neuron_model);
                        S.print_statistics_to_file("figure_1b_"+neuron_model+"_",
						   subplot);
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
double subplot)
{
	LIF_spike S(100);

	cout << "Starting figure 2a using values:" << endl;
	cout << "Using Model: " << neuron_model << endl;
	cout << "Lambda = " << XIF_params.lambda << endl;
	cout << "Sigma  = " << XIF_params.sigma << endl;
	// Varying lambda variable.
	#pragma omp parallel for private(S)
	for(int i=0; i<300; ++i)
	{
		S.seed_ran_gen(i+9872349);
                S.create_XIF_data(XIF_params.gamma,
				  XIF_params.lambda,
				  XIF_params.sigma,
				  neuron_model);
		S.print_statistics_to_file("figure_2a_"+neuron_model+"_",
					   subplot);
		S.zero_LIF_data();
		// display progress bar
		//cout << progress_bar(i) << flush;
	}
}

void create_figure_1a(double subplot, string neuron_model)
{
	parameters_t XIF_params = {0,0,0,0,0};

	if(subplot == 0.1) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){0,0.1,2.08,-58,-65};
			figure_1a_components(XIF_params,neuron_model);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){0,0.1,0.74,-12.275,-12.6};
			figure_1a_components(XIF_params,neuron_model);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){0,0.1,7.4,-10,-31};
			figure_1a_components(XIF_params,neuron_model);
		}
	}
	else if(subplot == 0.3) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){0,0.3,2.08,-58,-65};
			figure_1a_components(XIF_params,neuron_model);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){0,0.3,0.74,-12.275,-12.6};
			figure_1a_components(XIF_params,neuron_model);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){0,0.3,7.4,-10,-31};
			figure_1a_components(XIF_params,neuron_model);
		}
	}
	else if(subplot == 0.5) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){0,0.5,2.08,-58,-65};
			figure_1a_components(XIF_params,neuron_model);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){0,0.5,0.74,-12.275,-12.6};
			figure_1a_components(XIF_params,neuron_model);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){0,0.5,7.4,-10,-31};
			figure_1a_components(XIF_params,neuron_model);
		}
	}
	else {
		cout << "Not a valid subplot value!" << endl;
	}
}

void create_figure_1b(double subplot, string neuron_model)
{
	parameters_t XIF_params = {0,0,0,0,0};

	if(subplot == 0.02) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){-62.23,0,2.08,0.9,0};
			figure_1b_components(XIF_params,neuron_model,subplot);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){-12.49,0,0.74,0.9,0};
			figure_1b_components(XIF_params,neuron_model,subplot);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){-21,0,7.4,0.9,0};
			figure_1b_components(XIF_params,neuron_model,subplot);
		}
	}
	else if(subplot == 0.05) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){-61.25,0,2.08,0.9,0};
			figure_1b_components(XIF_params,neuron_model,subplot);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){-12.44,0,0.74,0.9,0};
			figure_1b_components(XIF_params,neuron_model,subplot);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){-18.4,0,7.4,0.94,0};
			figure_1b_components(XIF_params,neuron_model,subplot);
		}
	}
	else if(subplot == 0.1) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){-60.5,0,2.08,0.9,0};
			figure_1b_components(XIF_params,neuron_model,subplot);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){-12.405,0,0.74,0.9,0};
			figure_1b_components(XIF_params,neuron_model,subplot);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){-16.05,0,7.4,0.9,0};
			figure_1b_components(XIF_params,neuron_model,subplot);
		}

	}
	else if(subplot == 0.2) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){-59.62,0,2.08,0.9,0};
			figure_1b_components(XIF_params,neuron_model,subplot);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){-12.36,0,0.74,0.9,0};
			figure_1b_components(XIF_params,neuron_model,subplot);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){-13.8,0,7.4,0.9,0};
			figure_1b_components(XIF_params,neuron_model,subplot);
		}
	}
	else {
		cout << "Not a valid subplot value!" << endl;
	}
}

void create_figure_2a(double subplot, std::string neuron_model)
{
	parameters_t XIF_params = {0,0,0,0,0};

	if(subplot == 0.05) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){-60.5,0.33,2.08,0,0};
			figure_2a_components(XIF_params,neuron_model,subplot);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){-12.405,0,0.74,0,0};
			figure_2a_components(XIF_params,neuron_model,subplot);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){-16.05,0,7.4,0,0};
			figure_2a_components(XIF_params,neuron_model,subplot);
		}
	}
	else if(subplot == 0.1) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){-60.5,0.5,2.08,0,0};
			figure_2a_components(XIF_params,neuron_model,subplot);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){-12.405,0,0.74,0,0};
			figure_2a_components(XIF_params,neuron_model,subplot);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){-16.05,0,7.4,0,0};
			figure_2a_components(XIF_params,neuron_model,subplot);
		}
	}
	else if(subplot == 0.25) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){-60.5,0.73,2.08,0,0};
			figure_2a_components(XIF_params,neuron_model,subplot);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){-12.405,0,0.74,0,0};
			figure_2a_components(XIF_params,neuron_model,subplot);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){-16.05,0,7.4,0,0};
			figure_2a_components(XIF_params,neuron_model,subplot);
		}
	}
	else {
		cout << "Not a valid subplot value!" << endl;
	}
}

void figure_control(string figure_name, double subplot, string neuron_model)
{
	if(figure_name == "fig1a") {
		create_figure_1a(subplot,neuron_model);
	}
	else if(figure_name == "fig1b") {
		create_figure_1b(subplot,neuron_model);
	}
	else if(figure_name == "fig2a") {
		create_figure_2a(subplot,neuron_model);
	}
	else if(figure_name == "fig3") {

	}
	else {
		cout << "Not a valid figure name!" << endl;
	}
}

