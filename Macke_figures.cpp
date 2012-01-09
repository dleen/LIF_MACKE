#include "LIF_spike.h"

using namespace std;

char LIF_spike::progress_bar(int percentage)
{
	string prog ("1%.......10%.......20%.......\
30%.......40%.......50%.......60%.......70%\
.......80%.......90%....100%");

	return prog[percentage];
}

void LIF_spike::figure_1a_components(double lambda)
{
	int k=0,m=0;

	for(int i=-700; i<100; ++i)
	{
		for(int j=0; j<5; ++j)
		{
			create_LIF_data(i*0.02,lambda)	;
			print_statistics_to_file("figure_1a_",lambda);
			zero_LIF_data();

			if(k%(800*5/100) == 0)
			{
				cout << progress_bar(m++) << flush;
			}
			++k;
		}
	}
	cout << endl;
}

void LIF_spike::figure_1b_components(double gamma)
{
	int k=0,m=0;

        for(int i=0; i<500; ++i)
        {
                for(int j=0; j<50; ++j)
                {
                        create_LIF_data(gamma,i*0.002);
                        print_statistics_to_file("figure_1b_",gamma);
                        zero_LIF_data();

			if(k%(500*50/100) == 0)
			{
				cout << progress_bar(m++) << flush;
			}
			++k;
                }
        }
	cout << endl;
}

void LIF_spike::figure_2a_components(double lambda)
{
	// gamma = 0.18 for mu ~ 0.1
	for(int i=0; i<100; ++i)
	{
		create_LIF_data(0.18,lambda);
		print_statistics_to_file("figure_2a_",lambda);
		zero_LIF_data();
		cout << progress_bar(i) << flush;
	}
	cout << endl;
}

void create_figure_1a()
{
	LIF_spike X(5);

	X.figure_1a_components(0.1);

	X.figure_1a_components(0.3);

	X.figure_1a_components(0.5);

}

void create_figure_1b()
{
        LIF_spike X(5);

        // Each of the lines in figure_1b
        //gamma = 0.65 for mu ~ 0.2
        cout << "0.65 Figure starting:" << endl;
	//X.figure_1b_components(0.65);
	X.figure_1b_components(-2.25);

        //gamma = 0.18 for mu ~ 0.1
        cout << "0.18 Figure starting:" << endl;
	//X.figure_1b_components(0.18);
	X.figure_1b_components(-4.5);

        //gamma = -0.07 for mu ~ 0.05
        cout << "-0.07 Figure starting:" << endl;
	//X.figure_1b_components(-0.07);
	X.figure_1b_components(-6.5);

        //gamma = -0.3 for mu ~ 0.02
        cout << "-0.3 Figure starting:" << endl;
	//X.figure_1b_components(-0.3);
	X.figure_1b_components(-8.25);
}

void create_figure_2a()
{
	LIF_spike X(100);

	// lambda = 0.2 for rho ~ 0.05
        cout << "0.2 Figure starting:" << endl;
	X.figure_2a_components(0.2);

	// lambda = 0.36 for rho ~ 0.1
        cout << "0.36 Figure starting:" << endl;
	X.figure_2a_components(0.36);

	// lambda = 0.7 for rho ~ 0.25
        cout << "0.7 Figure starting:" << endl;
	X.figure_2a_components(0.7);
}
