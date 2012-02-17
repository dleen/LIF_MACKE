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

void figure_1a_components(LIF_spike& S, const parameters_t& XIF_params, 
string neuron_model)
//void figure_1a_components(LIF_spike& S,double lambda, double sigma, double gam_low, 
//double gam_upp, string neuron_model)
{
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

	for(int i=0; i<1000; ++i)
	{
		// repeat each point 100 times to be averaged later
		for(int j=0; j<10; ++j)
		{
			S.create_XIF_data(XIF_params.lower_lim+i*step,
					  XIF_params.lambda,
					  XIF_params.sigma,neuron_model);
			S.print_statistics_to_file("figure_1a_"+neuron_model+"_",
						   XIF_params.lambda);
			S.zero_LIF_data();
			// display progress bar
			if(k%(1000*10/100) == 0)
			{
				cout << progress_bar(m++) << flush;
			}
			++k;
		}
	}
	cout << endl;
}

void figure_1b_components(LIF_spike& S, const parameters_t& XIF_params,
string neuron_model, double subplot)
{
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

        for(int i=0; i<1000; ++i)
        {
		// repeat each point 50 times to be averaged later
                for(int j=0; j<100; ++j)
                {
                        S.create_XIF_data(XIF_params.gamma,
					  XIF_params.lower_lim+i*step,
					  XIF_params.sigma,neuron_model);
                        S.print_statistics_to_file("figure_1b_"+neuron_model+"_",
						   subplot);
                        S.zero_LIF_data();

			// display progress bar so we can keep track
			if(k%(1000*100/100) == 0)
			{
				cout << progress_bar(m++) << flush;
			}
			++k;
                }
        }
	cout << endl;
}

void figure_2a_components(LIF_spike& S, double lambda, double sigma, string neuron_model)
{
	// gamma = -4.5 for mu ~ 0.1
	// run 100 times to be averaged later
	if(neuron_model == "LIF") {
		cout << "Using LIF Model" << endl;
		cout << "Starting figure using values:" << endl;
		cout << "Lambda = " << lambda << endl;
		cout << "Sigma  = " << sigma << endl;
		for(int i=0; i<100; ++i)
		{
			// LIF version
			//S.create_LIF_data(-60.5,lambda,2.08);
			S.print_statistics_to_file("figure_2a_LIF_",lambda);
			S.zero_LIF_data();
			// display progress bar
			cout << progress_bar(i) << flush;
		}
		cout << endl;
	}
	else if(neuron_model == "EIF") {
		cout << "Using EIF Model" << endl;
		cout << "Starting figure using values:" << endl;
		cout << "Lambda = " << lambda << endl;
		cout << "Sigma  = " << sigma << endl;
		for(int i=0; i<100; ++i)
		{
			// EIF version
			//S.create_EIF_data(-12.4,lambda,0.74);
			S.print_statistics_to_file("figure_2a_EIF_",lambda);
			S.zero_LIF_data();
			// display progress bar
			cout << progress_bar(i) << flush;
		}
		cout << endl;
	}
	else if(neuron_model == "QIF") {
		cout << "Using QIF Model" << endl;
		cout << "Starting figure using values:" << endl;
		cout << "Lambda = " << lambda << endl;
		cout << "Sigma  = " << sigma << endl;
		for(int i=0; i<100; ++i)
		{
			// QIF version
			//S.create_QIF_data(-15,lambda,7.25);
			S.print_statistics_to_file("figure_2a_QIF_",lambda);
			S.zero_LIF_data();
			// display progress bar
			cout << progress_bar(i) << flush;
		}
		cout << endl;
	}
}

