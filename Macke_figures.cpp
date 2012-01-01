#include "LIF_spike.h"

char LIF_spike::progress_bar(int percentage)
{
	string prog ("1%.......10%.......20%.......\
30%.......40%.......50%.......60%.......70%\
.......80%.......90%....100%");

	return prog[percentage];
}

void LIF_spike::create_figure_1b(double gamma)
{
	int k=0,m=0;

        for(int i=0; i<500; ++i)
        {
                for(int j=0; j<10; ++j)
                {
                        create_LIF_data(gamma,i*0.002);
                        print_statistics_to_file();
                        zero_LIF_data();

			if(k%(500*10/100) == 0)
			{
				cout << progress_bar(m++) << flush;
			}
			++k;
                }
        }
	cout << endl;
}

void LIF_spike::create_figure_2a(double gamma)
{

}
