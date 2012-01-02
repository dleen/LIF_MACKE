#include "LIF_spike.h"

using namespace std;

char LIF_spike::progress_bar(int percentage)
{
	string prog ("1%.......10%.......20%.......\
30%.......40%.......50%.......60%.......70%\
.......80%.......90%....100%");

	return prog[percentage];
}

void LIF_spike::figure_1b_components(double gamma)
{
	int k=0,m=0;

        for(int i=0; i<10; ++i)
        {
                for(int j=0; j<10; ++j)
                {
                        create_LIF_data(gamma,i*0.002);
                        print_statistics_to_file();
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

void LIF_spike::figure_2a_components(double gamma)
{

}

void create_figure_1b()
{
        LIF_spike X(5);

        // Each of the lines in figure_1b
        //gamma = 0.65 for mu ~ 0.2
        cout << "0.65 Figure starting:" << endl;
	X.figure_1b_components(0.65);
        //gamma = 0.18 for mu ~ 0.1
        cout << "0.18 Figure starting:" << endl;
	X.figure_1b_components(0.18);
        //gamma = -0.07 for mu ~ 0.05
        cout << "-0.07 Figure starting:" << endl;
	X.figure_1b_components(-0.07);
        //gamma = -0.3 for mu ~ 0.02
        cout << "-0.3 Figure starting:" << endl;
	X.figure_1b_components(-0.3);
}