void create_figure_1a(double subplot, string neuron_model)
{
	LIF_spike S(5);

	parameters_t XIF_params = {0,0,0,0,0};

	if(subplot == 0.1) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){0,0.1,2.08,-58,-65};
			figure_1a_components(S,XIF_params,neuron_model);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){0,0.1,0.74,-12.275,-12.6};
			figure_1a_components(S,XIF_params,neuron_model);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){0,0.1,7.4,-10,-31};
			figure_1a_components(S,XIF_params,neuron_model);
		}
	}
	else if(subplot == 0.3) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){0,0.3,2.08,-58,-65};
			figure_1a_components(S,XIF_params,neuron_model);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){0,0.3,0.74,-12.275,-12.6};
			figure_1a_components(S,XIF_params,neuron_model);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){0,0.3,7.4,-10,-31};
			figure_1a_components(S,XIF_params,neuron_model);
		}
	}
	else if(subplot == 0.5) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){0,0.5,2.08,-58,-65};
			figure_1a_components(S,XIF_params,neuron_model);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){0,0.5,0.74,-12.275,-12.6};
			figure_1a_components(S,XIF_params,neuron_model);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){0,0.5,7.4,-10,-31};
			figure_1a_components(S,XIF_params,neuron_model);
		}
	}
	else {
		cout << "Not a valid subplot value!" << endl;
	}
}

void create_figure_1b(double subplot, string neuron_model)
{
        LIF_spike S(5);

	double sigma=0;
	double gamma=0;
	double lam_low=0;
	double lam_upp=0;

	parameters_t XIF_params = {0,0,0,0,0};

	if(subplot == 0.02) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){-62.23,0,2.08,0.9,0};
			figure_1b_components(S,XIF_params,neuron_model,subplot);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){-12.49,0,0.74,0.9,0};
			figure_1b_components(S,XIF_params,neuron_model,subplot);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){-21,0,7.4,0.9,0};
			figure_1b_components(S,XIF_params,neuron_model,subplot);
		}
	}
	else if(subplot == 0.05) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){-61.25,0,2.08,0.9,0};
			figure_1b_components(S,XIF_params,neuron_model,subplot);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){-12.44,0,0.74,0.9,0};
			figure_1b_components(S,XIF_params,neuron_model,subplot);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){-18.4,0,7.4,0.94,0};
			figure_1b_components(S,XIF_params,neuron_model,subplot);
		}
	}
	else if(subplot == 0.1) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){-60.5,0,2.08,0.9,0};
			figure_1b_components(S,XIF_params,neuron_model,subplot);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){-12.405,0,0.74,0.9,0};
			figure_1b_components(S,XIF_params,neuron_model,subplot);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){-16.05,0,7.4,0.9,0};
			figure_1b_components(S,XIF_params,neuron_model,subplot);
		}

	}
	else if(subplot == 0.2) {
		if(neuron_model == "LIF") {
			XIF_params = (parameters_t){-59.62,0,2.08,0.9,0};
			figure_1b_components(S,XIF_params,neuron_model,subplot);
		}
		else if(neuron_model == "EIF") {
			XIF_params = (parameters_t){-12.36,0,0.74,0.9,0};
			figure_1b_components(S,XIF_params,neuron_model,subplot);
		}
		else if(neuron_model == "QIF") {
			XIF_params = (parameters_t){-13.8,0,7.4,0.9,0};
			figure_1b_components(S,XIF_params,neuron_model,subplot);
		}
	}
	else {
		cout << "Not a valid subplot value!" << endl;
	}
}

void create_figure_2a(double subplot, std::string neuron_model)
{
	LIF_spike S(100);

        // Each of the lines in figure_2a
	// lambda = 0.325 for rho ~ 0.05
	//figure_2a_components(S,0.325,2.08);
	figure_2a_components(S,0.26,0.74,neuron_model);

	// lambda = 0.49 for rho ~ 0.1
	//figure_2a_components(S,0.49,2.08);
	figure_2a_components(S,0.39,0.74,neuron_model);

	// lambda = 0.73 for rho ~ 0.25
	//figure_2a_components(S,0.73,2.08);
	figure_2a_components(S,0.64,0.74,neuron_model);
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

