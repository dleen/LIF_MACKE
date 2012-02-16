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

void figure_1a_components(LIF_spike& S, double lambda, double sigma, double gam_low, 
double gam_upp, string neuron_model)
{
	int k=0,m=0;
	double step = (gam_upp-gam_low)/1000;

	// We loop over gamma from a very negative value
	// to a positive value - this is to ensure the variable
	// mu ranges from 0 to ~0.3
	cout << "Starting figure 1a using values:" << endl;
	cout << "Using Model: " << neuron_model << endl;
	cout << "Lambda = " << lambda << endl;
	cout << "Sigma  = " << sigma << endl;
	cout << "Gamma lower limit= " << gam_low << endl;
	cout << "Gamma upper limit= " << gam_upp << endl;

	for(int i=0; i<1000; ++i)
	{
		// repeat each point 100 times to be averaged later
		for(int j=0; j<10; ++j)
		{
			S.create_XIF_data(gam_low+i*step,lambda,sigma,neuron_model);
			S.print_statistics_to_file("figure_1a_"+neuron_model+"_",
						   lambda);
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

void figure_1b_components(LIF_spike& S, double lam_low, double lam_upp,
double sigma, double gamma, string neuron_model, double subplot)
{
	int k=0,m=0;
	double step = (lam_upp-lam_low)/1000;

	// 500 points along x-axis
	// we loop over lambda and hence over rho, while keeping
	// gamma constant
	cout << "Starting figure 1b using values:" << endl;
	cout << "Using Model: " << neuron_model << endl;
	cout << "Gamma = " << gamma << endl;
	cout << "Sigma  = " << sigma << endl;
	cout << "Lambda lower limit= " << lam_low << endl;
	cout << "Lambda upper limit= " << lam_upp << endl;

        for(int i=0; i<1000; ++i)
        {
		// repeat each point 50 times to be averaged later
                for(int j=0; j<100; ++j)
                {
                        S.create_XIF_data(gamma,lam_low+i*step,sigma,neuron_model);
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

	double sigma=0;
	double lambda=0;
	double gam_low=0;
	double gam_upp=0;

	if(subplot == 0.1) {
		lambda = 0.1;
		if(neuron_model == "LIF") {
			sigma = 2.08;
			gam_low = -65;
			gam_upp = -58;
			figure_1a_components(S,lambda,sigma,gam_low,
					     gam_upp,neuron_model);
		}
		else if(neuron_model == "EIF") {
			sigma = 0.74;
			gam_low = -12.6;
			gam_upp = -12.275;
			figure_1a_components(S,lambda,sigma,gam_low,
					     gam_upp,neuron_model);
		}
		else if(neuron_model == "QIF") {
			sigma = 7.4;
			gam_low = -31;
			gam_upp = -10;
			figure_1a_components(S,lambda,sigma,gam_low,
					     gam_upp,neuron_model);
		}
	}
	else if(subplot == 0.3) {
		lambda = 0.3;
		if(neuron_model == "LIF") {
			sigma = 2.08;
			gam_low = -65;
			gam_upp = -58;
			figure_1a_components(S,lambda,sigma,gam_low,
					     gam_upp,neuron_model);
		}
		else if(neuron_model == "EIF") {
			sigma = 0.74;
			gam_low = -12.6;
			gam_upp = -12.275;
			figure_1a_components(S,lambda,sigma,gam_low,
					     gam_upp,neuron_model);
		}
		else if(neuron_model == "QIF") {
			sigma = 7.4;
			gam_low = -31;
			gam_upp = -10;
			figure_1a_components(S,lambda,sigma,gam_low,
					     gam_upp,neuron_model);
		}
	}
	else if(subplot == 0.5) {
		lambda = 0.5;
		if(neuron_model == "LIF") {
			sigma = 2.08;
			gam_low = -65;
			gam_upp = -58;
			figure_1a_components(S,lambda,sigma,gam_low,
					     gam_upp,neuron_model);
		}
		else if(neuron_model == "EIF") {
			sigma = 0.74;
			gam_low = -12.6;
			gam_upp = -12.275;
			figure_1a_components(S,lambda,sigma,gam_low,
					     gam_upp,neuron_model);
		}
		else if(neuron_model == "QIF") {
			sigma = 7.25;
			gam_low = -31;
			gam_upp = -10;
			figure_1a_components(S,lambda,sigma,gam_low,
					     gam_upp,neuron_model);
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

	if(subplot == 0.02) {
		if(neuron_model == "LIF") {
			sigma = 2.08;
			gamma = -62.23;
			lam_low = 0;
			lam_upp = 0.9;
			figure_1b_components(S,lam_low,lam_upp,sigma,gamma,
					     neuron_model,subplot);
		}
		else if(neuron_model == "EIF") {
			sigma = 0.74;
			gamma = -12.49;
			lam_low = 0;
			lam_upp = 0.9;
			figure_1b_components(S,lam_low,lam_upp,sigma,gamma,
					     neuron_model,subplot);
		}
		else if(neuron_model == "QIF") {
			sigma = 7.4;
			gamma = -21;
			lam_low = 0;
			lam_upp = 0.9;
			figure_1b_components(S,lam_low,lam_upp,sigma,gamma,
					     neuron_model,subplot);
		}
	}
	else if(subplot == 0.05) {
		if(neuron_model == "LIF") {
			sigma = 2.08;
			gamma = -61.25;
			lam_low = 0;
			lam_upp = 0.9;
			figure_1b_components(S,lam_low,lam_upp,sigma,gamma,
					     neuron_model,subplot);
		}
		else if(neuron_model == "EIF") {
			sigma = 0.74;
			gamma = -12.44;
			lam_low = 0;
			lam_upp = 0.9;
			figure_1b_components(S,lam_low,lam_upp,sigma,gamma,
					     neuron_model,subplot);
		}
		else if(neuron_model == "QIF") {
			sigma = 7.4;
			gamma = -18.4;
			lam_low = 0;
			lam_upp = 0.94;
			figure_1b_components(S,lam_low,lam_upp,sigma,gamma,
					     neuron_model,subplot);
		}
	}
	else if(subplot == 0.1) {
		if(neuron_model == "LIF") {
			sigma = 2.08;
			gamma = -60.5;
			lam_low = 0;
			lam_upp = 0.9;
			figure_1b_components(S,lam_low,lam_upp,sigma,gamma,
					     neuron_model,subplot);
		}
		else if(neuron_model == "EIF") {
			sigma = 0.74;
			gamma = -12.405;
			lam_low = 0;
			lam_upp = 0.9;
			figure_1b_components(S,lam_low,lam_upp,sigma,gamma,
					     neuron_model,subplot);
		}
		else if(neuron_model == "QIF") {
			sigma = 7.4;
			gamma = -16.05;
			lam_low = 0;
			lam_upp = 0.9;
			figure_1b_components(S,lam_low,lam_upp,sigma,gamma,
					     neuron_model,subplot);
		}

	}
	else if(subplot == 0.2) {
		if(neuron_model == "LIF") {
			sigma = 2.08;
			gamma = -59.62;
			lam_low = 0;
			lam_upp = 0.9;
			figure_1b_components(S,lam_low,lam_upp,sigma,gamma,
					     neuron_model,subplot);
		}
		else if(neuron_model == "EIF") {
			sigma = 0.74;
			gamma = -12.36;
			lam_low = 0;
			lam_upp = 0.9;
			figure_1b_components(S,lam_low,lam_upp,sigma,gamma,
					     neuron_model,subplot);
		}
		else if(neuron_model == "QIF") {
			sigma = 7.4;
			gamma = -13.8;
			lam_low = 0;
			lam_upp = 0.9;
			figure_1b_components(S,lam_low,lam_upp,sigma,gamma,
					     neuron_model,subplot);
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
	if(figure_name == "fig1a")
	{
		create_figure_1a(subplot,neuron_model);
	}
	else if(figure_name == "fig1b")
	{
		create_figure_1b(subplot,neuron_model);
	}
	else if(figure_name == "fig2a")
	{
		create_figure_2a(subplot,neuron_model);
	}
	else if(figure_name == "fig3")
	{

	}
	else
	{
		cout << "Not a valid figure name!" << endl;
	}


}

