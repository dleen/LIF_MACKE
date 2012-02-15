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

void figure_1a_components(LIF_spike& S, double lambda, double sigma)
{
	int k=0,m=0;

	// we loop over gamma from a very negative value
	// to a positive value - this is to ensure the variable
	// mu ranges from 0 to ~0.3
	for(int i=-700; i<100; ++i)
	{
		// repeat each point 100 times to be averaged later
		for(int j=0; j<100; ++j)
		{
			S.create_LIF_data(i*0.02,lambda,sigma)	;
			S.print_statistics_to_file("figure_1a_",lambda);
			S.zero_LIF_data();

			// display progress bar
			if(k%(800*100/100) == 0)
			{
				cout << progress_bar(m++) << flush;
			}
			++k;
		}
	}
	cout << endl;
}

void figure_1b_components(LIF_spike& S, double gamma, double sigma)
{
	int k=0,m=0;

	// 500 points along x-axis
	// we loop over lambda and hence over rho, while keeping
	// gamma constant
        for(int i=0; i<500; ++i)
        {
		// repeat each point 50 times to be averaged later
                for(int j=0; j<50; ++j)
                {
                        S.create_LIF_data(gamma,i*0.00168,sigma);
                        S.print_statistics_to_file("figure_1b_",gamma);
                        S.zero_LIF_data();

			// display progress bar so we can keep track
			if(k%(500*50/100) == 0)
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
			S.create_LIF_data(-60.5,lambda,2.08);
			S.print_statistics_to_file("figure_2a_LIF_",lambda);
			S.zero_LIF_data();
			// display progress bar
			cout << progress_bar(i) << flush;
		}
	}
	else if(neuron_model == "EIF") {
		cout << "Using EIF Model" << endl;
		cout << "Starting figure using values:" << endl;
		cout << "Lambda = " << lambda << endl;
		cout << "Sigma  = " << sigma << endl;
		for(int i=0; i<100; ++i)
		{
			// EIF version
			S.create_EIF_data(-12.4,lambda,0.74);
			S.print_statistics_to_file("figure_2a_EIF_",lambda);
			S.zero_LIF_data();
			// display progress bar
			cout << progress_bar(i) << flush;
		}
	}
	else if(neuron_model == "QIF") {
		cout << "Using EIF Model" << endl;
		cout << "Starting figure using values:" << endl;
		cout << "Lambda = " << lambda << endl;
		cout << "Sigma  = " << sigma << endl;
		for(int i=0; i<100; ++i)
		{
			// QIF version
			S.create_QIF_data(-15,lambda,7.25);
			S.print_statistics_to_file("figure_2a_QIF_",lambda);
			S.zero_LIF_data();
			// display progress bar
			cout << progress_bar(i) << flush;
		}
	}

	cout << endl;
}

void create_figure_1a()
{
	LIF_spike S(5);

        // Each of the lines in figure_1a
	// lambda = 0.1
	figure_1a_components(S,0.1,10);

	// lambda = 0.3
	figure_1a_components(S,0.3,10);

	// lambda = 0.5
	figure_1a_components(S,0.5,10);
}

void create_figure_1b()
{
        LIF_spike S(5);

        // Each of the lines in figure_1b
        // gamma = -59.65 for mu ~ 0.2
        cout << "-2.25 Figure starting:" << endl;
	figure_1b_components(S,-59.65,2.08);

        // gamma = -60.5 for mu ~ 0.1
        cout << "-4.5 Figure starting:" << endl;
	figure_1b_components(S,-60.5,2.08);

        // gamma = -61.2 for mu ~ 0.05
        cout << "-6.5 Figure starting:" << endl;
	figure_1b_components(S,-61.2,2.08);

        // gamma = -62 for mu ~ 0.02
        cout << "-8.25 Figure starting:" << endl;
	figure_1b_components(S,-62,2.08);
}

void create_figure_2a(std::string neuron_model)
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
